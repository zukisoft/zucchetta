//-----------------------------------------------------------------------------
// Copyright (c) 2016 Michael G. Brehm
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
#include "SystemCall.h"

#include "SystemCallContext.h"
#include "Process.h"

#pragma warning(push, 4)

//-----------------------------------------------------------------------------
// sys_umask
//
// Sets the default file creation mask for the calling process
//
// Arguments:
//
//	context		- System call context object
//	mask		- New default file creation bitmask

uapi::long_t sys_umask(const Context* context, uapi::mode_t mask)
{
	return -LINUX_ENOSYS;

	//// Get the previously set UMASK and apply the new one
	//uapi::mode_t previous = context->Process->FileCreationModeMask;
	//context->Process->FileCreationModeMask = mask;

	//// Return the previous UMASK bitmask as the result from this system call
	//return static_cast<uapi::long_t>(previous);
}

// sys32_umask
//
sys32_long_t sys32_umask(sys32_context_t context, sys32_mode_t mask)
{
	return static_cast<sys32_long_t>(SystemCall::Invoke(sys_umask, context, mask));
}

#ifdef _M_X64
// sys64_umask
//
sys64_long_t sys64_umask(sys64_context_t context, sys64_mode_t mask)
{
	return SystemCall::Invoke(sys_umask, context, mask);
}
#endif

//---------------------------------------------------------------------------

#pragma warning(pop)
