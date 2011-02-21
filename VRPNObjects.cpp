#include "VRPNObjects.h"

#include "vrpn_BaseClass.h"

#include <QMutexLocker>

VRPNObjects::VRPNObjects(QObject *parent) :
    QObject(parent)
{
}

VRPNObjects::~VRPNObjects() {
    QMutexLocker locker(&_vectorMutex);
    /// Delete in reverse order
    for (unsigned int i = _vrpn.size() - 1; i >= 0; --i) {
        delete _vrpn[i];
        _vrpn[i] = NULL;
    }
}

void VRPNObjects::add(VRPNObject * o) {
    if (o == NULL) {
        return;
    }
    QMutexLocker locker(&_vectorMutex);
    _vrpn.push_back(o);
}

void VRPNObjects::mainloop() {
    QMutexLocker locker(&_vectorMutex);
    for (unsigned int i = 0; i < _vrpn.size(); ++i) {
        if (_vrpn[i]) {
            _vrpn[i]->mainloop();
        }
    }
}
