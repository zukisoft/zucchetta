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

#ifndef __IMAGE_H_
#define __IMAGE_H_
#pragma once

#pragma warning(push, 4)

//-----------------------------------------------------------------------------
// Class Image
//
// Image provides information about a loaded executable module

struct __declspec(novtable) Image
{
	//-------------------------------------------------------------------------
	// Properties

	// BaseAddress
	//
	// Gets the base address of the loaded image
	__declspec(property(get=getBaseAddress)) void const* BaseAddress;
	virtual void const* getBaseAddress(void) const = 0;

	// EntryPoint
	//
	// Gets the entry point of the loaded image
	__declspec(property(get=getEntryPoint)) void const* EntryPoint;
	virtual void const* getEntryPoint(void) const = 0;
};

//-----------------------------------------------------------------------------

#pragma warning(pop)

#endif	// __IMAGE_H_
