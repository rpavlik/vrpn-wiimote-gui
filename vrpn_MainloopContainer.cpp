#include "vrpn_MainloopContainer.h"

#include <iostream>

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
    std::cout << "Clearing VRPNObjects" << std::endl;
    std::cout << "Have to delete and clear " << _vrpn.size() << std::endl;
    if (_vrpn.empty()) {
        return;
    }
    /// Delete in reverse order
    for (int i = _vrpn.size() - 1; i >= 0; --i) {
        std::cout << "Deleting index " << i << std::endl << std::flush;
        delete _vrpn[i];
        _vrpn[i] = NULL;

        std::cout << "OK deleting index " << i << std::endl << std::endl<< std::flush;
    }
    std::cout << "Done clearing"<< std::endl << std::endl<< std::flush;
    _vrpn.clear();
}

void vrpn_MainloopContainer::mainloop() {
    for (unsigned int i = 0; i < _vrpn.size(); ++i) {
        _vrpn[i]->mainloop();
    }
}
