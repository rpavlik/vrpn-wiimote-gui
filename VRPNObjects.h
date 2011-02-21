#ifndef VRPNOBJECTS_H
#define VRPNOBJECTS_H

#include <QObject>
#include <QSharedPointer>
#include <QMutex>
#include <vector>

class vrpn_BaseClass;
class vrpn_Connection;

class VRPNObjects : public QObject
{
    Q_OBJECT
public:
    explicit VRPNObjects(QObject *parent = 0);
    ~VRPNObjects();

    void add(vrpn_BaseClass * o);
    void add(vrpn_Connection * o);
    void remove(vrpn_BaseClass * o);
    void remove(vrpn_Connection * o);

signals:

public slots:
    void mainloop();
private:
    QMutex _vectorMutex;
    std::vector<vrpn_Connection *> _connections;
    std::vector<vrpn_BaseClass *> _vrpn;
};

#endif // VRPNOBJECTS_H
