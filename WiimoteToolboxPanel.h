#ifndef WIIMOTETOOLBOXPANEL_H
#define WIIMOTETOOLBOXPANEL_H

#include "wiimotewand.h"

#include <QString>
#include <QSharedPointer>
#include <QWidget>

class QWiimoteWidget;

namespace Ui {
	class WiimotePanel;
}

class WiimoteToolboxPanel : public QWidget {
		Q_OBJECT
	public:
		explicit WiimoteToolboxPanel(QWidget *parent = 0);
		~WiimoteToolboxPanel();
	public slots:
		void setBattery(float battery);
		void connected(QSharedPointer<WiimoteWand> wand);
		void disconnected();
		void buttonUpdate(int button, bool state);
		void wiimoteNumber(int num);
	private:
		Ui::WiimotePanel * ui;
		QWiimoteWidget * wiiWidget;
};

#endif // WIIMOTETOOLBOXPANEL_H
