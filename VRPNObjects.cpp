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
        _vrpn.erase(i);
    }
}

void VRPNObjects::add(vrpn_BaseClass * o) {
    if (o == NULL) {
        return;
    }
    QMutexLocker locker(&_vectorMutex);
    _vrpn.push_back(o);
}

void VRPNObjects::add(vrpn_Connection * o) {
    if (o == NULL) {
        return;
    }
    QMutexLocker locker(&_vectorMutex);
    _connections.push_back(o);
}

void VRPNObjects::remove(vrpn_BaseClass * o) {
    if (o == NULL) {
        return;
    }
    QMutexLocker locker(&_vectorMutex);
    int num = -1;
    for (unsigned int i = 0; i < _vrpn.size(); ++i) {
        if (_vrpn[i] == o) {
            num = i;
        }
    }
    if (num != -1) {
        _vrpn.erase(num);
    }
}

void VRPNObjects::remove(vrpn_Connection * o) {
    if (o == NULL) {
        return;
    }
    QMutexLocker locker(&_vectorMutex);
    int num = -1;
    for (unsigned int i = 0; i < _connections.size(); ++i) {
        if (_connections[i] == o) {
            num = i;
        }
    }
    if (num != -1) {
        _connections.erase(num);
    }
}

void VRPNObjects::mainloop() {
    QMutexLocker locker(&_vectorMutex);
    for (unsigned int i = 0; i < _vrpn.size(); ++i) {
        _vrpn[i]->mainloop();
    }
}
