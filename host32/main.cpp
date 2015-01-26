//-----------------------------------------------------------------------------
// Copyright (c) 2015 Michael G. Brehm
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include <process.h>
#include "SystemInformation.h"

#pragma warning(push, 4)
#pragma warning(disable:4731)	// frame pointer modified by inline assembly code

// g_rpccontext
//
// Global RPC context handle to the system calls server
sys32_context_t g_rpccontext;

// EmulationExceptionHandler (emulator.cpp)
//
// Vectored Exception handler used to provide emulation
LONG CALLBACK EmulationExceptionHandler(PEXCEPTION_POINTERS exception);

// t_hostedthread
//
// Used to determine if the current thread is a hosted/emulated thread
__declspec(thread) bool t_hostedthread;

// t_gs (emulator.cpp)
//
// Emulated GS register value
extern __declspec(thread) uint32_t t_gs;

// t_ldt (emulator.cpp)
//
// Thread-local LDT
extern __declspec(thread) sys32_ldt_t t_ldt;

//// TEST
#include <vector>
#include <linux\signal.h>
std::vector<uapi::sigaction> g_sigactions;
//////////

//-----------------------------------------------------------------------------
// ThreadMain
//
// Entry point for a hosted thread
//
// Arguments:
//
//	arg			- Argument passed to _beginthreadex (sys32_task_state_t)

unsigned __stdcall ThreadMain(void* arg)
{
	uapi::pid_t				tid;				// Thread id from the RPC service

	// This is a hosted thread
	t_hostedthread = true;

	// First register the thread with the RPC service
	HRESULT result = sys32_register_thread(g_rpccontext, GetCurrentThreadId(), &tid);
	if(FAILED(result)) { /* TODO: HANDLE BAD THING */ }

	// Cast out the task state structure passed into the thread entry point
	sys32_task_state_t* taskstate = reinterpret_cast<sys32_task_state_t*>(arg);

	// Initialize the LDT as a copy of the provided LDT
	memcpy(&t_ldt, taskstate->ldt, sizeof(sys32_ldt_t));

	// Set up the emulated GS register for this thread
	t_gs = taskstate->gs;
	
	// Use the frame pointer to access the startup information fields;
	// this function will never return so it can be trashed
	__asm mov ebp, arg;

	// Set the general-purpose registers
	__asm mov eax, [ebp]sys32_task_state_t.eax;
	__asm mov ebx, [ebp]sys32_task_state_t.ebx;
	__asm mov ecx, [ebp]sys32_task_state_t.ecx;
	__asm mov edx, [ebp]sys32_task_state_t.edx;
	__asm mov edi, [ebp]sys32_task_state_t.edi;
	__asm mov esi, [ebp]sys32_task_state_t.esi;

	// Set the stack pointer and push the instruction pointer
	__asm mov esp, [ebp]sys32_task_state_t.esp;
	__asm push [ebp]sys32_task_state_t.eip;

	// Restore the frame pointer and jump via return
	__asm mov ebp, [ebp]sys32_task_state_t.ebp;
	__asm ret

	// Hosted thread never returns control back to here
	return static_cast<unsigned>(E_UNEXPECTED);
}

//-----------------------------------------------------------------------------
// WinMain
//
// Application entry point
//
// Arguments:
//
//	hInstance			- Application instance handle (base address)
//	hPrevInstance		- Unused in Win32
//	pszCommandLine		- Pointer to the application command line
//	nCmdShow			- Initial window show command

int APIENTRY _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	zero_init<sys32_task_state_t>	taskstate;		// State information from the service
	RPC_BINDING_HANDLE				binding;		// RPC binding from command line
	MSG								message;		// Thread message queue message
	RPC_STATUS						rpcresult;		// Result from RPC function call
	DWORD							exitcode;		// Exit code from the main thread
	HRESULT							hresult;		// Result from system call API function

	// This is not a hosted thread
	t_hostedthread = false;

	// EXPECTED ARGUMENTS:
	//
	// [0] - Executable path
	// [1] - RPC binding string
	if(__argc != 2) return static_cast<int>(ERROR_INVALID_PARAMETER);

	// The only argument passed into the host process is the RPC binding string necessary to connect to the server
	rpcresult = RpcBindingFromStringBinding(reinterpret_cast<rpc_tchar_t*>(__targv[1]), &binding);
	if(rpcresult != RPC_S_OK) return static_cast<int>(rpcresult);

	// Establish a thread message queue prior to contacting the RPC server
	PeekMessage(&message, nullptr, WM_USER, WM_USER, PM_NOREMOVE);

	// Attempt to acquire the host runtime context handle from the server
	hresult = sys32_acquire_context(binding, &taskstate, &g_rpccontext);
	if(FAILED(hresult)) return static_cast<int>(hresult);

	// Create a suspended thread that will execute the Linux binary
	HANDLE thread = reinterpret_cast<HANDLE>(_beginthreadex(nullptr, SystemInformation::AllocationGranularity, ThreadMain, &taskstate, CREATE_SUSPENDED, nullptr));
	if(thread == nullptr) { /* TODO: HANDLE THIS */ }

	// Install the emulator, which operates by intercepting low-level exceptions
	AddVectoredExceptionHandler(1, EmulationExceptionHandler);

	ResumeThread(thread);						// Launch the hosted process

	// TODO: TEMPORARY - This thread will need to wait for signals and also shouldn't
	// die until every hosted thread has called exit() or some reasonable equivalent

	// New plan, this would be a standard message loop not msgwaitformultipleobjects/peekmessage,
	// GetMessage returns false when WM_QUIT is received
	while(MsgWaitForMultipleObjects(1, &thread, FALSE, INFINITE, QS_ALLPOSTMESSAGE) == (WAIT_OBJECT_0 + 1)) {

		while(PeekMessage(&message, reinterpret_cast<HWND>(-1), 0, 0, PM_REMOVE)) {

			int signal;
			switch(message.message) {

				// WM_APP: placeholder for a signal
				case WM_APP:
					// lParam == signal code
					signal = static_cast<int>(message.lParam);
					break;

				// WM_QUIT: will need to handle this
				case WM_QUIT:
					break;
			}
		}
	}

	///WaitForSingleObject(thread, INFINITE);

	GetExitCodeThread(thread, &exitcode);		// Get the exit code from the thread
	CloseHandle(thread);						// Finished with the thread handle

	// All hosted threads have terminated, release the RPC context
	sys32_release_context(&g_rpccontext);

	// Return the exit code from the main thread as the result from this process
	return static_cast<int>(exitcode);
}

//-----------------------------------------------------------------------------

#pragma warning(pop)
