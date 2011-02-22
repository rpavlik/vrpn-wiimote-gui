#ifndef VRPNOBJECTS_H
#define VRPNOBJECTS_H

#include <QObject>
#include <QTimer>
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

    class VRPNObject
    {
    public:

        virtual ~VRPNObject() {}
        virtual void mainloop() = 0;
    protected:
        VRPNObject() {}
    };

    void clear();

private:
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
    static VRPNObject * wrapVRPNObject(T * o) {
        return new TypedVRPNObject<T>(o);
    }

    void _add(VRPNObject * o);

public:
    template<class T>
    void add(T * o) {
        _add(wrapVRPNObject(o));
    }



signals:

public slots:
    void start();
    void mainloop();
    void stop();
private:
    QMutex _vectorMutex;
    std::vector<VRPNObject *> _vrpn;
    QSharedPointer<QTimer> _timer;


};

#endif // VRPNOBJECTS_H
