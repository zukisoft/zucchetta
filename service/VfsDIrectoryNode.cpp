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
#include "VfsDirectoryNode.h"			// Include VfsDirectoryNode declarations

#pragma warning(push, 4)				// Enable maximum compiler warnings

// VfsDirectoryNode::s_lock
//
// Synchronization object (NOTE: may need one per instance rather than static)
ReaderWriterLock VfsDirectoryNode::s_lock;

//-----------------------------------------------------------------------------
// VfsDirectoryNode Constructor
//
// Arguments:
//
//	mode		- Initial mode flags for the virtual directory
//	uid			- Initial owner uid for the virtual directory
//	gid			- Initial owner gid for the virtual directory

VfsDirectoryNode::VfsDirectoryNode(mode_t mode, uid_t uid, gid_t gid) : VfsNode(mode, uid, gid)
{
	_ASSERTE((mode & S_IFMT) == S_IFDIR);
	if((mode & S_IFMT) != S_IFDIR) throw Exception(E_VFS_INVALIDNODEMODE, mode);
}

//-----------------------------------------------------------------------------
// VfsDirectoryNode::AddAlias
//
// Adds a new alias to the directory
//
// Arguments:
//
//	alias		- Alias name
//	node		- VfsNode that alias refers to

void VfsDirectoryNode::AddAlias(const char_t* alias, const VfsNodePtr& node)
{
	AutoWriterLock lock(s_lock);

	// Attempt to insert the alias into the collection
	if(!m_aliases.insert(std::make_pair(std::string(alias), VfsNodePtr(node))).second)
		throw Exception(E_VFS_ALIASEXISTS, alias, VfsNode::Index);
}

//-----------------------------------------------------------------------------
// VfsDirectoryNode::GetAlias
//
// Searches for a specific alias in this directory
//
// Arguments:
//
//	alias		- Alias name

VfsNodePtr VfsDirectoryNode::GetAlias(const char_t* alias)
{
	AutoReaderLock lock(s_lock);

	// Attempt to locate the alias in the member collection, return Null if not found
	std::map<std::string, VfsNodePtr>::iterator iterator = m_aliases.find(std::string(alias));
	if(iterator == m_aliases.end()) return VfsNodePtr::Null;

	return VfsNodePtr(iterator->second);		// Return new VfsNodePtr
}

//-----------------------------------------------------------------------------
// VfsDirectoryNode::RemoveAlias
//
// Removes an alias from the directory
//
// Arguments:
//
//	alias		- Alias name

void VfsDirectoryNode::RemoveAlias(const char_t* alias)
{
	AutoWriterLock lock(s_lock);

	// Attempt to remove the alias from the collection
	if(m_aliases.erase(std::string(alias)) == 0) 
		throw Exception(E_VFS_ALIASNOTFOUND, alias, VfsNode::Index);
}

//-----------------------------------------------------------------------------

#pragma warning(pop)
