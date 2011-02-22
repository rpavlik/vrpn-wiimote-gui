#include "wiimotewand.h"

#include <vrpn_Connection.h>
#include <vrpn_Analog.h>
#include <vrpn_WiiMote.h>

#include <iostream>

static void VRPN_CALLBACK handle_wiimote(void* userdata, const vrpn_ANALOGCB a) {
        static_cast<WiimoteWand*>(userdata)->setBattery(a.channel[0]);
}


static const char WIIMOTE_NAME[] = "WiiMote0";


WiimoteWand::WiimoteWand(QObject *parent) :
    QObject(parent),
    _connected(false)
{
}

QString WiimoteWand::deviceName() const {
    return QString(WIIMOTE_NAME);
}

void WiimoteWand::connect() {
    disconnect();
    _vrpn.clear();

    std::cout << "Creating connection" << std::endl;
    emit startingConnectionAttempt();
    emit statusUpdate(QString("Creating server connection..."));
    _connection = vrpn_create_server_connection();
    if (!_connection) {
        emit connectionFailed(QString("Could not create connection!"));
    }
    _vrpn.add(_connection);


    emit statusUpdate(QString("Creating Wiimote device object..."));
    _wiimote = new vrpn_WiiMote(WIIMOTE_NAME, _connection, 0, 0, 0, 1);
    if (!_wiimote) {
        emit connectionFailed(QString("Creation of wiimote object failed!"));
        return;
    }

    _vrpn.add(_wiimote);
#ifdef vrpn_THREADS_AVAILABLE
    emit statusUpdate(QString("Waiting for Wiimote to connect..."));
    std::cout << "threads available, this could be annoying." << std::endl;
    QTimer::singleShot(300, this, SLOT(checkWiimoteDevice()));
#else
    if (!wm->isValid()) {
        std::cout << "wiimote device reports that it is invalid" << std::endl<< std::flush;
        emit connectionFailed(QString("Connection to wiimote failed!"));
        return;
    }
    std::cout << "wiimote device reports that it is valid" << std::endl;
    checkWiimoteDevice();
#endif



}

void WiimoteWand::disconnect() {
    if (_connected) {
        _vrpn.stop();
        _vrpn.clear();
        _connected = false;
        emit disconnected();
    }
}

void WiimoteWand::checkWiimoteDevice() {
    std::cout << "Checking wiimote status" << std::endl;
    if (!_wiimote->isValid()) {
        std::cout << "Wiimote not valid!" << std::endl;

#ifdef vrpn_THREADS_AVAILABLE
        std::cout << "Will check again later" << std::endl;
        QTimer::singleShot(300, this, SLOT(checkWiimoteDevice()));
#endif
        return;
    }

    emit statusUpdate(QString("Creating device client..."));

    vrpn_Analog_Remote * anaRem(new vrpn_Analog_Remote(WIIMOTE_NAME, _connection));
    if (!anaRem) {
        emit connectionFailed(QString("Creation of analog remote object failed!"));
        return;
    }
    _vrpn.add(anaRem);

    anaRem->register_change_handler(this, &handle_wiimote);


    emit statusUpdate(QString("Starting VRPN mainloop..."));
    _vrpn.start();

    _connected = true;

    emit statusUpdate(QString("Connected!"));
    emit connected();
}

void WiimoteWand::setBattery(float level) {
    std::cout << "Got battery level " << level << std::endl;
    emit batteryUpdate(level);
}
