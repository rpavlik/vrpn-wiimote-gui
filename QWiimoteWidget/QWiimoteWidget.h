#ifndef QWIIMOTEWIDGET_H
#define QWIIMOTEWIDGET_H

#include <QGraphicsView>
#include <QSvgRenderer>

class QWiimoteWidget : public QGraphicsView
{
    Q_OBJECT

public:
    explicit QWiimoteWidget(QWidget *parent = 0);
    ~QWiimoteWidget();

public slots:
	/// num is 1-4
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
protected:
	virtual void resizeEvent(QResizeEvent * event);
private:
	QGraphicsItem * _createAndAddSubitem(QString const& id);
	static bool _loaded_resources;
	QGraphicsItem * _wiimote;
	QSvgRenderer * _activated;

	QGraphicsItem * _leds[4];

	QGraphicsItem * _button1;
	QGraphicsItem * _button2;
	QGraphicsItem * _buttonA;
	QGraphicsItem * _buttonB;
	QGraphicsItem * _buttonPlus;
	QGraphicsItem * _buttonMinus;
	QGraphicsItem * _buttonHome;

	QGraphicsItem * _buttonLeft;
	QGraphicsItem * _buttonRight;
	QGraphicsItem * _buttonDown;
	QGraphicsItem * _buttonUp;

};

#endif // QWIIMOTEWIDGET_H
