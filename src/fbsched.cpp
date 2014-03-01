/* (C) 2012 Markus Klotzbuecher <markus.klotzbuecher@mech.kuleuven.be>
 * Department of Mechanical Engineering
 * Katholieke Universiteit Leuven, Belgium.
 * Licensed under dual LGPL/BSD. See footer.
 */

#include "fbsched.hpp"
#include <rtt/Component.hpp>
#include <iostream>

using namespace RTT;
using namespace std;

// helper
bool contains(std::vector<std::string> &sv, const std::string &s)
{
	std::vector<std::string>::iterator it;

	for (it=sv.begin(); it<sv.end(); it++)
		if(*it == s) return true;

	return false;
}

FBSched::FBSched(std::string const& name)
	: TaskContext(name)
{
	this->addProperty("sched_order", sched_order).doc("Partial order in which peers are executed. Unmentioned peers come last.");

	this->addEventPort("trigger", trigger).doc("Event port for triggering a function block update cycle. Value is ignored.");

	this->addOperation("displaySchedList", &FBSched::displaySchedList, this, OwnThread).doc("Display the current list of scheduled components. This is for debug purposes");
}

bool FBSched::startHook()
{
	std::vector<std::string>::iterator it;
	RTT::TaskContext* tc_tmp;

	// place all remaining peers in sched_list
	std::vector<std::string> peers = this->getPeerList();

	// first store all peers mentioned in sched_order in sched_list
	for(it=sched_order.begin(); it<sched_order.end(); it++) {
		if((tc_tmp=this->getPeer(*it))==0) {
			Logger::log(Logger::Error) << "FBSched error: component '" << *it
						   << "'in sched_order is not a peer of us."
						   << endlog();
			goto out_fail;
		}
		sched_list.push_back(tc_tmp);
	}

	for(it=peers.begin(); it<peers.end(); it++) {
		if (!contains(sched_order, *it)) { // current peer not mentioned in order
			if((tc_tmp=this->getPeer(*it))==0) {
				Logger::log(Logger::Error)
					<< "FBSched error: failed to getPeer '" << *it << "'" << endlog();
				goto out_fail;
			}
			sched_list.push_back(tc_tmp);
		}
	}

	/* catch silly misconfigurations */
	if (sched_list.size() == 0) {
		Logger::log(Logger::Error) << "FBSched error: refusing to start with zero peers to trigger"
					   << endlog();
		goto out_fail;
	}

	/* everythink Ok! */
	Logger::log(Logger::Info) << "FBSched: running " << sched_list.size()
				  << " peers in the following order:";

	for(unsigned int i=0; i<sched_list.size(); i++)
		Logger::log(Logger::Info) << " " << sched_list[i]->getName();

	Logger::log(Logger::Info) << endlog();

	return true;

 out_fail:
	sched_list.clear();
	return false;
}

void FBSched::updateHook()
{
	for(unsigned int i=0; i<sched_list.size(); i++) {
		if (!sched_list[i]->update()) {
			Logger::log(Logger::Error)
				<< "FBSched error: failed to trigger component #" << i
				<< " '" << sched_list[i]->getName() << "'" << endlog();
			goto out_fail;
		}
	}

 out_fail:
	return;
}

void FBSched::cleanupHook()
{
	sched_list.clear();
}

void FBSched::displaySchedList()
{
	if( isRunning() ) {
		cout << endl;
		cout << "The current order of scheduling is : "<< endl;
		for(unsigned int i=0; i<sched_list.size(); i++) {
			cout << sched_list[i]->getName() << endl;
		}
		cout << endl;
	} else {
		cout << endl;
		cout << "FBSched component must be running to provide a sched_list"<< endl;
		cout << endl;
	}
}

ORO_CREATE_COMPONENT_LIBRARY()
ORO_LIST_COMPONENT_TYPE( FBSched )

/**************************************************************************
 *  You may redistribute this software and/or modify it under either the  *
 *  terms of the GNU Lesser General Public License version 2.1 (LGPLv2.1  *
 *  <http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html>) or (at your *
 *  discretion) of the Modified BSD License:                              *
 *  Redistribution and use in source and binary forms, with or without    *
 *  modification, are permitted provided that the following conditions    *
 *  are met:                                                              *
 *  1. Redistributions of source code must retain the above copyright     *
 *  notice, this list of conditions and the following disclaimer.         *
 *  2. Redistributions in binary form must reproduce the above copyright  *
 *  notice, this list of conditions and the following disclaimer in the   *
 *  documentation and/or other materials provided with the distribution.  *
 *  3. The name of the author may not be used to endorse or promote       *
 *  products derived from this software without specific prior written    *
 *  permission.                                                           *
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR  *
 *  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED        *
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE    *
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,*
 *  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES    *
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS       *
 *  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) *
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,   *
 *  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING *
 *  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE    *
 *  POSSIBILITY OF SUCH DAMAGE.                                           *
 *                                                                        *
 **************************************************************************/
