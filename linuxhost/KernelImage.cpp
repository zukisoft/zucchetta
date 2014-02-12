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
#include "KernelImage.h"				// Include KernelImage decls

#pragma warning(push, 4)				// Enable maximum compiler warnings

#define KiB		*(1 << 10)				// KiB multiplier
#define MiB		*(1 << 20)				// MiB multiplier

//-----------------------------------------------------------------------------
// KernelImage::Load (static)
//
// Loads and decompresses a Linux kernel image from disk
//
// Arguments:
//
//	path			- Path to the Linux kernel image file

KernelImage* KernelImage::Load(LPCTSTR path)
{
	void*					vmlinuz;				// Pointer to the vmlinuz image

	// Create a read-only memory mapping of the kernel image file
	std::unique_ptr<KernelImage::MappedImage> mapping(KernelImage::MappedImage::Load(path));

	// Test for magic numbers in the memory mapped file in the same order as extract-vmlinux.
	// When a magic number is found, attempt to decompress and test the image successfully before 
	// moving on to the next potential compression algorithm.  Limit searches to the first 512KiB
	// of the file to try and avoid false positives

	// UNCOMPRESSED -----
	if(ElfBinary::TryValidateHeader(mapping->Pointer, mapping->Length)) {

		std::unique_ptr<StreamReader> reader(new BufferStreamReader(mapping->Pointer, mapping->Length));
		return new KernelImage(ElfBinary::Load(reader));
	}

	// GZIP -------------
	uint8_t gzipMagic[] = { 0x1F, 0x8B, 0x08, 0x00 };
	vmlinuz = BoyerMoore::Search(mapping->Pointer, min(512 KiB, mapping->Length), gzipMagic, sizeof(gzipMagic));
	if(vmlinuz != NULL) {

		size_t length = mapping->Length - (reinterpret_cast<intptr_t>(vmlinuz) - reinterpret_cast<intptr_t>(mapping->Pointer));
		std::unique_ptr<StreamReader> reader(new GZipStreamReader(vmlinuz, length));
		return new KernelImage(ElfBinary::Load(reader));
	}

	// XZ ---------------
	uint8_t xzMagic[] = { 0xFD, '7', 'z', 'X', 'Z', 0x00 };
	vmlinuz = BoyerMoore::Search(mapping->Pointer, min(512 KiB, mapping->Length), xzMagic, sizeof(xzMagic));
	if(vmlinuz != NULL) {

		size_t length = mapping->Length - (reinterpret_cast<intptr_t>(vmlinuz) - reinterpret_cast<intptr_t>(mapping->Pointer));
		std::unique_ptr<StreamReader> reader(new XzStreamReader(vmlinuz, length));
		return new KernelImage(ElfBinary::Load(reader));
	}
	
	// BZIP2 ------------
	uint8_t bzip2Magic[] = { 'B', 'Z', 'h' };
	vmlinuz = BoyerMoore::Search(mapping->Pointer, min(512 KiB, mapping->Length), bzip2Magic, sizeof(bzip2Magic));
	if(vmlinuz != NULL) {

		size_t length = mapping->Length - (reinterpret_cast<intptr_t>(vmlinuz) - reinterpret_cast<intptr_t>(mapping->Pointer));
		std::unique_ptr<StreamReader> reader(new BZip2StreamReader(vmlinuz, length));
		return new KernelImage(ElfBinary::Load(reader));
	}

	// LZMA -------------
	uint8_t lzmaMagic[] = { 0x5D, 0x00, 0x00, 0x00 };
	vmlinuz = BoyerMoore::Search(mapping->Pointer, min(512 KiB, mapping->Length), lzmaMagic, sizeof(lzmaMagic));
	if(vmlinuz != NULL) {

		//
		// TODO: Not sure I even want to support LZMA, but I did all the others ...
		//
	}
	
	// LZOP --------------
	uint8_t lzopMagic[] = { 0x89, 'L', 'Z', 'O', 0x00, 0x0D, 0x0A, 0x1A, 0x0A };
	vmlinuz = BoyerMoore::Search(mapping->Pointer, min(512 KiB, mapping->Length), lzopMagic, sizeof(lzopMagic));
	if(vmlinuz != NULL) {

		size_t length = mapping->Length - (reinterpret_cast<intptr_t>(vmlinuz) - reinterpret_cast<intptr_t>(mapping->Pointer));
		std::unique_ptr<StreamReader> reader(new LzopStreamReader(vmlinuz, length));
		return new KernelImage(ElfBinary::Load(reader));
	}

	// LZ4 --------------
	uint8_t lz4Magic[] = { 0x02, 0x21, 0x4C, 0x18 };
	vmlinuz = BoyerMoore::Search(mapping->Pointer, min(512 KiB, mapping->Length), lz4Magic, sizeof(lz4Magic));
	if(vmlinuz != NULL) {

		size_t length = mapping->Length - (reinterpret_cast<intptr_t>(vmlinuz) - reinterpret_cast<intptr_t>(mapping->Pointer));
		std::unique_ptr<StreamReader> reader(new Lz4StreamReader(vmlinuz, length));
		return new KernelImage(ElfBinary::Load(reader));
	}

	// UNKNOWN ----------
	throw Exception(E_KERNELIMAGE_UNKNOWNFORMAT);
}

//-----------------------------------------------------------------------------
// KernelImage::MappedImage Destructor

KernelImage::MappedImage::~MappedImage()
{
	if(m_pvMapping) UnmapViewOfFile(m_pvMapping);
	if(m_hMapping) CloseHandle(m_hMapping);
	if(m_hFile != INVALID_HANDLE_VALUE) CloseHandle(m_hFile);
}

//-----------------------------------------------------------------------------
// KernelImage::MappedImage::Load (static)
//
// Creates a read-only memory mapped file against the raw kernel image
//
// Arguments:
//
//	path			- Path to the Linux kernel image file

KernelImage::MappedImage* KernelImage::MappedImage::Load(LPCTSTR path)
{
	HANDLE						hFile;				// Image file handle
	HANDLE						hMapping;			// Image file mapping handle
	void*						pvMapping;			// Pointer to the mapped file data

	if(!path || !(*path)) throw Exception(E_INVALIDARG);

	// Open the input file in read-only sequential scan mode
	hFile = CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if(hFile == INVALID_HANDLE_VALUE) throw Win32Exception();

	// Create a file mapping for the entire input file
	hMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	if(hMapping == NULL) { DWORD dwResult = GetLastError(); CloseHandle(hFile); throw Win32Exception(dwResult); }

	// Map the input file as read-only memory
	pvMapping = MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);
	if(pvMapping == NULL) { DWORD dwResult = GetLastError(); CloseHandle(hMapping); CloseHandle(hFile); throw Win32Exception(dwResult); }

	return new KernelImage::MappedImage(hFile, hMapping, pvMapping);
}

size_t KernelImage::MappedImage::getLength(void) const
{
	MEMORY_BASIC_INFORMATION	memInfo;			// Mapped file information

	// Get the size of the mapped file memory
	ZeroMemory(&memInfo, sizeof(MEMORY_BASIC_INFORMATION));
	VirtualQuery(m_pvMapping, &memInfo, sizeof(MEMORY_BASIC_INFORMATION));

	return memInfo.RegionSize;
}

//-----------------------------------------------------------------------------

#pragma warning(pop)
