//-----------------------------------------------------------------------------
// Copyright (c) 2014 Michael G. Brehm
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

// g_rpccontext
//
// Global RPC context handle to the system calls server
sys64_context_t g_rpccontext;

//-----------------------------------------------------------------------------
// _tmain
//
// Application entry point
//
// Arguments:
//
//	argc		- Number of provided command line arguments
//	argv		- Array of command line argument strings

int _tmain(int argc, tchar_t** argv)
{
	zero_init<sys64_startup_info>	startinfo;			// Startup information from the service
	RPC_BINDING_HANDLE				binding;			// RPC binding from command line
	RPC_STATUS						rpcresult;			// Result from RPC function call
	HRESULT							hresult;			// Result from system call API function

	// EXPECTED ARGUMENTS:
	//
	// [0] - Executable path
	// [1] - RPC binding string
	if(argc != 2) return static_cast<int>(ERROR_INVALID_PARAMETER);

	// The only argument passed into the host process is the RPC binding string necessary to connect to the server
	rpcresult = RpcBindingFromStringBinding(reinterpret_cast<rpc_tchar_t*>(argv[1]), &binding);
	if(rpcresult != RPC_S_OK) return static_cast<int>(rpcresult);

	// Attempt to acquire the host runtime context handle from the server
	hresult = sys64_acquire_context(binding, &startinfo, &g_rpccontext);
	if(FAILED(hresult)) return static_cast<int>(hresult);

	// TODO: this is temporary; the main thread needs to wait for signals and whatnot
	return static_cast<int>(sys64_release_context(&g_rpccontext));
}

//-----------------------------------------------------------------------------
