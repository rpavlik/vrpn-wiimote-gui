#ifndef QWIIMOTEWIDGET_H
#define QWIIMOTEWIDGET_H

#include <QWidget>
#include <QGraphicsScene>

namespace Ui {
    class QWiimoteWidget;
}

class QWiimoteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QWiimoteWidget(QWidget *parent = 0);
    ~QWiimoteWidget();

public slots:
	void setWiimoteLED(int num, bool state);
	void setAButton(bool state);
	void setBButton(bool state);
	void setUpButton(bool state);
	void setDownButton(bool state);
	void setLeftButton(bool state);
	void setRightButton(bool state);
	void set1Button(bool state);
	void set2Button(bool state);
	void setHomeButton(bool state);
	void setPlusButton(bool state);
	void setMinusButton(bool state);

private:
	Ui::QWiimoteWidget *ui;
	QGraphicsScene * _scene;
};

#endif // QWIIMOTEWIDGET_H
