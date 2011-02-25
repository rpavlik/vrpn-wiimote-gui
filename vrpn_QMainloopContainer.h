#ifndef _VRPN_QMAINLOOPCONTAINER_H_
#define _VRPN_QMAINLOOPCONTAINER_H_

#include "vrpn_MainloopContainer.h"

#include <QObject>
#include <QTimer>
#include <QSharedPointer>
#include <QMutex>

/// A class supporting the interaction of Qt and the VRPN mainloop:
/// uses vrpn_MainloopContainer to hold arbitrary vrpn objects and
/// mainloop them at a regular basis.
class vrpn_QMainloopContainer : public QObject {
		Q_OBJECT
	public:
		explicit vrpn_QMainloopContainer(int msInterval = 20, QObject *parent = 0);
		~vrpn_QMainloopContainer();

		void add(vrpn_MainloopObject * o);

		template<class T>
		void add(T o) {
			add(vrpn_MainloopObject::wrap(o));
		}

	signals:
		void added();
		void started();
		void stopped();
		void beforeMainloop();
		void afterMainloop();
		void cleared();

	public slots:
		void start();
		void mainloop();
		void stop();
		void clear();

	private:
		int _msInterval;
		QMutex _vectorMutex;
		QSharedPointer<QTimer> _timer;
		vrpn_MainloopContainer _vrpn;
};

#endif // _VRPN_QMAINLOOPCONTAINER_H_
