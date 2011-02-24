#include "vrpn_MainloopContainer.h"

vrpn_MainloopContainer::~vrpn_MainloopContainer() {
	clear();
}

void vrpn_MainloopContainer::add(vrpn_MainloopObject* o) {
	if (!o) {
		return;
	}
	_vrpn.push_back(o);
}

void vrpn_MainloopContainer::clear() {
	if (_vrpn.empty()) {
		return;
	}
	/// Delete in reverse order
	for (int i = _vrpn.size() - 1; i >= 0; --i) {
		delete _vrpn[i];
		_vrpn[i] = NULL;
	}
	_vrpn.clear();
}

void vrpn_MainloopContainer::mainloop() {
	for (unsigned int i = 0; i < _vrpn.size(); ++i) {
		_vrpn[i]->mainloop();
	}
}
