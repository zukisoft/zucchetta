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
#include <linux\mman.h>

#pragma warning(push, 4)

// g_rpccontext (main.cpp)
//
// RPC context handle
extern sys32_context_t g_rpccontext;

//-----------------------------------------------------------------------------
// sys_clone
//
// Creates a child process or thread
//
// Arguments:
//
//	clone_flags		- Operation flags
//	newsp			- New child process/thread stack address
//	parent_tidptr	- Address to store the new child pid_t (in parent and child)
//	tls_val			- Ignored; new thread local storage descriptor 
//	child_tidptr	- Address to store the new child pit_t (in child only)

uapi::long_t sys_clone(unsigned long clone_flags, void* newsp, uapi::pid_t* parent_tidptr, int tls_val, uapi::pid_t* child_tidptr)
{
	// For now this is just a pass-through to the RPC function, but I think I'll need to use
	// a local syscall to deal with some of this.  It can always be removed later
	//
	// NOTE: The Linux kernel ignores tls_val completely

	return sys32_clone(g_rpccontext, clone_flags, reinterpret_cast<sys32_addr_t>(newsp), reinterpret_cast<sys32_addr_t>(parent_tidptr), 
		tls_val, reinterpret_cast<sys32_addr_t>(child_tidptr));
}

//-----------------------------------------------------------------------------

#pragma warning(pop)

