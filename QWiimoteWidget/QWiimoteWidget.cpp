#include "QWiimoteWidget.h"

#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QMessageBox>

#include <iostream>
#include <stdexcept>

/// Static definition
bool QWiimoteWidget::_loaded_resources = false;

static const QString WIISVG(":/wiimotewidget/full-wiimote.svg");
static const QString ACTIVESVG(":/wiimotewidget/activated.svg");

QWiimoteWidget::QWiimoteWidget(QWidget *parent) :
	QGraphicsView(parent)
{
	if (!_loaded_resources) {
		Q_INIT_RESOURCE(wiimotewidget);
		_loaded_resources = true;
	}

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	updateGeometry();

	setScene(new QGraphicsScene(this));

	QGraphicsScene *s = scene();

	_wiimote = new QGraphicsSvgItem(WIISVG);
	s->addItem(_wiimote);

	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	fitInView(_wiimote, Qt::KeepAspectRatio);

	_activated = new QSvgRenderer(ACTIVESVG, this);

	for (unsigned int i = 0; i < 4; ++i) {
		_leds[i] = _createAndAddSubitem(QString("led") + QString::number(i+1));
	}

	_button1 = _createAndAddSubitem("button1Down");
	_button2 = _createAndAddSubitem("button2Down");
	_buttonA = _createAndAddSubitem("aButtonDown");
	_buttonB = _createAndAddSubitem("bButtonDown");
	_buttonPlus = _createAndAddSubitem("plusButtonDown");
	_buttonMinus = _createAndAddSubitem("minusButtonDown");
	_buttonHome = _createAndAddSubitem("homeButtonDown");

	_buttonLeft = _createAndAddSubitem("leftButtonDown");
	_buttonRight = _createAndAddSubitem("rightButtonDown");
	_buttonDown = _createAndAddSubitem("downButtonDown");
	_buttonUp = _createAndAddSubitem("upButtonDown");
}

QWiimoteWidget::~QWiimoteWidget()
{
	delete _wiimote;
}


void QWiimoteWidget::setWiimoteLED(int num, bool state) {
	if (num < 1 || num > 4) {
		throw std::logic_error("setWiimoteLED expects a number in the range of 1-4");
	}
	_leds[num - 1]->setVisible(state);
}

void QWiimoteWidget::setAButton(bool state) {
	_buttonA->setVisible(state);
}

void QWiimoteWidget::setBButton(bool state) {
	_buttonB->setVisible(state);
}

void QWiimoteWidget::setUpButton(bool state) {
	_buttonUp->setVisible(state);
}

void QWiimoteWidget::setDownButton(bool state) {
	_buttonDown->setVisible(state);
}

void QWiimoteWidget::setLeftButton(bool state) {
	_buttonLeft->setVisible(state);
}

void QWiimoteWidget::setRightButton(bool state) {
	_buttonRight->setVisible(state);
}

void QWiimoteWidget::set1Button(bool state) {
	_button1->setVisible(state);
}

void QWiimoteWidget::set2Button(bool state) {
	_button2->setVisible(state);
}

void QWiimoteWidget::setHomeButton(bool state) {
	_buttonHome->setVisible(state);
}

void QWiimoteWidget::setPlusButton(bool state) {
	_buttonPlus->setVisible(state);
}

void QWiimoteWidget::setMinusButton(bool state) {
	_buttonMinus->setVisible(state);
}

void QWiimoteWidget::resizeEvent(QResizeEvent * event) {
	QGraphicsView::resizeEvent(event);
	fitInView(_wiimote, Qt::KeepAspectRatio);
}

QGraphicsItem * QWiimoteWidget::_createAndAddSubitem(QString const& id) {
	QGraphicsSvgItem * ret = new QGraphicsSvgItem;
	ret->setSharedRenderer(_activated);
	ret->setElementId(id);
	QPolygonF elt = _activated->boundsOnElement(id) *
					_activated->matrixForElement(id);

	ret->setPos(elt.boundingRect().topLeft());
	ret->setZValue(1);

	ret->setVisible(false);
	//ret->setVisible(true);

	scene()->addItem(ret);
	return ret;
}
