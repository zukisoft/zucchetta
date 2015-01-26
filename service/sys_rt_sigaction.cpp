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
#include "SystemCall.h"

#pragma warning(push, 4)

//-----------------------------------------------------------------------------
// sys_rt_sigaction
//
// Examine or change a signal action
//
// Arguments:
//
//	context		- SystemCall context object
//	signal		- Signal to examine or change (cannot be SIGKILL or SIGSTOP)
//	action		- Specifies the new action for the signal
//	oldaction	- Receives the old action for the signal
//	sigsetsize	- Size of the sigset_t data type

__int3264 sys_rt_sigaction(const SystemCall::Context* context, int signal, const uapi::sigaction* action, uapi::sigaction* oldaction, size_t sigsetsize)
{
	// The RPC marshaler would not have been able to deal with a mask longer than defined in the structure
	if(sigsetsize != sizeof(uapi::sigset_t)) return -LINUX_EINVAL;

	// SIGKILL and SIGSTOP cannot be changed
	if((signal == LINUX_SIGKILL) || (signal == LINUX_SIGSTOP)) return -LINUX_EINVAL;

	// SA_SIGINFO is not currently supported (may never need to be on x86/x86-64)
	if(action && (action->sa_flags & LINUX_SA_SIGINFO)) return -LINUX_EINVAL;

	try {

		SystemCall::Impersonation impersonation;

		(context);
		(signal);
		(action);
		(oldaction);

		return 0;
	}

	catch(...) { return SystemCall::TranslateException(std::current_exception()); }
}

// sys32_rt_sigaction
//
sys32_long_t sys32_rt_sigaction(sys32_context_t context, sys32_int_t signal, const sys32_sigaction_t* action, sys32_sigaction_t* oldaction, sys32_size_t sigsetsize)
{
	static_assert(sizeof(uapi::sigaction) == sizeof(sys32_sigaction_t), "uapi::sigaction is not equivalent to sys32_sigaction_t");
	return sys_rt_sigaction(reinterpret_cast<SystemCall::Context*>(context), signal, reinterpret_cast<const uapi::sigaction*>(action), reinterpret_cast<uapi::sigaction*>(oldaction), sigsetsize);
}

//---------------------------------------------------------------------------

#pragma warning(pop)
