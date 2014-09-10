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

#ifndef __FILESYSTEM_H_
#define __FILESYSTEM_H_
#pragma once

#include <vector>
#include <linux/fcntl.h>
#include <linux/stat.h>
#include <linux/types.h>

#pragma warning(push, 4)

// todo: document

struct FileSystem;
using FileSystemPtr = std::shared_ptr<FileSystem>;

//-----------------------------------------------------------------------------
// FileSystem
//
// todo: words

struct __declspec(novtable) FileSystem
{
	// AliasPtr
	//
	// Alias for an std::shared_ptr<Alias>
	struct Alias;
	using AliasPtr = std::shared_ptr<Alias>;

	// DirectoryPtr
	//
	// Alias for an std::shared_ptr<Directory>
	struct Directory;
	using DirectoryPtr = std::shared_ptr<Directory>;

	// HandlePtr
	//
	// Alias for an std::shared_ptr<Handle>
	struct Handle;
	using HandlePtr = std::shared_ptr<Handle>;

	// NodePtr
	//
	// Alias for an std::shared_ptr<Node>
	struct Node;
	using NodePtr = std::shared_ptr<Node>;

	// SymbolicLinkPtr
	//
	// Alias for an std::shared_ptr<SymbolicLink>
	struct SymbolicLink;
	using SymbolicLinkPtr = std::shared_ptr<SymbolicLink>;

	// need typedef for Mount(const tchar_t* device, uint32_t flags, const void* data)
	// need table type for mountable file systems -> Mount() function pointers

	// NodeType
	//
	// Strogly typed enumeration for the S_IFxxx inode type constants
	enum class NodeType
	{
		BlockDevice			= LINUX_S_IFBLK,
		CharacterDevice		= LINUX_S_IFCHR,
		Directory			= LINUX_S_IFDIR,
		File				= LINUX_S_IFREG,
		Pipe				= LINUX_S_IFIFO,
		Socket				= LINUX_S_IFSOCK,
		SymbolicLink		= LINUX_S_IFLNK,
	};

	// NODE_INDEX_ROOT
	//
	// Constant indicating the node index for a file system root node
	static const uapi::ino_t NODE_INDEX_ROOT = 2;

	// NODE_INDEX_LOSTANDFOUND
	//
	// Constant indicating the node index for a lost+found directory node
	static const uapi::ino_t NODE_INDEX_LOSTANDFOUND = 3;

	// NODE_INDEX_FIRSTDYNAMIC
	//
	// Constant indicating the first dynamic node index that should be used
	static const uapi::ino_t NODE_INDEX_FIRSTDYNAMIC = 4;

	//
	static const int MAXIMUM_PATH_SYMLINKS = 40;

	// Alias
	//
	// todo: document when done
	struct __declspec(novtable) Alias
	{
		// Mount
		//
		// Mounts/binds a foreign node to this alias, obscuring the previous node
		virtual void Mount(const NodePtr& node) = 0;

		// Unmount
		//
		// Unmounts/unbinds a node from this alias, revealing the previously bound node
		virtual void Unmount(void) = 0;

		// Name
		//
		// Gets the name associated with this alias
		__declspec(property(get=getName)) const tchar_t* Name;
		virtual const tchar_t* getName(void) = 0;

		// Node
		//
		// Gets the node instance that this alias references
		__declspec(property(get=getNode)) NodePtr Node;
		virtual NodePtr getNode(void) = 0;

		// Parent
		//
		// Gets the parent Alias instance for this alias
		__declspec(property(get=getParent)) AliasPtr Parent;
		virtual AliasPtr getParent(void) = 0;
	};

	// Node
	//
	// todo: need permission arguments (mode_t)
	struct __declspec(novtable) Node
	{
		// Open
		//
		// Creates a FileSystem::Handle instance for this node
		virtual HandlePtr Open(int flags) = 0;

		// Resolve
		//
		// Resolves a relative path from this node to an Alias instance
		// TODO: too many arguments, create a state object.  Resolve() is recursive, don't blow up the stack
		virtual AliasPtr Resolve(const AliasPtr& root, const AliasPtr& current, const tchar_t* path, int flags, int* symlinks) = 0;		

		// Index
		//
		// Gets the node index
		__declspec(property(get=getIndex)) uint64_t Index;
		virtual uint64_t getIndex(void) = 0;

		// Type
		//
		// Gets the node type
		__declspec(property(get=getType)) NodeType Type;
		virtual NodeType getType(void) = 0;
	};

	// Directory
	//
	// Specialization of Node for Directory objects
	struct __declspec(novtable) Directory : public Node
	{
		// CreateDirectory
		//
		// Creates a new directory node as a child of this node
		virtual void CreateDirectory(const AliasPtr& parent, const tchar_t* name) = 0;

		// CreateFile
		//
		// Creates a new regular file node as a child of this node
		virtual HandlePtr CreateFile(const AliasPtr& parent, const tchar_t* name, int flags) = 0;

		// CreateNode
		//
		// Creates a new special node as a child of this node
		// TODO

		// CreateSymbolicLink
		//
		// Creates a new symbolic link as a child of this node
		virtual void CreateSymbolicLink(const AliasPtr& parent, const tchar_t* name, const tchar_t* target) = 0;

		// RemoveDirectory
		//
		// Removes a directory child from the node
		//virtual void RemoveDirectory(const tchar_t* name) = 0;

		// RemoveNode
		//
		// Removes a non-directory child from the node
		//virtual void RemoveNode(const tchar_t* name) = 0;
	};

	// SymbolicLink
	//
	// Specialization of Node for Symbolic Link objects
	struct __declspec(novtable) SymbolicLink : public virtual Node
	{
		// ReadTarget
		//
		// Reads the target of the symbolic link
		virtual uapi::size_t ReadTarget(tchar_t* buffer, size_t count) = 0; 
	};

	// Handle
	//
	// todo: document when done
	struct __declspec(novtable) Handle
	{
		// Read
		//
		// Synchronously reads data from the underlying node into a buffer
		virtual uapi::size_t Read(void* buffer, uapi::size_t count) = 0;

		// Seek
		//
		// Changes the file position
		virtual uapi::loff_t Seek(uapi::loff_t offset, int whence) = 0;

		// Sync
		//
		// Synchronizes all metadata and data associated with the file to storage
		virtual void Sync(void) = 0;

		// SyncData
		//
		// Synchronizes all data associated with the file to storage, not metadata
		virtual void SyncData(void) = 0;

		// Write
		//
		// Synchronously writes data from a buffer to the underlying node
		virtual uapi::size_t Write(const void* buffer, uapi::size_t count) = 0;
	};

	//
	// FileSystem Members
	//

	// Remount
	//
	// Changes the options used for the file system mount
	//// virtual void Remount(uint32_t flags, const void* data) = 0;

	// Root
	//
	// Returns the root alias for the file system
	__declspec(property(get=getRoot)) AliasPtr Root;
	virtual AliasPtr getRoot(void) = 0;
};

//-----------------------------------------------------------------------------

#pragma warning(pop)

#endif	// __FILESYSTEM_H_