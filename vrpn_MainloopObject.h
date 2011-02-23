#ifndef _VRPN_MAINLOOPOBJECT_H_
#define _VRPN_MAINLOOPOBJECT_H_

#define VRPNOBJECT_VERBOSE

#include "vrpn_ConnectionPtr.h"

#include <vrpn_Connection.h>

#ifdef VRPNOBJECT_VERBOSE
#include <iostream>
#endif
#include <stdexcept>

/// An interface for all VRPN objects that have a "mainloop" method.
/// Not instantiated directly: use vrpn_MainloopObject::wrap() to create one
///
class vrpn_MainloopObject {
	public:
		struct CannotWrapNullPointerIntoMainloopObject : public std::logic_error {
			CannotWrapNullPointerIntoMainloopObject() : std::logic_error("Cannot wrap a null pointer into a vrpn_MainloopObject!") {}
		};
		virtual ~vrpn_MainloopObject() {}
		virtual void mainloop() = 0;

		static vrpn_MainloopObject * wrap(vrpn_ConnectionPtr o);

		template<class T>
		static vrpn_MainloopObject * wrap(T * o);

		template<class T>
		static vrpn_MainloopObject * wrap(T * o, bool owner);
	protected:
		vrpn_MainloopObject() {}
};

namespace detail {
	template<class T>
	class TypedMainloopObject : public vrpn_MainloopObject {
	public:
		TypedMainloopObject(T * o, bool do_delete = true) :
			_instance(o),
			_do_delete(do_delete) {
				if (!o) {
					throw vrpn_MainloopObject::CannotWrapNullPointerIntoMainloopObject();
				}
	#ifdef VRPNOBJECT_VERBOSE
				std::cout << "Wrapping vrpn object " << o << std::endl;
	#endif
			}
		virtual ~TypedMainloopObject() {
			if (_do_delete) {
			   delete _instance;
	#ifdef VRPNOBJECT_VERBOSE
			   std::cout << "Deleted contained vrpn object " << _instance << std::endl;
			} else {
				std::cout << "NOT deleting contained vrpn object " << _instance << std::endl;
	#endif
			}
		}
		

        virtual void mainloop() {
            _instance->mainloop();
        }

    private:
        T * _instance;
        bool _do_delete;
    };

	class ConnectionPtrObject : public vrpn_MainloopObject {
		public:
			explicit ConnectionPtrObject(vrpn_ConnectionPtr o) : _instance(o) {
				if (!o.valid()) {
					throw vrpn_MainloopObject::CannotWrapNullPointerIntoMainloopObject();
				}
			}
			virtual void mainloop() {
				_instance->mainloop();
			}
		private:
			vrpn_ConnectionPtr _instance;
	};

} // end of namespace detail

inline vrpn_MainloopObject * vrpn_MainloopObject::wrap(vrpn_ConnectionPtr o) {
	return new detail::ConnectionPtrObject(o);
}

template<class T>
inline vrpn_MainloopObject * vrpn_MainloopObject::wrap(T * o) {
	return new detail::TypedMainloopObject<T>(o, true);
}

template<class T>
inline vrpn_MainloopObject * vrpn_MainloopObject::wrap(T * o, bool owner) {
	return new detail::TypedMainloopObject<T>(o, owner);
}

/* Disabled for now because we do need to delete connection objects we create ourselves */
template<>
inline vrpn_MainloopObject * vrpn_MainloopObject::wrap<vrpn_Connection>(vrpn_Connection * o) {
    // Connection objects auto-delete
#ifdef VRPNOBJECT_VERBOSE
	std::cout << "Creating a non-deleting wrapper for the vrpn_Connection instance " << o << std::endl;
#endif
    return new detail::TypedMainloopObject<vrpn_Connection>(o, false);
}

#endif