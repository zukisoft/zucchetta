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

#ifndef __ELFBINARYIMAGE_H_
#define __ELFBINARYIMAGE_H_
#pragma once

#include <memory>
#include "Architecture.h"
#include "BinaryImage.h"
#include "BinaryFormat.h"

#pragma warning(push, 4)
#pragma warning(disable:4396)	// inline specifier cannot be used with specialization

// Forward Declarations
//
class Executable;
class Host;

//-----------------------------------------------------------------------------
// ElfBinaryImage
//
// Specialization of BinaryImage for ELF images

class ElfBinaryImage : public BinaryImage
{
public:

	// Destructor
	//
	virtual ~ElfBinaryImage()=default;

	//-------------------------------------------------------------------------
	// Friend Functions

	// LoadElfBinary
	//
	// Architecture-specific implementation of Load
	template<Architecture architecture>
	friend std::unique_ptr<BinaryImage> LoadElfBinary(Host* host, Executable const* executable);

	// ValidateElfHeader
	//
	// Architecture-specific ELF header validation function
	template <Architecture architecture>
	friend void ValidateElfHeader(void const* buffer, size_t cb);

	//-------------------------------------------------------------------------
	// Member Functions

	// Load (static)
	//
	// Loads an ELF binary image
	static std::unique_ptr<BinaryImage> Load(Host* host, Executable const* executable);

	//-------------------------------------------------------------------------
	// Binary Implementation

	// getBaseAddress
	//
	// Gets the virtual memory base address of the loaded image
	virtual void const* getBaseAddress(void) const;

	// getBreakAddress
	//
	// Get a pointer to the program break address
	virtual void const* getBreakAddress(void) const;

	// EntryPoint
	//
	// Gets the entry point for the image
	virtual void const* getEntryPoint(void) const;

	// getInterpreter
	//
	// Indicates the path to the program interpreter binary, if one is present
	virtual char_t const* getInterpreter(void) const;

	// getProgramHeadersAddress
	//
	// Pointer to program headers that were defined as part of the loaded image
	virtual void const* getProgramHeadersAddress(void) const;

	// getProgramHeaderCount
	//
	// Number of program headers defines as part of the loaded image
	virtual size_t getProgramHeaderCount(void) const;

private:

	ElfBinaryImage(ElfBinaryImage const&)=delete;
	ElfBinaryImage& operator=(ElfBinaryImage const&)=delete;

	// format_traits_t
	//
	// Architecture specific ELF format traits
	template <Architecture architecture> struct format_traits_t {};

	// metadata_t
	//
	// Provides metadata about the loaded Elf image
	struct metadata_t
	{
		void const*		baseaddress = nullptr;
		void const*		breakaddress = nullptr;
		void const*		entrypoint = nullptr;
		void const*		progheaders = nullptr;
		size_t			numprogheaders = 0;
		std::string		interpreter;
	};

	// Instance Constructor
	//
	ElfBinaryImage(metadata_t&& metadata);
	friend std::unique_ptr<ElfBinaryImage> std::make_unique<ElfBinaryImage, metadata_t>(metadata_t&&);

	//-------------------------------------------------------------------------
	// Member Variables

	metadata_t const		m_metadata;			// Loaded image metadata
};

//-----------------------------------------------------------------------------

#pragma warning(pop)

#endif	// __ELFBINARYIMAGE_H_