#include "WiimoteToolboxPanel.h"
#include "ui_wiimotepanel.h"

#include "QWiimoteWidget/QWiimoteWidget.h"


WiimoteToolboxPanel::WiimoteToolboxPanel(QWidget * parent) :
	QWidget(parent),
	ui(new Ui::WiimotePanel) {
	ui->setupUi(this);
	wiiWidget = new QWiimoteWidget(this);
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
