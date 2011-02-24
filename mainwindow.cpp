#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "wiimotewand.h"

#include <QDateTime>

MainWindow::MainWindow(QSharedPointer<WiimoteWand> wand, QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	_wmPanel(new WiimoteToolboxPanel),
	_wand(wand) {
	ui->setupUi(this);
	connect(ui->connect, SIGNAL(clicked()), _wand.data(), SLOT(connect()));
	connect(ui->disconnect, SIGNAL(clicked()), _wand.data(), SLOT(disconnect()));

	connect(_wand.data(), SIGNAL(startingConnectionAttempt()), this, SLOT(disableAllDuringConnectionAttempt()));
	connect(_wand.data(), SIGNAL(connected()), this, SLOT(updateButtons()));
	connect(_wand.data(), SIGNAL(connected()), this, SLOT(connectedWiimote()));
	connect(_wand.data(), SIGNAL(disconnected()), this, SLOT(updateButtons()));
	connect(_wand.data(), SIGNAL(disconnected()), this, SLOT(handleDisconnect()));
	connect(_wand.data(), SIGNAL(connectionFailed(QString)), this, SLOT(handleMessages(QString)));
	connect(_wand.data(), SIGNAL(statusUpdate(QString)), this, SLOT(handleMessages(QString)));



	connect(_wand.data(), SIGNAL(batteryUpdate(float)), _wmPanel.data(), SLOT(setBattery(float)));
	connect(_wand.data(), SIGNAL(disconnected()), _wmPanel.data(), SLOT(disconnected()));

	handleMessages(QString("Application started"));
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::connectedWiimote() {
	ui->toolBox->addItem(_wmPanel.data(), _wand->deviceName());
	_wmPanel->connected(_wand);
}
void MainWindow::handleDisconnect() {
	ui->toolBox->removeItem(1);
}

void MainWindow::disableAllDuringConnectionAttempt() {
	ui->connect->setEnabled(false);
	ui->disconnect->setEnabled(false);
}

void MainWindow::updateButtons() {
	bool connected = _wand->isConnected();
	ui->connect->setEnabled(!connected);
	ui->disconnect->setEnabled(connected);
}

void MainWindow::handleMessages(QString message) {
	ui->textBrowser->append(QDateTime::currentDateTime().toString() + QString(": ") + message);
}

