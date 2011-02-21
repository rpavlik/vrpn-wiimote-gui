#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "VRPNObjects.h"

#include <vrpn_Connection.h>
#include <vrpn_Analog.h>
#include <vrpn_WiiMote.h>

static void VRPN_CALLBACK handle_wiimote(void* userdata, const vrpn_ANALOGCB a) {
        static_cast<MainWindow*>(userdata)->setBattery(a.channel[0]);
}

static const char WIIMOTE_NAME[] = "WiiMote0";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    vrpn_Connection * connection(vrpn_create_server_connection());
    _vrpn.add(connection);

    vrpn_WiiMote * wm(new vrpn_WiiMote(WIIMOTE_NAME, connection, 0, 0, 0, 1));
    _vrpn.add(wm);

    vrpn_Analog_Remote * anaRem(new vrpn_Analog_Remote(WIIMOTE_NAME, connection));
    _vrpn.add(anaRem);

    anaRem->register_change_handler(this, &handle_wiimote);
}

MainWindow::~MainWindow()
{
    delete ui;
}
