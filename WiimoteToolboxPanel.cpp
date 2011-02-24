#include "WiimoteToolboxPanel.h"
#include "ui_wiimotepanel.h"

#include "QWiimoteWidget/QWiimoteWidget.h"


WiimoteToolboxPanel::WiimoteToolboxPanel(QWidget * parent) :
	QWidget(parent),
	ui(new Ui::WiimotePanel) {
	ui->setupUi(this);
	wiiWidget = ui->wiiWidget;
}
WiimoteToolboxPanel::~WiimoteToolboxPanel() {
	delete ui;
}
void WiimoteToolboxPanel::connected(QSharedPointer<WiimoteWand> wand) {

	ui->deviceName->setText(wand->deviceName());
}
void WiimoteToolboxPanel::disconnected() {
	ui->batteryBar->setValue(0);
	ui->batteryBar->setFormat("Unknown");
	ui->deviceName->setText(QString(""));
}

void WiimoteToolboxPanel::setBattery(float battery) {
	ui->batteryBar->setFormat("%p%");
	ui->batteryBar->setValue(static_cast<int>(battery * 100));
}

void WiimoteToolboxPanel::buttonUpdate(int button, bool state) {
	switch (button) {
	case 0:
		wiiWidget->setHomeButton(state);
		break;
	case 1:
		wiiWidget->set1Button(state);
		break;
	case 2:
		wiiWidget->set2Button(state);
		break;
	case 3:
		wiiWidget->setAButton(state);
		break;
	case 4:
		wiiWidget->setBButton(state);
		break;
	case 5:
		wiiWidget->setMinusButton(state);
		break;
	case 6:
		wiiWidget->setPlusButton(state);
		break;
	case 7:
		wiiWidget->setLeftButton(state);
		break;
	case 8:
		wiiWidget->setRightButton(state);
		break;
	case 9:
		wiiWidget->setDownButton(state);
		break;
	case 10:
		wiiWidget->setUpButton(state);
		break;
	default:
		break;
	}
}

void WiimoteToolboxPanel::wiimoteNumber(int num) {
	for (int i = 1; i <=4; ++i) {
		wiiWidget->setWiimoteLED(i, i == num);
	}
}
