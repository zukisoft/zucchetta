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
#include "Mount.h"

#pragma warning(push, 4)

//-----------------------------------------------------------------------------
// Mount Constructor (private)
//
// Arguments:
//
//	source		- Source device name of the mount point
//	target		- Target alias of the mount point
//	fs			- File system instance referenced by the mount point

Mount::Mount(const char_t* const source, const std::shared_ptr<::FileSystem::Alias>& target,
	const std::shared_ptr<::FileSystem>& fs) : m_source(source), m_target(target), m_fs(fs)
{
}

//-----------------------------------------------------------------------------
// Mount::getFileSystem
//
// Gets the FileSystem instance referenced by this mount point

std::shared_ptr<::FileSystem> Mount::getFileSystem(void) const
{
	return m_fs;
}

//-----------------------------------------------------------------------------
// Mount::getSource
//
// Gets the source device name for the mount point

const char_t* const Mount::getSource(void) const
{
	return m_source.c_str();
}

//-----------------------------------------------------------------------------
// Mount::getSource
//
// Gets a reference to the mount point target alias

std::shared_ptr<FileSystem::Alias> Mount::getTarget(void) const
{
	return m_target;
}

//-----------------------------------------------------------------------------

#pragma warning(pop)
