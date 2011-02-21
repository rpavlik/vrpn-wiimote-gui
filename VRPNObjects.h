#ifndef VRPNOBJECTS_H
#define VRPNOBJECTS_H

#include <QObject>
#include <QSharedPointer>
#include <QMutex>
#include <vector>

class vrpn_BaseClass;
class vrpn_Connection;

class VRPNObject
{
public:

    virtual ~VRPNObject() {}
    virtual void mainloop() = 0;
protected:
    VRPNObject() {}
};

template<class T>
class TypedVRPNObject : public VRPNObject{
public:
    TypedVRPNObject(T * o) :
        _instance(o) { }
    virtual ~TypedVRPNObject() {
        delete _instance;
    }

    virtual void mainloop() {
        _instance->mainloop();
    }

private:
    T * _instance;
};

template<class T>
VRPNObject * wrapVRPNObject(T * o) {
    return new TypedVRPNObject<T>(o);
}

class VRPNObjects : public QObject
{
    Q_OBJECT
public:
    explicit VRPNObjects(QObject *parent = 0);
    ~VRPNObjects();

    template<class T>
    void add(T * o) {
        add(wrapVRPNObject(o));
    }

    void add(VRPNObject * o);

signals:

public slots:
    void mainloop();
private:
    QMutex _vectorMutex;
    std::vector<VRPNObject *> _vrpn;
};

#endif // VRPNOBJECTS_H
