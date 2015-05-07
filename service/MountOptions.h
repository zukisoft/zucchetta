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

#ifndef __MOUNTOPTIONS_H_
#define __MOUNTOPTIONS_H_
#pragma once

#include <atomic>
#include <map>
#include <memory>
#include <vector>
#include <linux/fs.h>

#pragma warning(push, 4)				
#pragma warning(disable:4396)	// inline specifier cannot be used with specialization

//-----------------------------------------------------------------------------
// MountOptions
//
// Linux mounting options processor class.  This accepts the general mount flags
// and optional data arguments from mount(2) and parses them out

class MountOptions
{
	// MountArguments
	//
	// Forward declaration of private class type
	class MountArguments;

public:

	//-------------------------------------------------------------------------
	// Member Functions

	// Create (static)
	//
	// Constructs a new MountOptions instance based on standard mount arguments
	static std::unique_ptr<MountOptions> Create(uint32_t flags);
	static std::unique_ptr<MountOptions> Create(uint32_t flags, const void* data, size_t datalen);

	// Parse (static)
	//
	// Parses a string-based set of mounting options 
	static std::unique_ptr<MountOptions> Parse(const char_t* options);
	static std::unique_ptr<MountOptions> Parse(uint32_t flags, const char_t* options);

	//-------------------------------------------------------------------------
	// Properties

	// AllowMandatoryLocks
	//
	// Gets/sets the MS_MANDLOCK mount flag
	__declspec(property(get=getAllowMandatoryLocks, put=putAllowMandatoryLocks)) bool AllowMandatoryLocks;
	bool getAllowMandatoryLocks(void) const { return getFlag(LINUX_MS_MANDLOCK); }
	void putAllowMandatoryLocks(bool value) { putFlag(LINUX_MS_MANDLOCK, value); }

	// ExtraArguments
	//
	// Gets a reference to the contained MountArguments instance
	__declspec(property(get=getExtraArguments)) const MountArguments& ExtraArguments;
	const MountArguments& getExtraArguments(void) const { return m_arguments; }

	// KernelMount
	//
	// Gets the MS_KERNMOUNT mount flag
	__declspec(property(get=getKernelMount)) bool KernelMount;
	bool getKernelMount(void) const { return getFlag(LINUX_MS_KERNMOUNT); }

	// LazyTimes
	//
	// Gets the MS_LAZYTIME mount flag
	__declspec(property(get=getLazyTimes)) bool LazyTimes;
	bool getLazyTimes(void) const { return getFlag(LINUX_MS_LAZYTIME); }

	// NoAccessTimes
	//
	// Gets the MS_NOATIME mount flag
	__declspec(property(get=getNoAccessTimes)) bool NoAccessTimes;
	bool getNoAccessTimes(void) const { return getFlag(LINUX_MS_NOATIME); }

	// NoDevices
	//
	// Gets the MS_NODEV mount flag
	__declspec(property(get=getNoDevices)) bool NoDevices;
	bool getNoDevices(void) const { return getFlag(LINUX_MS_NODEV); }

	// NoDirectoryAccessTimes
	//
	// Gets the MS_NODIRATIME mount flag
	__declspec(property(get=getNoDirectoryAccessTimes)) bool NoDirectoryAccessTimes;
	bool getNoDirectoryAccessTimes(void) const { return getFlag(LINUX_MS_NODIRATIME); }

	// NoExecute
	//
	// Gets the MS_NOEXEC mount flag
	__declspec(property(get=getNoExecute)) bool NoExecute;
	bool getNoExecute(void) const { return getFlag(LINUX_MS_NOEXEC); }

	// NoSuperUser
	//
	// Gets the MS_NOSUID mount flag
	__declspec(property(get=getNoSuperUser)) bool NoSuperUser;
	bool getNoSuperUser(void) const { return getFlag(LINUX_MS_NOSUID); }

	// ReadOnly
	//
	// Gets/sets the MS_RDONLY mount flag
	__declspec(property(get=getReadOnly, put=putReadOnly)) bool ReadOnly;
	bool getReadOnly(void) const { return getFlag(LINUX_MS_RDONLY); }
	void putReadOnly(bool value) { putFlag(LINUX_MS_RDONLY, value); }

	// RelativeAccessTimes
	//
	// Gets the MS_RELATIME mount flag
	__declspec(property(get=getRelativeAccessTimes)) bool RelativeAccessTimes;
	bool getRelativeAccessTimes(void) const { return getFlag(LINUX_MS_RELATIME); }

	// Remount
	//
	// Gets the MS_REMOUNT mount flag
	__declspec(property(get=getRemount)) bool Remount;
	bool getRemount(void) const { return getFlag(LINUX_MS_REMOUNT); }

	// Silent
	//
	// Gets the MS_SILENT mount flag
	__declspec(property(get=getSilent)) bool Silent;
	bool getSilent(void) const { return getFlag(LINUX_MS_SILENT); }

	// StrictAccessTimes
	//
	// Gets the MS_STRICTATIME mount flag
	__declspec(property(get=getStrictAccessTimes)) bool StrictAccessTimes;
	bool getStrictAccessTimes(void) const { return getFlag(LINUX_MS_STRICTATIME); }

	// SynchronousDirectoryWrites
	//
	// Gets the MS_DIRSYNC mount flag
	__declspec(property(get=getSynchronousDirectoryWrites)) bool SynchronousDirectoryWrites;
	bool getSynchronousDirectoryWrites(void) const { return getFlag(LINUX_MS_DIRSYNC); }

	// SynchronousWrites
	//
	// Gets/sets the MS_SYNCHRONOUS mount flag
	__declspec(property(get=getSynchronousWrites, put=putSynchronousWrites)) bool SynchronousWrites;
	bool getSynchronousWrites(void) const { return getFlag(LINUX_MS_SYNCHRONOUS); }
	void putSynchronousWrites(bool value) { putFlag(LINUX_MS_SYNCHRONOUS, value); }

private:

	MountOptions(const MountOptions&)=delete;
	MountOptions& operator=(const MountOptions&)=delete;

	//-------------------------------------------------------------------------
	// Private Type Declarations

	// MountArguments
	//
	// Collection type for mounting options passed through data
	class MountArguments
	{
	public:

		// Constructor
		explicit MountArguments(const std::vector<std::string>& args);

		// Contains
		//
		// Determines if the collection contains at least one of the switches
		bool Contains(const std::string& key) const;

		// GetValue
		//
		// Gets the first value associated with a switch key
		std::string GetValue(const std::string& key) const;

		// GetValues
		//
		// Gets all values associated with a switch key
		std::vector<std::string> GetValues(const std::string key) const;

	private:

		MountArguments(const MountArguments&)=delete;
		MountArguments& operator=(const MountArguments&)=delete;

		// ArgumentCompare
		//
		// Case-insensitive key comparison for the argument collection
		struct ArgumentCompare 
		{ 
			bool operator() (const std::string& lhs, const std::string& rhs) const 
			{ 
				return _stricmp(lhs.c_str(), rhs.c_str()) < 0; 
			}
		};
	
		// m_col
		//
		// Collection of non-standard mounting arguments
		std::multimap<std::string, std::string, ArgumentCompare> m_col;
	};

	// Instance Constructor
	//

	MountOptions(uint32_t flags, std::vector<std::string>&& extraargs);
	friend std::unique_ptr<MountOptions> std::make_unique<MountOptions, uint32_t&, std::vector<std::string>>(uint32_t&, std::vector<std::string>&&);

	//-------------------------------------------------------------------------
	// Private Member Functions

	// getFlag / putFlag
	//
	// Helper function to get/set specific flag bits
	inline bool getFlag(uint32_t flag) const { return (m_flags & flag) == flag; }
	inline void putFlag(uint32_t flag, bool value) { if(value) m_flags |= flag; else m_flags &= ~flag; }

	// ParseToken (static)
	//
	// Parses a single mounting options string token
	static void ParseToken(std::string&& token, uint32_t& flags, std::vector<std::string>& extraarguments);

	//-------------------------------------------------------------------------
	// Member Variables

	std::atomic<uint32_t>		m_flags;			// Standard mounting flags
	MountArguments				m_arguments;		// Non-standard arguments
};

//-----------------------------------------------------------------------------

#pragma warning(pop)

#endif	// __MOUNTOPTIONS_H_
