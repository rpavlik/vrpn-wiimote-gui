#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "wiimotewand.h"
#include "WiimoteToolboxPanel.h"

#include <QMainWindow>
#include <QString>
#include <QSharedPointer>

namespace Ui {
	class MainWindow;
}


class MainWindow : public QMainWindow {
		Q_OBJECT

	public:
		explicit MainWindow(QSharedPointer<WiimoteWand> wand, QWidget *parent = 0);
		~MainWindow();

	public slots:
		void disableAllDuringConnectionAttempt();
		void handleDisconnect();
		void connectedWiimote();
		void updateButtons();
		void handleMessages(QString message);
	private:
		Ui::MainWindow *ui;
		QSharedPointer<WiimoteToolboxPanel> _wmPanel;
		QSharedPointer<WiimoteWand> _wand;

};

#endif // MAINWINDOW_H
