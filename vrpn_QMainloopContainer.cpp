#include "vrpn_QMainloopContainer.h"

#include <QMutexLocker>

vrpn_QMainloopContainer::vrpn_QMainloopContainer(QObject *parent) :
    QObject(parent)
{
}

vrpn_QMainloopContainer::~vrpn_QMainloopContainer() {
    clear();
}

void vrpn_QMainloopContainer::add(vrpn_MainloopObject * o) {
    if (!o) {
        return;
    }
    QMutexLocker locker(&_vectorMutex);
    _vrpn.add(o);
}

void vrpn_QMainloopContainer::clear() {
	stop();
	QMutexLocker locker(&_vectorMutex);
	_vrpn.clear();
}   

void vrpn_QMainloopContainer::start() {
    if (!_timer.isNull()) {
        return;
    }
    QSharedPointer<QTimer> tmr(new QTimer(this));
    _timer = tmr;
    connect(_timer.data(), SIGNAL(timeout()), this, SLOT(mainloop()));

    _timer->start(20);
}

void vrpn_QMainloopContainer::mainloop() {
    QMutexLocker locker(&_vectorMutex);
    _vrpn.mainloop();
}

void vrpn_QMainloopContainer::stop() {
    if (_timer.isNull()) {
        return;
    }
    _timer->stop();
    _timer.clear();
}
