#include <QtGui/QApplication>
#include "mainwindow.h"
#include "wiimotewand.h"

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	QSharedPointer<WiimoteWand> wand(new WiimoteWand);
	MainWindow w(wand);
	w.show();

	return a.exec();
}
