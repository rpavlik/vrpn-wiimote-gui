#ifndef WIIMOTEWAND_H
#define WIIMOTEWAND_H

#include "VRPNObjects.h"

#include <QObject>
#include <QString>

class vrpn_WiiMote;
class vrpn_Connection;

class WiimoteWand : public QObject
{
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
    void connectionFailed(QString message);
    void statusUpdate(QString message);
    void disconnected();

    void batteryUpdate(float level);

public slots:
    void connect();
    void disconnect();

    void checkWiimoteDevice();
private:
    bool _connected;
    vrpn_WiiMote * _wiimote;
    vrpn_Connection * _connection;
    VRPNObjects _vrpn;

public:
    void setBattery(float level);
};

#endif // WIIMOTEWAND_H
