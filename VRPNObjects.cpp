#include "VRPNObjects.h"

#include "vrpn_BaseClass.h"

#include <QMutexLocker>

#include <iostream>

VRPNObjects::VRPNObjects(QObject *parent) :
    QObject(parent)
{
}

VRPNObjects::~VRPNObjects() {
    clear();
}

void VRPNObjects::_add(VRPNObjects::VRPNObject * o) {
    if (o == NULL) {
        return;
    }
    QMutexLocker locker(&_vectorMutex);
    _vrpn.push_back(o);
}

void VRPNObjects::clear() {
    std::cout << "Clearing VRPNObjects" << std::endl;
    stop();
    QMutexLocker locker(&_vectorMutex);
    std::cout << "Have to delete and clear " << _vrpn.size() << std::endl;
    if (_vrpn.empty()) {
        return;
    }
    /// Delete in reverse order
    for (unsigned int i = _vrpn.size() - 1; i >= 0; --i) {
        delete _vrpn[i];
        _vrpn[i] = NULL;
    }
    _vrpn.clear();
}

void VRPNObjects::start() {
    if (!_timer.isNull()) {
        return;
    }
    QSharedPointer<QTimer> tmr(new QTimer(this));
    _timer = tmr;
    connect(_timer.data(), SIGNAL(timeout()), this, SLOT(mainloop()));

    _timer->start(20);
}

void VRPNObjects::mainloop() {
    QMutexLocker locker(&_vectorMutex);
    for (unsigned int i = 0; i < _vrpn.size(); ++i) {
        if (_vrpn[i]) {
            _vrpn[i]->mainloop();
        }
    }
}

void VRPNObjects::stop() {
    if (_timer.isNull()) {
        return;
    }
    _timer->stop();
    _timer.clear();
}
