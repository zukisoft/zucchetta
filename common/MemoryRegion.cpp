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

#include "stdafx.h"
#include "MemoryRegion.h"

#pragma warning(push, 4)				

// MemoryRegion::s_sysinfo
//
// Static SYSTEM_INFO information
MemoryRegion::SystemInfo MemoryRegion::s_sysinfo;

// MemoryRegion::AllocationGranularity
//
// Static copy of the system allocation granularity
size_t const MemoryRegion::AllocationGranularity = MemoryRegion::s_sysinfo.dwAllocationGranularity;

// MemoryRegion::PageSize
//
// Static copy of the system page size
size_t const MemoryRegion::PageSize = MemoryRegion::s_sysinfo.dwPageSize;

//-----------------------------------------------------------------------------
// MemoryRegion Destructor

MemoryRegion::~MemoryRegion()
{
	if(m_base) {

		// Decommit and release the memory region with the appropriate API
		if(m_process == INVALID_HANDLE_VALUE) VirtualFree(m_base, 0, MEM_RELEASE);
		else VirtualFreeEx(m_process, m_base, 0, MEM_RELEASE);
	}
}

//-----------------------------------------------------------------------------
// MemoryRegion::Commit
//
// Commits page(s) of memory within the region using the specified protection
// attributes.  If address does not align on a page boundary it will be aligned
// down and returned as the result from this function
//
// Arguments:
//
//	address		- Base address to be committed
//	length		- Length of the region to be committed
//	protect		- Protection flags to be applied to the committed region

void* MemoryRegion::Commit(void* address, size_t length, uint32_t protect)
{
	uintptr_t base = uintptr_t(m_base);
	uintptr_t requested = uintptr_t(address);
	uintptr_t aligned = align::down(uintptr_t(address), MemoryRegion::PageSize);

	// Verify the requested address space is not outside of the region
	length += requested - aligned;
	if((aligned < base) || ((aligned + length) > (base + m_length))) throw Exception(E_BOUNDS);	

	// Use the appropriate VirtualAlloc version to commit the page(s) within the region
	void* result = (m_process == INVALID_HANDLE_VALUE) ? VirtualAlloc(address, length, MEM_COMMIT, protect) :
		VirtualAllocEx(m_process, address, length, MEM_COMMIT, protect);
	if(result == nullptr) throw Win32Exception();

	return result;
}

//-----------------------------------------------------------------------------
// MemoryRegion::Decommit
//
// Decommits page(s) of memory from within the region 
//
// Arguments:
//
//	address		- Base address to be decommitted
//	length		- Length of the region to be decommitted

void* MemoryRegion::Decommit(void* address, size_t length)
{
	uintptr_t base = uintptr_t(m_base);
	uintptr_t requested = uintptr_t(address);
	uintptr_t aligned = align::down(uintptr_t(address), MemoryRegion::PageSize);

	// Verify the requested address space is not outside of the region
	length += requested - aligned;
	if((aligned < base) || ((aligned + length) > (base + m_length))) throw Exception(E_BOUNDS);	

	// Use the appropriate VirtualFree version to decommit the page(s) from within the region
	BOOL result = (m_process == INVALID_HANDLE_VALUE) ? VirtualFree(reinterpret_cast<void*>(aligned), length, MEM_DECOMMIT) :
		VirtualFreeEx(m_process, reinterpret_cast<void*>(aligned), length, MEM_DECOMMIT);
	if(!result) throw Win32Exception();

	return reinterpret_cast<void*>(aligned);
}

//-----------------------------------------------------------------------------
// MemoryRegion::Detach
//
// Detaches the memory region from the class so that it will not be released
// on object destruction
//
// Arguments:
//
//	length		- Optional size_t pointer to receive the region length

void* MemoryRegion::Detach(size_t* length)
{
	// Save the region base pointer and optionally set the length [out] argument
	void* base = m_base;
	if(length) *length = m_length;

	// Reset member variables to an uninitialized state
	m_base = nullptr;
	m_length = 0;
	m_process = INVALID_HANDLE_VALUE;

	// Return the previously held base address
	return base;
}

//-----------------------------------------------------------------------------
// MemoryRegion::Lock
//
// Locks page(s) of the region into physical memory
//
// Arguments:
//
//	address		- Base address to be locked
//	length		- Length of the region to be locked

void* MemoryRegion::Lock(void* address, size_t length)
{
	// Lock cannot be used on memory regions assigned to another process
	if(m_process != INVALID_HANDLE_VALUE) throw Win32Exception(ERROR_INVALID_HANDLE);

	uintptr_t base = uintptr_t(m_base);
	uintptr_t requested = uintptr_t(address);
	uintptr_t aligned = align::down(uintptr_t(address), MemoryRegion::PageSize);

	// Verify the requested address space is not outside of the region
	length += requested - aligned;
	if((aligned < base) || ((aligned + length) > (base + m_length))) throw Exception(E_BOUNDS);	

	// Use the appropriate version of VirtualLock to lock the page(s) into physical memory
	if(!VirtualLock(reinterpret_cast<void*>(aligned), length)) throw Win32Exception();

	return reinterpret_cast<void*>(aligned);
}

//-----------------------------------------------------------------------------
// MemoryRegion::Protect
//
// Applies new protection flags to page(s) within the allocated region
//
// Arguments:
//
//	address		- Base address to apply the protection
//	length		- Length of the memory to apply the protection to
//	protect		- Virtual memory protection flags

void* MemoryRegion::Protect(void* address, size_t length, uint32_t protect)
{
	DWORD		oldprotect;					// Old protection flags

	uintptr_t base = uintptr_t(m_base);
	uintptr_t requested = uintptr_t(address);
	uintptr_t aligned = align::down(uintptr_t(address), MemoryRegion::PageSize);

	// Verify the requested address space is not outside of the region
	length += requested - aligned;
	if((aligned < base) || ((aligned + length) > (base + m_length))) throw Exception(E_BOUNDS);	

	// Apply the requested protection flags; throw away the old flags returned
	BOOL result = (m_process == INVALID_HANDLE_VALUE) ? VirtualProtect(reinterpret_cast<void*>(aligned), length, protect, &oldprotect) :
		VirtualProtectEx(m_process, reinterpret_cast<void*>(aligned), length, protect, &oldprotect);
	if(!result) throw Win32Exception();

	return reinterpret_cast<void*>(aligned);
}

//-----------------------------------------------------------------------------
// MemoryRegion::Reserve (private, static)
//
// Arguments:
//
//	process		- Optional process handle to operate against or INVALID_HANDLE_VALUE
//	address		- Optional base address to use for the allocation
//	length		- Length of the memory region to allocate
//	flags		- Memory region allocation type flags
//	protect		- Memory region protection flags

std::unique_ptr<MemoryRegion> MemoryRegion::Reserve(HANDLE process, size_t length, void* address, uint32_t flags, uint32_t protect)
{
	//
	// TODO: This is completely screwed up, why did I do this?  What SHOULD happen here
	// is that the base address is stored so that VirtualFree(Ex) can be called, BUT the
	// pointer ultimately returned to the caller needs to be the original address or if NULL,
	// the base address.  All these functions are aligning crap for no reason?
	//

	// Can calculate the MEMORY_BASIC_INFORMATION, don't need VirtualQuery(Ex)

	uintptr_t requested = uintptr_t(address);
	uintptr_t aligned = align::down(uintptr_t(address), MemoryRegion::AllocationGranularity);

	// Adjust the requested length to accomodate any downward alignment
	length += requested - aligned;

	// Pass the arguments onto the appropriate VirtualAlloc and just throw any resultant error
	void* base = (process == INVALID_HANDLE_VALUE) ? VirtualAlloc(address, length, flags, protect) :
		VirtualAllocEx(process, address, length, flags, protect);
	if(!base) throw Win32Exception();

	// Some callers have a need to know exactly what memory was reserved, run VirtualQuery()
	// before any pages are changed to get metadata about the entire region
	MEMORY_BASIC_INFORMATION meminfo;
	BOOL result = (process == INVALID_HANDLE_VALUE) ? VirtualQuery(base, &meminfo, sizeof(MEMORY_BASIC_INFORMATION)) :
		VirtualQueryEx(process, base, &meminfo, sizeof(MEMORY_BASIC_INFORMATION));
	if(!result) {

		Win32Exception exception;				// GetLastError-based exception object

		// In the unlikely event that VirtualQuery(Ex) fails, the region has to be released
		// before throwing the exception up to the caller
		if(process == INVALID_HANDLE_VALUE) VirtualFree(base, 0, MEM_RELEASE);
		else VirtualFreeEx(process, base, 0, MEM_RELEASE);
		throw exception;
	}

	// Construct the MemoryRegion instance to take ownership of the pointer
	return std::make_unique<MemoryRegion>(process, base, length, std::move(meminfo));
}

//-----------------------------------------------------------------------------
// MemoryRegion::Unlock
//
// Unlocks page(s) of the region from physical memory
//
// Arguments:
//
//	address		- Base address to be unlocked
//	length		- Length of the region to be unlocked

void* MemoryRegion::Unlock(void* address, size_t length)
{
	// Unlock cannot be used on memory regions assigned to another process
	if(m_process != INVALID_HANDLE_VALUE) throw Win32Exception(ERROR_INVALID_HANDLE);

	uintptr_t base = uintptr_t(m_base);
	uintptr_t requested = uintptr_t(address);
	uintptr_t aligned = align::down(uintptr_t(address), MemoryRegion::PageSize);

	// Verify the requested address space is not outside of the region
	length += requested - aligned;
	if((aligned < base) || ((aligned + length) > (base + m_length))) throw Exception(E_BOUNDS);	

	// Use VirtualUnlock() to unlock the page(s) from physical memory
	if(!VirtualUnlock(reinterpret_cast<void*>(aligned), length)) throw Win32Exception();

	return reinterpret_cast<void*>(aligned);
}

//-----------------------------------------------------------------------------

#pragma warning(pop)
