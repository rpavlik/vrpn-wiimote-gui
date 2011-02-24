#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QSharedPointer>

namespace Ui {
	class MainWindow;
	class WiimotePanel;
}

class WiimoteWand;

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
