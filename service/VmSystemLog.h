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

#ifndef __VMSYSTEMLOG_H_
#define __VMSYSTEMLOG_H_
#pragma once

#include "Exception.h"
#include "MemoryRegion.h"
#include "VmSettings.h"

#pragma warning(push, 4)
#pragma warning(disable:4200)		// zero-sized array in struct/union

// VmSystemLogFacility
//
// Strongly typed enumeration defining the facility of a log entry
enum class VmSystemLogFacility : uint8_t
{
	Kernel			= 0,			// Kernel-generated log entry
	User			= 1,			// User-generated log entry

	// TODO: there are many more of these
};

// VmSystemLogFormat
//
// Strongly typed enumeration defining the print format for the system log
enum class VmSystemLogFormat
{
	Standard		= 0,			// Standard kmsg format
	Device			= 1,			// Linux /dev/mksg device format
};

// VmSystemLogLevel
//
// Strongly typed enumeration defining the level of a log entry
enum class VmSystemLogLevel : uint8_t
{
	Emergency		= 0,			// System is unusable
	Alert			= 1,			// Action must be taken immediately
	Critical		= 2,			// Critical conditions
	Error			= 3,			// Error conditions
	Warning			= 4,			// Warning conditions
	Notice			= 5,			// Normal but significant condition
	Informational	= 6,			// Informational
	Debug			= 7,			// Debug-level messages
};

//-----------------------------------------------------------------------------
// VmSystemLog
//
// Provides the system log functionality for a virtual machine, similar to the
// linux kernel ring buffer
//
// TODO: NEEDS TO BE THREAD-SAFE; start with a basic slim reader/writer or something
// and then comment that this should be upgraded to a lock-free implementation
// in the future -- the performance of this class is important, but not if I'm
// never going to finish this project!

class VmSystemLog
{
public:

	// Constructor / Destructor
	VmSystemLog(const std::unique_ptr<VmSettings>& settings);
	~VmSystemLog()=default;

	//-------------------------------------------------------------------------
	// Member Functions

	// Peek
	//
	// Reads entries from the system log, does not clear them
	size_t Peek(void* buffer, size_t length) { return Peek(VmSystemLogFormat::Standard, buffer, length); }
	size_t Peek(VmSystemLogFormat format, void* buffer, size_t length);

	// Pop
	//
	// Reads entries from the system log and removes them
	size_t Pop(void* buffer, size_t length) { return Pop(VmSystemLogFormat::Standard, buffer, length); }
	size_t Pop(VmSystemLogFormat format, void* buffer, size_t length);

	// Push
	// 
	// Writes an entry into the system log
	// TODO: needs better overloads for facility, level, should accept varargs, and so on
	void Push(const char_t* message) { return Push(VmSystemLogLevel::Error, VmSystemLogFacility::Kernel, message); }
	void Push(VmSystemLogLevel level, const char_t* message) { return Push(level, VmSystemLogFacility::Kernel, message); }
	void Push(VmSystemLogLevel level, VmSystemLogFacility facility, const char_t* message);

	//-------------------------------------------------------------------------
	// Properties

	// Available
	//
	// Gets the number of bytes available to be read from the log
	__declspec(property(get=getAvailable)) size_t Available;
	size_t getAvailable(void) { return Peek(nullptr, 0); }

	// TODO: Need more properties, like the default console log level -- see syslog(2)

	// Length
	//
	// The adjusted length of the system log circular buffer
	__declspec(property(get=getLength)) size_t Length;
	size_t getLength(void) const { return m_buffer->Length; }

	// TimestampBias
	//
	// Gets/sets the bias to use when printing timestamp values; this value
	// should come from a call to QueryPerformanceCounter() at startup
	__declspec(property(get=getTimestampBias, put=putTimestampBias)) int64_t TimestampBias;
	int64_t getTimestampBias(void) const { return m_tsbias; }
	void putTimestampBias(int64_t value) { m_tsbias = value; }

private:

	VmSystemLog(const VmSystemLog&)=delete;
	VmSystemLog& operator=(const VmSystemLog&)=delete;

	// MAX_BUFFER
	//
	// Controls the upper boundary on the system log size
	static const size_t MAX_BUFFER	= (1 << 23);

	// LogEntry
	//
	// Represents the data contained in a single log entry
	struct LogEntry
	{
		int64_t			timestamp;			// Entry timestamp
		uint16_t		entrylength;		// Overall entry length
		uint16_t		messagelength;		// Length of the message text
		uint8_t			facility : 5;		// Facility code
		uint8_t			level : 3;			// Entry level code
		uint8_t			reserved[3];		// Alignment padding (repurpose me)
		char_t			message[];			// Log message text

		// message[] is followed by padding to properly align the next entry
	};

	//-------------------------------------------------------------------------
	// Private Member Functions

	// Align
	//
	// Address alignment helper function
	template <typename _type, size_t _align = __alignof(void*)>
	inline _type Align(_type value) { return value + ((_align - (value % _align)) % _align); }

	// IncrementTail
	//
	// Increments a tail pointer to reference the next log entry
	bool IncrementTailPointer(uintptr_t& tailptr);

	// Print
	//
	// Prints data from the log into an output buffer using a specified tail pointer
	size_t Print(VmSystemLogFormat format, char* buffer, size_t length, uintptr_t& tailptr);

	// PrintDeviceFormat
	//
	// Formats a log entry to an output buffer in DEVICE format
	size_t PrintDeviceFormat(const LogEntry* entry, char* buffer, size_t length);

	// PrintStandardFormat
	//
	// Formats a log entry to an output buffer in STANDARD format
	size_t PrintStandardFormat(const LogEntry* entry, char* buffer, size_t length);

	//-------------------------------------------------------------------------
	// Member Variables

	std::unique_ptr<MemoryRegion>	m_buffer;			// Underlying buffer
	uintptr_t						m_top;				// Top of the buffer
	uintptr_t						m_bottom;			// Bottom of the buffer
	uintptr_t						m_head;				// Write position
	uintptr_t						m_tail;				// Read position
	double							m_tsfreq;			// Timestamp frequency
	int64_t							m_tsbias = 0;		// Timestamp bias
};

//-----------------------------------------------------------------------------

#pragma warning(pop)

#endif	// __VMSYSTEMLOG_H_
