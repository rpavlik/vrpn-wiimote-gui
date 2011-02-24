#ifndef WIIMOTETOOLBOXPANEL_H
#define WIIMOTETOOLBOXPANEL_H

#include "wiimotewand.h"

#include <QString>
#include <QSharedPointer>
#include <QWidget>

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
	private:
		Ui::WiimotePanel * ui;
};

#endif // WIIMOTETOOLBOXPANEL_H
