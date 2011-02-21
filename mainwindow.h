#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "VRPNObjects.h"

#include <QMainWindow>
#include <QSharedPointer>

namespace Ui {
    class MainWindow;
}

class VRPNObjects;

class vrpn_Analog_Remote;
class vrpn_Connection;
class vrpn_WiiMote;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setBattery(float battery);

public slots:

private:
    Ui::MainWindow *ui;

    VRPNObjects _vrpn;
};

#endif // MAINWINDOW_H
