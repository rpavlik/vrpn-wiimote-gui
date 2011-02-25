#ifndef _VRPN_CONNECTIONPTR_H_
#define _VRPN_CONNECTIONPTR_H_

#include <vrpn_Connection.h>

/// A shared pointer class for holding on to vrpn_Connection instances, using the
/// existing "intrusive reference counting" automatically.
class vrpn_ConnectionPtr {
	public:
		/// Explicit constructor from a non-smart connection pointer
		explicit vrpn_ConnectionPtr(vrpn_Connection * c = NULL) : _p(c) {
			if (_p) {
				_p->addReference();
			}
		}

		/// Copy constructor from smart pointer
		vrpn_ConnectionPtr(vrpn_ConnectionPtr const& other) : _p(other._p) {
			if (_p) {
				_p->addReference();
			}
		}

		/// Assignment operator from smart pointer
		vrpn_ConnectionPtr & operator=(vrpn_ConnectionPtr const& other) {
			if (this == &other || _p == other._p) {
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

		/// Assignment operator from non-smart pointer
		vrpn_ConnectionPtr & operator=(vrpn_Connection * other) {
			if (_p == other) {
				/// self-assignment is a no-op
				return *this;
			}

			reset();
			if (other) {
				_p = other;
				_p->addReference();
			}
			return *this;
		}

		/// Destructor - decrements the contained reference count, if applicable
		~vrpn_ConnectionPtr() {
			reset();
		}

		/// Clears the contained pointer and decrements the reference count, if
		/// applicable
		void reset() {
			if (_p) {
				_p->removeReference();
			}
			_p = NULL;
		}

		/// Gets the contained "non-smart" pointer. You are responsible
		/// for calling vrpn_Connection::addReference() if you want to
		/// affect connection lifetime with this pointer!
		/// (Included VRPN devices take care of this by default)
		vrpn_Connection * get() const {
			return _p;
		}

		/// @name Smart Pointer operators
		/// @{
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
		/// @}

		/// @todo this is a hack to make safe bool compile on vc9 - what am I doing wrong?
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

		/// @name Connection creation functions
		/// Use these function, rather than initializing a vrpn_ConnectionPtr with results of
		/// vrpn_create_server_connection() - this will correctly handle the default reference added
		/// by the vrpn_create_server_connection() function. Identical signatures are provided for
		/// your convenience
		/// @{
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
		/// @}

	private:
		/// Private constructor used by the connection creation functions, allowing
		/// creation of a vrpn_ConnectionPtr without increasing the reference count
		/// since the construction functions in VRPN automatically do this once.
		vrpn_ConnectionPtr(vrpn_Connection * c, bool needsAddRef) : _p(c) {
			if (_p && needsAddRef) {
				_p->addReference();
			}
		}

		/// Contained pointer
		vrpn_Connection * _p;

		/// Dummy function supporting the safe bool idiom
		void this_type_does_not_support_comparisons() {}
};

/// Equality operator for connection smart pointers
/// @relates vrpn_ConnectionPtr
inline bool operator==(const vrpn_ConnectionPtr& lhs, const vrpn_ConnectionPtr& rhs) {
	return lhs.get() == rhs.get();
}

/// Inequality operator for connection smart pointers
/// @relates vrpn_ConnectionPtr
inline bool operator!=(const vrpn_ConnectionPtr& lhs, const vrpn_ConnectionPtr& rhs) {
	return lhs.get() != rhs.get();
}

/// @name Poisoning operators for connection smart pointers
/// Supporting the safe bool idiom
/// @relates vrpn_ConnectionPtr
/// @{
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
/// @}

#endif // _VRPN_CONNECTIONPTR_H_
