#ifndef _VRPN_QMAINLOOPCONTAINER_H_
#define _VRPN_QMAINLOOPCONTAINER_H_

#include "vrpn_MainloopContainer.h"

#include <QObject>
#include <QTimer>
#include <QSharedPointer>
#include <QMutex>

class vrpn_QMainloopContainer : public QObject {
		Q_OBJECT
	public:
		explicit vrpn_QMainloopContainer(QObject *parent = 0);
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
		QMutex _vectorMutex;
		QSharedPointer<QTimer> _timer;
		vrpn_MainloopContainer _vrpn;
};

#endif // _VRPN_QMAINLOOPCONTAINER_H_
