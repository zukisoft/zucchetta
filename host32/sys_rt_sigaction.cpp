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
#include <linux/signal.h>

#pragma warning(push, 4)

//-----------------------------------------------------------------------------
// sys_rt_sigaction
//
// Examine or change a signal action
//
// Arguments:
//
//	signal		- Signal to examine or change (cannot be SIGKILL or SIGSTOP)
//	action		- Specifies the new action for the signal
//	oldaction	- Receives the old action for the signal
//	sigsetsize	- Size of the sigset_t data type

uapi::long_t sys_rt_sigaction(int signal, const uapi::sigaction* action, uapi::sigaction* oldaction, size_t sigsetsize)
{
	return -38;
}

//-----------------------------------------------------------------------------

#pragma warning(pop)

