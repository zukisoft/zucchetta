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

#ifndef __ELFIMAGE_H_
#define __ELFIMAGE_H_
#pragma once

#include <linux/fs.h>
#include "elf_traits.h"
#include "Architecture.h"
#include "Exception.h"
#include "FileSystem.h"
#include "HeapBuffer.h"
#include "Host.h"
#include "NtApi.h"
#include "SystemInformation.h"
#include "StructuredException.h"
#include "Win32Exception.h"

#pragma warning(push, 4)
#pragma warning(disable:4396)	// inline specifier cannot be used with specialization

//-----------------------------------------------------------------------------
// ElfImage
//
// Loads an ELF binary image into a native operating system host process

class ElfImage
{
public:

	// Destructor
	//
	virtual ~ElfImage()=default;

	//-------------------------------------------------------------------------
	// Member Functions

	// Load (StreamReader)
	//
	// Loads an ELF image into memory from a StreamReader instance
	template <Architecture architecture>
	static std::unique_ptr<ElfImage> Load(const FileSystem::HandlePtr& handle, const std::unique_ptr<Host>& host);

	//-------------------------------------------------------------------------
	// Properties

	// BaseAddress
	//
	// Gets the virtual memory base address of the loaded image
	__declspec(property(get=getBaseAddress)) const void* BaseAddress;
	const void* getBaseAddress(void) const { return m_metadata.BaseAddress; }

	// EntryPoint
	//
	// Gets the entry point for the image
	__declspec(property(get=getEntryPoint)) const void* EntryPoint;
	const void* getEntryPoint(void) const { return m_metadata.EntryPoint; }

	// Interpreter
	//
	// Indicates the path to the program interpreter, if one is present
	__declspec(property(get=getInterpreter)) const uapi::char_t* Interpreter;
	const uapi::char_t* getInterpreter(void) const { return (m_metadata.Interpreter.size() == 0) ? nullptr : m_metadata.Interpreter.c_str(); }

	// ProgramBreak
	//
	// Pointer to the initial program break address
	__declspec(property(get=getProgramBreak)) const void* ProgramBreak;
	const void* getProgramBreak(void) const { return m_metadata.ProgramBreak; }

	// NumProgramHeaders
	//
	// Number of program headers defines as part of the loaded image
	__declspec(property(get=getNumProgramHeaders)) size_t NumProgramHeaders;
	size_t getNumProgramHeaders(void) const { return m_metadata.NumProgramHeaders; }

	// ProgramHeaders
	//
	// Pointer to program headers that were defined as part of the loaded image
	__declspec(property(get=getProgramHeaders)) const void* ProgramHeaders;
	const void* getProgramHeaders(void) const { return m_metadata.ProgramHeaders; }

private:

	ElfImage(const ElfImage&)=delete;
	ElfImage& operator=(const ElfImage&)=delete;

	// Forward Declarations
	//
	struct Metadata;

	// Instance Constructor
	//
	ElfImage(Metadata&& metadata) : m_metadata(std::move(metadata)) {}
	friend std::unique_ptr<ElfImage> std::make_unique<ElfImage, Metadata>(Metadata&&);

	//-------------------------------------------------------------------------
	// Private Type Declarations

	// Metadata
	//
	// Provides information about an image that has been loaded by LoadBinary<>
	struct Metadata
	{
		const void*				BaseAddress = nullptr;
		const void*				ProgramBreak = nullptr;
		const void*				ProgramHeaders = nullptr;
		size_t					NumProgramHeaders = 0;
		const void*				EntryPoint = nullptr;
		std::string				Interpreter;
	};

	//-------------------------------------------------------------------------
	// Private Member Functions

	// FlagsToProtection
	//
	// Converts ELF p_flags into VirtualAlloc(Ex) protection flags
	static DWORD FlagsToProtection(uint32_t flags);

	// LoadBinary
	//
	// Loads an ELF binary image into virtual memory
	template <Architecture architecture>
	static std::unique_ptr<ElfImage> LoadBinary(const FileSystem::HandlePtr& handle, const std::unique_ptr<Host>& host);

	// ValidateHeader
	//
	// Validates the contents of an ELF binary header
	template <Architecture architecture>
	static void ValidateHeader(const typename elf_traits<architecture>::elfheader_t* elfheader);

	//-------------------------------------------------------------------------
	// Member Variables

	Metadata						m_metadata;		// Loaded image metadata
};

//-----------------------------------------------------------------------------

#pragma warning(pop)

#endif	// __ELFIMAGE_H_
