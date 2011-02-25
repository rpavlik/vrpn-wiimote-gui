#ifndef _VRPN_MAINLOOPCONTAINER_H_
#define _VRPN_MAINLOOPCONTAINER_H_

#include "vrpn_MainloopObject.h"

#include <vector>

/// A container that holds and owns one or more VRPN objects,
class vrpn_MainloopContainer {
	public:
		/// Constructor
		vrpn_MainloopContainer() {}
		/// Destructor: invokes clear()
		~vrpn_MainloopContainer();

		/// Clear internal structure holding objects, deleting them
		/// in reverse order of their addition.
		void clear();

		/// Add an object wrapped by vrpn_MainloopObject.
		void add(vrpn_MainloopObject * o);

		/// Template method to automatically wrap objects
		/// with vrpn_MainloopObject before adding them.
		template<class T>
		void add(T o) {
			add(vrpn_MainloopObject::wrap(o));
		}

		/// Runs mainloop on all contained objects, in the order
		/// that they were added.
		void mainloop();

	private:
		std::vector<vrpn_MainloopObject *> _vrpn;
};

#endif // _VRPN_MAINLOOPCONTAINER_H_
