#include <vrpn_Connection.h>

class VRPNConnectionPtr {
	public:
		explicit VRPNConnectionPtr(vrpn_Connection * c = NULL) : _p(c) {
			if (_p) {
				_p->addReference();
			}
		}

		VRPNConnectionPtr(VRPNConnectionPtr const& other) : _p(other._p) {
			if (_p) {
				_p->addReference();
			}
		}

		VRPNConnectionPtr & operator=(VRPNConnectionPtr const& other) {
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

		~VRPNConnectionPtr() {
			reset();
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

		static VRPNConnectionPtr create_server_connection(int port = vrpn_DEFAULT_LISTEN_PORT_NO,
			const char * local_in_logfile_name = NULL,
			const char * local_out_logfile_name = NULL,
			const char * NIC_NAME = NULL) {
				return VRPNConnectionPtr(
					vrpn_create_server_connection(port, local_in_logfile_name, local_out_logfile_name, NIC_NAME),
					false);						
		}
	private:
		VRPNConnectionPtr(vrpn_Connection * c, bool needsAddRef) : _p(c) {
			if (_p && needsAddRef) {
				_p->addReference();
			}
		}
		vrpn_Connection * _p;
};