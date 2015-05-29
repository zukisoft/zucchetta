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

#ifndef __DIRECTORY_H_
#define __DIRECTORY_H_
#pragma once

#include "Node.h"

#pragma warning(push, 4)

// Forward Declarations
//
struct __declspec(novtable) Alias;

//-----------------------------------------------------------------------------
// Directory
//
// Specialization of Node for a file system directory object

struct Directory : public Node
{
	// CreateCharacterDevice
	//
	// Creates a new character device node as a child of this node
	virtual void CreateCharacterDevice(const std::shared_ptr<Alias>& parent, const char_t* name, uapi::mode_t mode, uapi::dev_t device) = 0;

	// CreateDirectory
	//
	// Creates a new directory node as a child of this node
	virtual void CreateDirectory(const std::shared_ptr<Alias>& parent, const char_t* name, uapi::mode_t mode) = 0;

	// CreateFile
	//
	// Creates a new regular file node as a child of this node
	virtual std::shared_ptr<Handle> CreateFile(const std::shared_ptr<Alias>& parent, const char_t* name, int flags, uapi::mode_t mode) = 0;

	// CreateSymbolicLink
	//
	// Creates a new symbolic link as a child of this node
	virtual void CreateSymbolicLink(const std::shared_ptr<Alias>& parent, const char_t* name, const char_t* target) = 0;
};

//-----------------------------------------------------------------------------

#pragma warning(pop)

#endif	// __DIRECTORY_H_