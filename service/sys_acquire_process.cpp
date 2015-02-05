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
#include "Context.h"
#include "SystemCall.h"

#pragma warning(push, 4)

//-----------------------------------------------------------------------------
// sys32_acquire_process
//
// Acquires the process context for a 32-bit host
//
// Arguments:
//
//	rpchandle		- RPC binding handle
//	threadproc		- [in] address of the thread creation entry point
//	process			- [out] set to the process startup information
//	context			- [out] set to the newly allocated context handle

HRESULT sys32_acquire_process(handle_t rpchandle, sys32_addr_t threadproc, sys32_process_t* process, sys32_context_exclusive_t* context)
{
	uuid_t						objectid;			// RPC object identifier
	Context*					handle = nullptr;	// System call context handle
	RPC_CALL_ATTRIBUTES			attributes;			// Client call attributes
	RPC_STATUS					rpcresult;			// Result from RPC function call

	(threadproc);

	// Acquire the object id for the interface connected to by the client, this will
	// indicate the VirtualMachine instance identifier
	rpcresult = RpcBindingInqObject(rpchandle, &objectid);
	if(rpcresult != RPC_S_OK) return HRESULT_FROM_WIN32(rpcresult);

	// Acquire the attributes of the calling process for the Context object, this 
	// exposes the client process' PID for mapping to a Process object instance
	memset(&attributes, 0, sizeof(RPC_CALL_ATTRIBUTES));
	attributes.Version = RPC_CALL_ATTRIBUTES_VERSION;
	attributes.Flags = RPC_QUERY_CLIENT_PID;

	rpcresult = RpcServerInqCallAttributes(rpchandle, &attributes);
	if(rpcresult != RPC_S_OK) return HRESULT_FROM_WIN32(rpcresult); 

	try {

		// Allocate and initialize a Context object to be passed back as the RPC context
		auto vm = VirtualMachine::FindVirtualMachine(objectid);
		auto proc = vm->FindProcessByHostID(reinterpret_cast<uint32_t>(attributes.ClientPID));
		handle = Context::Allocate(vm, proc);

		// Acquire the task state information for the process
		handle->Process->GetInitialTaskState(&process->task, sizeof(sys32_task_t));
		process->ldt = reinterpret_cast<sys32_addr_t>(const_cast<void*>(handle->Process->TESTLDT));
	}

	catch(const Exception& ex) { Context::Release(handle); return ex.HResult; }
	catch(...) { Context::Release(handle); return E_FAIL; }

	*context = reinterpret_cast<sys32_context_exclusive_t>(handle);
	return S_OK;
}

//---------------------------------------------------------------------------

#pragma warning(pop)