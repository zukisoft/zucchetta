////-----------------------------------------------------------------------------
//// Copyright (c) 2014 Michael G. Brehm
//// 
//// Permission is hereby granted, free of charge, to any person obtaining a copy
//// of this software and associated documentation files (the "Software"), to deal
//// in the Software without restriction, including without limitation the rights
//// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//// copies of the Software, and to permit persons to whom the Software is
//// furnished to do so, subject to the following conditions:
//// 
//// The above copyright notice and this permission notice shall be included in all
//// copies or substantial portions of the Software.
//// 
//// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//// SOFTWARE.
////-----------------------------------------------------------------------------
//
#include "stdafx.h"
//#include "RamFileSystem.h"
//
//#pragma warning(push, 4)
//
//// RamFileSystem::Chunk::BlockSize
////
//// Initialized to the system memory page size
//const size_t RamFileSystem::Chunk::BlockSize = []() -> size_t {
//
//	SYSTEM_INFO info;
//	GetNativeSystemInfo(&info);
//	return info.dwPageSize;
//}();
//
////-----------------------------------------------------------------------------
//// RamFileSystem::Chunk Destructor
//
//RamFileSystem::Chunk::~Chunk()
//{
//	// Release the entire chunk of virtual memory on destruction
//	if(m_base) VirtualFree(reinterpret_cast<void*>(m_base), 0, MEM_RELEASE);
//}
//
////-----------------------------------------------------------------------------
//// RamFileSystem::Chunk::AllocateBlock
////
//// Allocates a block of data from the chunk
////
//// Arguments:
////
////	NONE
//
//int16_t RamFileSystem::Chunk::AllocateBlock(void)
//{
//	// The other version of AllocateBlock() that returns the pointer
//	// to the data is undoubtedly going to be more useful, implementation
//	// has been moved into that function ...
//
//	int16_t index;
//	AllocateBlock(index);
//	return index;
//}
//
////-----------------------------------------------------------------------------
//// RamFileSystem::Chunk::AllocateBlock
////
//// Allocates a block of data from the chunk and provides the base pointer
////
//// Arguments:
////
////	index		- Reference to receive the allocated block index
//
//void* RamFileSystem::Chunk::AllocateBlock(int16_t& index)
//{
//	// Try to grab a spent index first, otherwise grab a new one
//	if(!m_spentblocks.try_pop(index)) index = m_nextblock++;
//
//	// Check that the index is within the boundaries of this chunk
//	if((index < 0) || (index >= m_total)) throw std::exception("TODO: new exception"); //Win32Exception(ERROR_INVALID_ADDRESS);
//
//	// Calculate the address of the block being committed and validate it
//	void* address = reinterpret_cast<void*>(m_base + (index * BlockSize));
//	_ASSERTE(ValidateBlockState(address, MEM_RESERVE));
//
//	// Commit the page with READWRITE access only, no EXECUTE here
//	if(!VirtualAlloc(address, BlockSize, MEM_COMMIT, PAGE_READWRITE)) throw std::exception("TODO: new exception"); //throw Win32Exception();
//
//	return address;
//}
//
////-----------------------------------------------------------------------------
//// RamFileSystem::Chunk::Create (static)
////
//// Creates a Chunk instance
////
//// Arguments:
////
////	blocks		- Number of blocks to reserve for this chunk
//
//std::unique_ptr<RamFileSystem::Chunk> RamFileSystem::Chunk::Create(int16_t blocks)
//{
//	// Attempt to reserve a contiguous address space for the chunk
//	void* base = VirtualAlloc(nullptr, blocks * BlockSize, MEM_RESERVE, PAGE_NOACCESS);
//	if(base == nullptr) throw std::exception("TODO: new excepton"); //Win32Exception();
//
//	return std::make_unique<Chunk>(base, blocks);
//}
//
////-----------------------------------------------------------------------------
//// RamFileSystem::Chunk::getBlock
////
//// Gets the base pointer for an allocated (committed) block
////
//// Arguments:
////
////	index		- Allocated block index
//
//void* RamFileSystem::Chunk::getBlock(int16_t index) const
//{
//	// Check that the index is within the boundaries of this chunk
//	if((index < 0) || (index > m_total)) throw std::exception("TODO: new exception"); //Win32Exception(ERROR_INVALID_ADDRESS);
//
//	// Calculate the address of the block being accessed and validate it
//	void* address = reinterpret_cast<void*>(m_base + (index * BlockSize));
//	_ASSERTE(ValidateBlockState(address, MEM_COMMIT));
//
//	return address;
//}
//
////-----------------------------------------------------------------------------
//// RamFileSystem::Chunk::ReleaseBlock
////
//// Releases a block from the chunk and marks it as available for reuse
////
//// Arguments:
////
////	index		- Allocated block index
//
//void RamFileSystem::Chunk::ReleaseBlock(int16_t index)
//{
//	// Check that the index is within the boundaries of this chunk
//	if((index < 0) || (index > m_total)) throw std::exception("TODO: new exception"); //Win32Exception(ERROR_INVALID_ADDRESS);
//
//	// Calculate the address of the block being released and validate it
//	void* address = reinterpret_cast<void*>(m_base + (index * BlockSize));
//	_ASSERTE(ValidateBlockState(address, MEM_COMMIT));
//
//	// Decommit the block from virtual memory and add the index to the spent blocks queue
//	if(!VirtualFree(address, BlockSize, MEM_DECOMMIT)) throw std::exception("TODO: new exception"); //Win32Exception();
//	m_spentblocks.push(index);
//}
//
////-----------------------------------------------------------------------------
//// RamFileSystem::Chunk::ValidateBlockState (private)
////
//// Verifies that a block address is in an expected state (committed/decommitted)
////
//// Arguments:
////
////	address		- Block address to validate
////	state		- Expected block state
//
//bool RamFileSystem::Chunk::ValidateBlockState(void* address, DWORD state) const
//{
//	// Query the information about the specified address
//	MEMORY_BASIC_INFORMATION meminfo;
//	VirtualQuery(address, &meminfo, sizeof(MEMORY_BASIC_INFORMATION));
//
//	// Check the state of the page against what the caller provided
//	return (meminfo.State == state);
//}
//
////-----------------------------------------------------------------------------
//// RamFileSystem::Alias
////-----------------------------------------------------------------------------
//
////-----------------------------------------------------------------------------
//// RamFileSystem::Alias Constructor (Root Node)
////
//// Arguments:
////
////	fs		- Reference to the parent RamFileSystem instance
//
//RamFileSystem::Alias::Alias(RamFileSystem& fs) : m_fs(fs) 
//{
//}
//
////-----------------------------------------------------------------------------
//// RamFileSystem::Alias Constructor
////
//// Arguments:
////
////	fs		- Reference to the parent RamFileSystem instance
////	parent	- Reference to the parent Alias instance
////	name	- Name to assign to this alias
//
//RamFileSystem::Alias::Alias(RamFileSystem& fs, const std::shared_ptr<FileSystem::Alias>& parent, const char_t* name) : Alias(fs)
//{
//	_ASSERTE(name && (name[0]));		// Name should never be NULL or zero-length
//
//	m_parent = parent;
//	m_name = name;
//}
//
//void RamFileSystem::Alias::AttachNode(const std::shared_ptr<FileSystem::Node>& node)
//{
//}
//
//
//RamFileSystem::File::File(RamFileSystem& fs, const std::shared_ptr<Node>& node) :
//	m_fs(fs), m_node(node)
//{
//}
//
//
//// node ctor
//RamFileSystem::Node::Node(RamFileSystem& fs) : m_fs(fs)
//{
//	m_index = static_cast<uint32_t>(m_fs.AllocateNodeIndex());
//}
//
//// node dtor
//RamFileSystem::Node::~Node()
//{
//	// Once the node has been deallocated, release it's index
//	m_fs.RelaseNodeIndex(static_cast<int32_t>(m_index));
//}
//
////-----------------------------------------------------------------------------
//// RamFileSystem Constructor
////
//// Arguments:
////
////	max				- Maximum size of the file system
//
//RamFileSystem::RamFileSystem(size_t max) : FileSystem()
//{
//	// todo: this needs to be sized appropriately, cannot go over int16_t max
//	// the idea is to allocate multiple smaller chunks rather than one large
//	// one as that will reserve the entire address space
//	m_tempchunk = Chunk::Create(1000);
//
//	// Construct a new Node that will serve as the filesystem root.
//	// (This should always end up with an assigned index of zero)
//	m_root = std::make_shared<Node>(*this);
//	_ASSERTE(m_root->Index == 0);
//}
//
//uint32_t RamFileSystem::AllocateBlock(void)
//{
//	_ASSERTE(m_tempchunk);
//
//	// TODO: This utlimately needs to store an CHUNK:BLOCK rather than
//	// just the BLOCK (chunk is always zero right now)
//
//	return static_cast<uint32_t>(m_tempchunk->AllocateBlock());
//}
//
//void* RamFileSystem::AllocateBlock(uint32_t& block)
//{
//	int16_t temp = 0;
//
//	_ASSERTE(m_tempchunk);
//
//	void* result = m_tempchunk->AllocateBlock(temp);
//
//	// TODO: This utlimately needs to store an CHUNK:BLOCK rather than
//	// just the BLOCK (Chunk is always zero right now)
//	block = static_cast<uint32_t>(temp);
//
//	return result;
//}
//
////-----------------------------------------------------------------------------
//// RamFileSystem::AllocateNodeIndex (private)
////
//// Allocates a node index from the pool of available indexes
////
//// Arguments:
////
////	NONE
//
//int32_t RamFileSystem::AllocateNodeIndex(void)
//{
//	int32_t index;					// Allocated index value
//
//	// Try to reuse a spent node index first, otherwise grab a new one.
//	// If the returned value overflowed, there are no more indexes left
//	if(!m_spentinodes.try_pop(index)) index = m_nextinode++;
//	if(index < 0) throw std::exception("TODO - EXCEPTION");
//
//	return index;
//}
//
//void RamFileSystem::ReleaseBlock(uint32_t block)
//{
//	// TODO: this changes to an CHUNK:BLOCK opaque key
//	_ASSERTE(block <= INT16_MAX);
//	m_tempchunk->ReleaseBlock(static_cast<int16_t>(block));
//}
//
////-----------------------------------------------------------------------------
//// RamFileSystem::ReleaseNodeIndex (private)
////
//// Releases a node index back into the pool of available indexes
////
//// Arguments:
////
////	index		- Node index to be released
//
//void RamFileSystem::RelaseNodeIndex(int32_t index)
//{
//	// The node indexes are reused aggressively for this file system,
//	// push it into the spent index queue so that it will be grabbed
//	// by AllocateNodeIndex() before a new index is generated
//	m_spentinodes.push(index);
//}
//
////-----------------------------------------------------------------------------
//// RamFileSystem::Mount (static)
////
//// Mounts the file system on the specified device
////
//// Arguments:
////
////	flags			- Flags passed into the mount() function
////	devicename		- Device name to mount the filesystem on
////	data			- File system specific mount information
//
//std::unique_ptr<FileSystem> RamFileSystem::Mount(int flags, const char_t* devicename, void* data)
//{
//	size_t max = UINT32_MAX;
//	return std::make_unique<RamFileSystem>(max);		// todo: parse
//}
//
////-----------------------------------------------------------------------------
//
//#pragma warning(pop)