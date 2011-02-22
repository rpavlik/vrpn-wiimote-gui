#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "wiimotewand.h"

#include <QDateTime>

MainWindow::MainWindow(QSharedPointer<WiimoteWand> wand, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _wand(wand)
{
    ui->setupUi(this);
    connect(ui->connect, SIGNAL(clicked()), _wand.data(), SLOT(connect()));
    connect(ui->disconnect, SIGNAL(clicked()), _wand.data(), SLOT(disconnect()));
    connect(_wand.data(), SIGNAL(connected()), this, SLOT(updateButtons()));
    connect(_wand.data(), SIGNAL(disconnected()), this, SLOT(updateButtons()));
    connect(_wand.data(), SIGNAL(disconnected()), this, SLOT(handleDisconnect()));
    connect(_wand.data(), SIGNAL(connectionFailed(QString)), this, SLOT(handleMessages(QString)));
    connect(_wand.data(), SIGNAL(statusUpdate(QString)), this, SLOT(handleMessages(QString)));

    connect(_wand.data(), SIGNAL(batteryUpdate(float)), this, SLOT(setBattery(float)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setBattery(float battery) {
    ui->batteryBar->setFormat("%p%");
    ui->batteryBar->setValue(static_cast<int>(battery * 100));
}

void MainWindow::handleDisconnect() {
    ui->batteryBar->setValue(0);
    ui->batteryBar->setFormat("Unknown");
    ui->deviceName->setText(QString(""));
}

void MainWindow::disableAllDuringConnectionAttempt() {
    ui->connect->setEnabled(false);
    ui->disconnect->setEnabled(false);
}

void MainWindow::updateButtons() {
    bool connected = _wand->isConnected();
    ui->connect->setEnabled(!connected);
    ui->disconnect->setEnabled(connected);
    if (connected) {
        ui->deviceName->setText(_wand->deviceName());
    }
}

void MainWindow::handleMessages(QString message) {
    ui->textBrowser->append(QDateTime::currentDateTime().toString() + QString(": ") + message);
}

