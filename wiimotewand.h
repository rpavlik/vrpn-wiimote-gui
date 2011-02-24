#ifndef WIIMOTEWAND_H
#define WIIMOTEWAND_H

#include "vrpn_QMainloopContainer.h"

#include <QObject>
#include <QString>

class vrpn_WiiMote;

class WiimoteWand : public QObject {
		Q_OBJECT
	public:
		explicit WiimoteWand(QObject *parent = 0);

		bool isConnected() const {
			return _connected;
		}

		QString deviceName() const;

	signals:
		void startingConnectionAttempt();
		void connected();
		void wiimoteNumber(int num); // in 1-4
		void connectionFailed(QString message);
		void statusUpdate(QString message);
		void disconnected();

		void batteryUpdate(float level);
		void buttonUpdate(int button, bool state);

	public slots:
		void connect();
		void disconnect();

		void checkWiimoteDevice();
	private:
		bool _connected;
		vrpn_WiiMote * _wiimote;
		vrpn_QMainloopContainer _vrpn;

	public:
		void setBattery(float level);
		void setButton(int button, bool state);
};

#endif // WIIMOTEWAND_H
