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

#include "stdafx.h"						// Include project pre-compiled headers
#include "Exception.h"					// Include Exception declarations

#pragma warning(push, 4)				// Enable maximum compiler warnings

//-----------------------------------------------------------------------------
// Exception Constructor
//
// Arguments:
//
//	hResult			- HRESULT code
//	...				- Variable arguments to be passed to FormatMessage

Exception::Exception(HRESULT hResult, ...) : m_hResult(hResult), m_inner(nullptr)
{
	LPTSTR			formatted;				// Formatted message

	// Initialize the variable argument list for FormatMessage()
	va_list	args;
	va_start(args, hResult);

	// Invoke FormatMessage to convert the HRESULT and the variable arguments into a message,
	// either from the system or the message resources in this module
	if(FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_FROM_SYSTEM, 
		GetModuleHandle(NULL), static_cast<DWORD>(hResult), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
		reinterpret_cast<LPTSTR>(&formatted), 0, &args) == 0) return;

	m_message = formatted;					// Convert into an std::string/wstring
	LocalFree(formatted);					// Release the allocated buffer
}

//-----------------------------------------------------------------------------
// Exception Constructor
//
// Arguments:
//
//	inner			- Inner exception object
//	hResult			- HRESULT code
//	...				- Variable arguments to be passed to FormatMessage

Exception::Exception(Exception& inner, HRESULT hResult, ...) : m_hResult(hResult)
{
	LPTSTR			formatted;				// Formatted message

	m_inner = new Exception(inner);			// Allocate inner exception

	// Initialize the variable argument list for FormatMessage()
	va_list	args;
	va_start(args, hResult);

	// Invoke FormatMessage to convert the HRESULT and the variable arguments into a message,
	// either from the system or the message resources in this module
	if(FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_FROM_SYSTEM, 
		GetModuleHandle(NULL), static_cast<DWORD>(hResult), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
		reinterpret_cast<LPTSTR>(&formatted), 0, &args) == 0) return;

	m_message = formatted;					// Convert into an std::string/wstring
	LocalFree(formatted);					// Release the allocated buffer
}

//-----------------------------------------------------------------------------
// Exception Copy Constructor

Exception::Exception(const Exception& rhs) 
{
	m_hResult = rhs.m_hResult;
	m_message = rhs.m_message;
	m_inner = (rhs.m_inner) ? new Exception(*rhs.m_inner) : nullptr;
}

//----------------------------------------------------------------------------
// Exception Destructor

Exception::~Exception()
{
	if(m_inner) delete m_inner;
}

//-----------------------------------------------------------------------------
// Exception::operator=

Exception& Exception::operator=(const Exception& rhs)
{
	m_hResult = rhs.m_hResult;
	m_message = rhs.m_message;
	
	// Inner exceptions are pointer-based; delete before changing it
	if(m_inner) delete m_inner; 
	m_inner = (rhs.m_inner) ? new Exception(*rhs.m_inner) : nullptr;

	return *this;
}

//-----------------------------------------------------------------------------

#pragma warning(pop)