#ifndef _VRPN_CONNECTIONPTR_H_
#define _VRPN_CONNECTIONPTR_H_

#include <vrpn_Connection.h>

class vrpn_ConnectionPtr {
	public:
		explicit vrpn_ConnectionPtr(vrpn_Connection * c = NULL) : _p(c) {
			if (_p) {
				_p->addReference();
			}
		}

		vrpn_ConnectionPtr(vrpn_ConnectionPtr const& other) : _p(other._p) {
			if (_p) {
				_p->addReference();
			}
		}

		vrpn_ConnectionPtr & operator=(vrpn_ConnectionPtr const& other) {
			if (this == &other) {
				/// self-assignment is a no-op
				return *this;
			}
			reset();
			if (other._p) {
				_p = other._p;
				_p->addReference();
			}
			return *this;
		}

		~vrpn_ConnectionPtr() {
			reset();
		}

		bool valid() const {
			return (_p != NULL);
		}

		void reset() {
			if (_p) {
				_p->removeReference();
			}
			_p = NULL;
		}

		vrpn_Connection * get() const {
			return _p;
		}
		
		operator vrpn_Connection*() const {
			return _p;
		}

		vrpn_Connection & operator*() {
			return *_p;
		}

		vrpn_Connection const& operator*() const{
			return *_p;
		}

		vrpn_Connection * operator->() {
			return _p;
		}

		vrpn_Connection const* operator->() const{
			return _p;
		}

		static vrpn_ConnectionPtr create_server_connection(int port = vrpn_DEFAULT_LISTEN_PORT_NO,
			const char * local_in_logfile_name = NULL,
			const char * local_out_logfile_name = NULL,
			const char * NIC_NAME = NULL) {
				return vrpn_ConnectionPtr(
					vrpn_create_server_connection(port, local_in_logfile_name, local_out_logfile_name, NIC_NAME),
					false);						
		}
	private:
		vrpn_ConnectionPtr(vrpn_Connection * c, bool needsAddRef) : _p(c) {
			if (_p && needsAddRef) {
				_p->addReference();
			}
		}
		vrpn_Connection * _p;
};

#endif // _VRPN_CONNECTIONPTR_H_