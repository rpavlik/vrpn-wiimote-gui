#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QSharedPointer>

namespace Ui {
	class MainWindow;
}

class WiimoteWand;

class MainWindow : public QMainWindow {
		Q_OBJECT

	public:
		explicit MainWindow(QSharedPointer<WiimoteWand> wand, QWidget *parent = 0);
		~MainWindow();

	public slots:
		void setBattery(float battery);
		void disableAllDuringConnectionAttempt();
		void handleDisconnect();
		void updateButtons();
		void handleMessages(QString message);
	private:
		Ui::MainWindow *ui;
		QSharedPointer<WiimoteWand> _wand;

};

#endif // MAINWINDOW_H
