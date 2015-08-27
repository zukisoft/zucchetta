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
#include "convert.h"

#include <stdint.h>
#include <Windows.h>
#include <linux/time.h>
#include "datetime.h"

#pragma warning(push, 4)

//-----------------------------------------------------------------------------
// Date and Time Conversions
//-----------------------------------------------------------------------------

// datetime --> FILETIME
//
template<> FILETIME convert<FILETIME>(const datetime& rhs)
{
	uint64_t filetime = rhs;
	return *reinterpret_cast<FILETIME*>(&filetime);
}

// FILETIME --> datetime
//
template<> datetime convert<datetime>(const FILETIME& rhs)
{
	return datetime(*reinterpret_cast<const uint64_t*>(&rhs));
}

// datetime --> uapi::timespec
//
template<> uapi::timespec convert<uapi::timespec>(const datetime& rhs)
{
	int64_t unixtime = (static_cast<uint64_t>(rhs) - 116444736000000000i64);
	return{ unixtime / 10000000i64, (unixtime * 100ui64) % 1000000000i64 };
}

// uapi::timespec --> datetime
//
template<> datetime convert<datetime>(const uapi::timespec& rhs)
{
	return datetime((rhs.tv_sec * 10000000i64) + (rhs.tv_nsec / 100i64) + 116444736000000000i64);
}

// FILETIME --> uapi::timespec
//
template<> uapi::timespec convert<uapi::timespec>(const FILETIME& rhs)
{
	int64_t unixtime = (*reinterpret_cast<const uint64_t*>(&rhs) - 116444736000000000i64);
	return{ unixtime / 10000000i64, (unixtime * 100ui64) % 1000000000i64 };
}

// uapi::timespec --> FILETIME
//
template<> FILETIME convert<FILETIME>(const uapi::timespec& rhs)
{
	uint64_t filetime = ((rhs.tv_sec * 10000000i64) + (rhs.tv_nsec / 100i64) + 116444736000000000i64);
	return *reinterpret_cast<FILETIME*>(&filetime);
}

//-----------------------------------------------------------------------------

#pragma warning(pop)
