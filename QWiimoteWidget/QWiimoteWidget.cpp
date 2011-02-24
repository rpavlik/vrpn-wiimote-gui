#include "QWiimoteWidget.h"

#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QMessageBox>

#include <iostream>

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

	_buttonA = _createAndAddSubitem("aButtonDown");
}

QWiimoteWidget::~QWiimoteWidget()
{
	delete _wiimote;
}


void QWiimoteWidget::setWiimoteLED(int num, bool state) {

}

void QWiimoteWidget::setAButton(bool state) {

}

void QWiimoteWidget::setBButton(bool state) {

}

void QWiimoteWidget::setUpButton(bool state) {

}

void QWiimoteWidget::setDownButton(bool state) {

}

void QWiimoteWidget::setLeftButton(bool state) {

}

void QWiimoteWidget::setRightButton(bool state) {

}

void QWiimoteWidget::set1Button(bool state) {

}

void QWiimoteWidget::set2Button(bool state) {

}

void QWiimoteWidget::setHomeButton(bool state) {

}

void QWiimoteWidget::setPlusButton(bool state) {

}

void QWiimoteWidget::setMinusButton(bool state) {

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

	//ret->setVisible(false);
	ret->setVisible(true);

	scene()->addItem(ret);
	return ret;
}
