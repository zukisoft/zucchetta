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

#pragma warning(push, 4)

// sys_openat.cpp
//
uapi::long_t sys_openat(const Context* context, int fd, const uapi::char_t* pathname, int flags, uapi::mode_t mode);

//-----------------------------------------------------------------------------
// sys_creat
//
// Creates a regular file object
//
// Arguments:
//
//	context		- System call context object
//	pathname	- Path to the file on the virtual file system
//	mode		- Mode mask to assign to the file if created

uapi::long_t sys_creat(const Context* context, const uapi::char_t* pathname, uapi::mode_t mode)
{
	return -LINUX_ENOSYS;

	//// sys_creat() is equivalent to sys_openat(AT_FDCWD) with a fixed set of flags
	//return sys_openat(context, LINUX_AT_FDCWD, pathname, LINUX_O_CREAT | LINUX_O_WRONLY | LINUX_O_TRUNC, mode);
}

// sys32_creat
//
sys32_long_t sys32_creat(sys32_context_t context, const sys32_char_t* pathname, sys32_mode_t mode)
{
	return static_cast<sys32_long_t>(SystemCall::Invoke(sys_creat, context, pathname, mode));
}

#ifdef _M_X64
// sys64_creat
//
sys64_long_t sys64_creat(sys64_context_t context, const sys64_char_t* pathname, sys64_mode_t mode)
{
	return SystemCall::Invoke(sys_creat, context, pathname, mode);
}
#endif

//---------------------------------------------------------------------------

#pragma warning(pop)
