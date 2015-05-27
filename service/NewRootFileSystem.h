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

#ifndef __NEWROOTFILESYSTEM_H_
#define __NEWROOTFILESYSTEM_H_
#pragma once

#include <memory>
#include "LinuxException.h"
#include "Directory.h"
#include "Mount.h"

#pragma warning(push, 4)

//-----------------------------------------------------------------------------
// RootFileSystem
//
// RootFileSystem implements a virtual single directory node file system in which
// no additional objects can be created.  Typically used only to provide a default
// virtual file system root node until a proper file system can be mounted

class NewRootFileSystem : public ::Mount, public Directory, public std::enable_shared_from_this<Directory>
{
public:

	// Destructor
	//
	virtual ~NewRootFileSystem()=default;

	// Mount (static)
	//
	// Mounts the file system
	static std::shared_ptr<::Mount> Mount(const char_t* const source, uint32_t flags, const void* data, size_t datalen);

private:

	NewRootFileSystem(const NewRootFileSystem&)=delete;
	NewRootFileSystem& operator=(const NewRootFileSystem&)=delete;

	// (Node)
	//

	// (Directory)
	//

	// Duplicate (Mount)
	//
	// Duplicates this mount instance
	virtual std::shared_ptr<::Mount> Duplicate(void);

	// Remount (Mount)
	//
	// Remounts this mount point with different flags and arguments
	virtual void Remount(uint32_t flags, const void* data, size_t datalen);

	// Node (Mount)
	//
	// Gets a reference to the root node of this mount
	virtual std::shared_ptr<FileSystem::Node> getNode(void);

	// Source
	//
	// Retrieves the source device name used to create the mount
	virtual const char_t* getSource(void);

	// Instance Constructor
	//
	NewRootFileSystem(const char_t* source);
	friend class std::_Ref_count_obj<NewRootFileSystem>;

	//-------------------------------------------------------------------------
	// Member Variables

	std::string					m_source;			// Source device
};

//-----------------------------------------------------------------------------

#pragma warning(pop)

#endif	// __NEWROOTFILESYSTEM_H_