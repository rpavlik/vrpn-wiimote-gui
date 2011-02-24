#ifndef QWIIMOTEWIDGET_H
#define QWIIMOTEWIDGET_H

#include <QGraphicsView>
#include <QGraphicsSvgItem>

class QWiimoteWidget : public QGraphicsView
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
protected:
	virtual void resizeEvent(QResizeEvent * event);
private:
	static bool _loaded_resources;
	QGraphicsSvgItem * _wiimote;
};

#endif // QWIIMOTEWIDGET_H
