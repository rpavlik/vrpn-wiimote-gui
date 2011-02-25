#include "vrpn_QMainloopContainer.h"

#include <QMutexLocker>

vrpn_QMainloopContainer::vrpn_QMainloopContainer(int msInterval, QObject *parent) :
	QObject(parent),
	_msInterval(msInterval) {
}

vrpn_QMainloopContainer::~vrpn_QMainloopContainer() {
	clear();
}

void vrpn_QMainloopContainer::add(vrpn_MainloopObject * o) {
	if (!o) {
		return;
	}
	{
		QMutexLocker locker(&_vectorMutex);
		_vrpn.add(o);
	}
	emit added();
}

void vrpn_QMainloopContainer::clear() {
	stop();
	{
		QMutexLocker locker(&_vectorMutex);
		_vrpn.clear();
	}
	emit cleared();
}

void vrpn_QMainloopContainer::start() {
	if (!_timer.isNull()) {
		return;
	}
	QSharedPointer<QTimer> tmr(new QTimer(this));
	_timer = tmr;
	connect(_timer.data(), SIGNAL(timeout()), this, SLOT(mainloop()));

	emit started();
	_timer->start(_msInterval);
}

void vrpn_QMainloopContainer::mainloop() {
	emit beforeMainloop();
	{
		QMutexLocker locker(&_vectorMutex);
		_vrpn.mainloop();
	}
	emit afterMainloop();
}

void vrpn_QMainloopContainer::stop() {
	if (_timer.isNull()) {
		return;
	}
	_timer->stop();
	_timer.clear();

	emit stopped();
}
