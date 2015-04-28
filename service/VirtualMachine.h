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

#ifndef __VIRTUALMACHINE_H_
#define __VIRTUALMACHINE_H_
#pragma once

#include <concrt.h>
#include <map>
#include <memory>
#include "Namespace.h"
#include "RpcInterface.h"
#include "Session.h"

#pragma warning(push, 4)

//-----------------------------------------------------------------------------
// Class VirtualMachine
//
// VirtualMachine the top-level virtual machine instance

class VirtualMachine : public Service<VirtualMachine>, public std::enable_shared_from_this<VirtualMachine>
{
public:

	// Instance Constructor
	//
	VirtualMachine();

	// Destructor
	//
	~VirtualMachine()=default;

	//-------------------------------------------------------------------------
	// Member Functions

	// Find (static)
	//
	// Locates a virtual machine instance based on its uuid
	static std::shared_ptr<VirtualMachine> Find(const uuid_t& instanceid);

	//-------------------------------------------------------------------------
	// Properties

	// InstanceId
	//
	// Gets the unique identifier for this virtual machine instance
	__declspec(property(get=getInstanceId)) uuid_t InstanceId;
	uuid_t getInstanceID(void) const { return m_instanceid; }

private:

	VirtualMachine(const VirtualMachine&)=delete;
	VirtualMachine& operator=(const VirtualMachine&)=delete;

	// Service<> Control Handler Map
	//
	BEGIN_CONTROL_HANDLER_MAP(VirtualMachine)
		CONTROL_HANDLER_ENTRY(SERVICE_CONTROL_STOP, OnStop)
	END_CONTROL_HANDLER_MAP()

	// uuid_key_comp_t
	//
	// Key comparison type for UUIDs when used as a collection key
	struct uuid_key_comp_t 
	{ 
		bool operator() (const uuid_t& lhs, const uuid_t& rhs) const { return (memcmp(&lhs, &rhs, sizeof(uuid_t)) < 0); }
	};

	// instance_map_t
	//
	// Collection of virtual machine instances
	using instance_map_t = std::map<uuid_t, std::shared_ptr<VirtualMachine>, uuid_key_comp_t>;

	// instance_map_lock_t
	//
	// Synchronization object for the instance collection
	using instance_map_lock_t = Concurrency::reader_writer_lock;

	// session_map_t
	//
	// Collection of sessions created within this virtual machine
	using session_map_t = std::map<std::shared_ptr<Pid>, std::shared_ptr<Session>>;

	// GenerateInstanceId
	//
	// Generates the universally unique identifier for this instance
	static uuid_t GenerateInstanceId(void);

	// OnStart (Service)
	//
	// Invoked when the service is started
	void OnStart(int argc, LPTSTR* argv);

	// OnStop
	//
	// Invoked when the service is stopped
	void OnStop(void);

	//-------------------------------------------------------------------------
	// Member Variables

	static instance_map_t		s_instances;		// Collection of all instances
	static instance_map_lock_t	s_instancelock;		// Synchronization object

	const uuid_t				m_instanceid;		// Instance identifier
	std::shared_ptr<Namespace>	m_rootns;			// Root namespace instance
};

//-----------------------------------------------------------------------------

#pragma warning(pop)

#endif	// __VIRTUALMACHINE_H_
