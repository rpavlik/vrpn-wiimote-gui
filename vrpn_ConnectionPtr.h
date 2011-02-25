#ifndef _VRPN_CONNECTIONPTR_H_
#define _VRPN_CONNECTIONPTR_H_

#include <vrpn_Connection.h>

/// A shared pointer class for holding on to vrpn_Connections, using the
/// existing "intrusive reference counting" automatically.
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

		vrpn_Connection const& operator*() const {
			return *_p;
		}

		vrpn_Connection * operator->() {
			return _p;
		}

		vrpn_Connection const* operator->() const {
			return _p;
		}

		///@todo this is a hack to make safe bool compile on vc9 - what am I doing wrong?
		bool operator!() const {
			return !_p;
		}

		/// @name Safe Bool Idiom
		/// @{
		typedef vrpn_Connection* vrpn_ConnectionPtr::*unspecified_bool_type;
		operator unspecified_bool_type() const {
			return (_p) ?
			       &vrpn_ConnectionPtr::_p : NULL;
		}
		/// @}

		/// Use this function, rather than vrpn_create_server_connection()
		static vrpn_ConnectionPtr create_server_connection(int port = vrpn_DEFAULT_LISTEN_PORT_NO,
		        const char * local_in_logfile_name = NULL,
		        const char * local_out_logfile_name = NULL,
		        const char * NIC_NAME = NULL) {
			return vrpn_ConnectionPtr(
			           vrpn_create_server_connection(port, local_in_logfile_name, local_out_logfile_name, NIC_NAME),
			           false);
		}

		static vrpn_ConnectionPtr create_server_connection(
		    const char * cname,
		    const char * local_in_logfile_name = NULL,
		    const char * local_out_logfile_name = NULL) {
			return vrpn_ConnectionPtr(
			           vrpn_create_server_connection(cname, local_in_logfile_name, local_out_logfile_name),
			           false);
		}

	private:
		vrpn_ConnectionPtr(vrpn_Connection * c, bool needsAddRef) : _p(c) {
			if (_p && needsAddRef) {
				_p->addReference();
			}
		}
		vrpn_Connection * _p;
		
		void this_type_does_not_support_comparisons() {}
};

template <typename T>
bool operator!=(const T& lhs, const vrpn_ConnectionPtr& rhs) {
	rhs.this_type_does_not_support_comparisons();
	return false;
}
template <typename T>
bool operator==(const T& lhs, const vrpn_ConnectionPtr& rhs) {
	rhs.this_type_does_not_support_comparisons();
	return false;
}
template <typename T>
bool operator!=(const vrpn_ConnectionPtr& lhs, const T& rhs) {
	lhs.this_type_does_not_support_comparisons();
	return false;
}
template <typename T>
bool operator==(const vrpn_ConnectionPtr& lhs, const T& rhs) {
	lhs.this_type_does_not_support_comparisons();
	return false;
}

#endif // _VRPN_CONNECTIONPTR_H_
