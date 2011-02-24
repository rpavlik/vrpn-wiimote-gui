#include "wiimotewand.h"
#include "vrpn_ConnectionPtr.h"

#include <vrpn_Connection.h>
#include <vrpn_Analog.h>
#include <vrpn_Button.h>
#include <vrpn_WiiMote.h>

#include <iostream>


static void VRPN_CALLBACK handle_wiimote(void* userdata, const vrpn_ANALOGCB a) {
	static_cast<WiimoteWand*>(userdata)->setBattery(a.channel[0]);
}
static void VRPN_CALLBACK handle_button(void *userdata,
										const vrpn_BUTTONCB info) {
	static_cast<WiimoteWand*>(userdata)->setButton(info.button, static_cast<bool>(info.state));
}


static const char WIIMOTE_NAME[] = "WiiMote0";


WiimoteWand::WiimoteWand(QObject *parent) :
	QObject(parent),
	_connected(false),
	_timesChecked(0) {
}

QString WiimoteWand::deviceName() const {
	return QString(WIIMOTE_NAME);
}

void WiimoteWand::connect() {
	disconnect();
	_vrpn.clear();

	emit startingConnectionAttempt();
	emit statusUpdate(QString("Creating server connection..."));
	vrpn_ConnectionPtr cnx(vrpn_ConnectionPtr::create_server_connection());
	if (!cnx) {
		emit connectionFailed(QString("Could not create connection!"));
	}
	_vrpn.add(cnx);

	emit statusUpdate(QString("Creating Wiimote device object..."));
	_wiimote = new vrpn_WiiMote(WIIMOTE_NAME, cnx, 0, 0, 0, 1);
	if (!_wiimote) {
		emit connectionFailed(QString("Creation of wiimote object failed!"));
		return;
	}
	emit wiimoteNumber(1);

	_vrpn.add(_wiimote);
#ifdef vrpn_THREADS_AVAILABLE
	_timesChecked = 0;
	emit statusUpdate(QString("Waiting for Wiimote to connect..."));
	QTimer::singleShot(50, this, SLOT(checkWiimoteDeviceInit()));
#else
	if (!wm->isValid()) {
		emit connectionFailed(QString("Connection to wiimote failed!"));
		return;
	}
	checkWiimoteDeviceInit();
#endif

}

void WiimoteWand::disconnect() {
	//if (_connected) {
		_vrpn.stop();
		_vrpn.clear();
		_wiimote = NULL;
		_connected = false;
		emit disconnected();
	//}
}

void WiimoteWand::checkWiimoteDeviceRuntime() {
	if (!_wiimote) {
		return;
	}
	if (!_wiimote->isValid()) {
		emit connectionFailed(QString("Lost connection to Wiimote!"));
		disconnect();
	} else {
		QTimer::singleShot(300, this, SLOT(checkWiimoteDeviceRuntime()));
	}
}


void WiimoteWand::checkWiimoteDeviceInit() {
	_vrpn.mainloop();
	if (!_wiimote->isValid()) {
#ifdef vrpn_THREADS_AVAILABLE
		_timesChecked++;
		if (_timesChecked < 12) {
			emit statusUpdate(QString("..."));
			QTimer::singleShot(300, this, SLOT(checkWiimoteDeviceInit()));
		} else {
#ifdef _WIN32
			emit connectionFailed(QString("Timed out connecting to Wiimote! Are you sure you have paired with the Wiimote?"));
#else
			emit connectionFailed(QString("Timed out connecting to Wiimote!"));
#endif
			disconnect();
		}
#endif
		return;
	}

	emit statusUpdate(QString("Creating analog device client..."));
	vrpn_ConnectionPtr cnx(static_cast<vrpn_Analog*>(_wiimote)->connectionPtr());
	vrpn_Analog_Remote * anaRem(new vrpn_Analog_Remote(WIIMOTE_NAME, cnx));
	if (!anaRem) {
		emit connectionFailed(QString("Creation of analog remote object failed!"));
		return;
	}
	_vrpn.add(anaRem);

	anaRem->register_change_handler(this, &handle_wiimote);

	emit statusUpdate(QString("Creating button device client..."));
	vrpn_Button_Remote * btnRem(new vrpn_Button_Remote(WIIMOTE_NAME, cnx));
	if (!btnRem) {
		emit connectionFailed(QString("Creation of button remote object failed!"));
		return;
	}
	_vrpn.add(btnRem);

	btnRem->register_change_handler(this, &handle_button);


	emit statusUpdate(QString("Starting VRPN mainloop..."));
	_vrpn.start();

	_connected = true;

	emit statusUpdate(QString("Connected!"));
	emit connected();

	QTimer::singleShot(300, this, SLOT(checkWiimoteDeviceRuntime()));
}

void WiimoteWand::setBattery(float level) {
	std::cout << "Got battery level " << level << std::endl;
	emit batteryUpdate(level);
}

void WiimoteWand::setButton(int button, bool state) {
	emit buttonUpdate(button, state);
}
