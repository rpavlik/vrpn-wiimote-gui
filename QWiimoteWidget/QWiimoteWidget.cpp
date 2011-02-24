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
	setTransformationAnchor(AnchorUnderMouse);
	setDragMode(ScrollHandDrag);
	setViewportUpdateMode(FullViewportUpdate);
	// Prepare background check-board pattern
	QPixmap tilePixmap(64, 64);
	tilePixmap.fill(Qt::white);
	QPainter tilePainter(&tilePixmap);
	QColor color(220, 220, 220);
	tilePainter.fillRect(0, 0, 32, 32, color);
	tilePainter.fillRect(32, 32, 32, 32, color);
	tilePainter.end();

	setBackgroundBrush(tilePixmap);

	QGraphicsScene *s = scene();

	_wiimote = new QGraphicsSvgItem(WIISVG);
	//_wiimote->setFlags(QGraphicsItem::ItemClipsToShape);
	//_wiimote->setZValue(0);
	s->addItem(_wiimote);

	//std::cerr <<_wiimote->boundingRect().width() << " by " << _wiimote->boundingRect().height() << std::endl;
	//s->setSceneRect(_wiimote->boundingRect().adjusted(-10, -10, 10, 10));
/*
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	fitInView(_wiimote, Qt::KeepAspectRatio);
*/
	_activated = new QSvgRenderer(ACTIVESVG, this);
	//_activated = _wiimote->renderer();

	for (unsigned int i = 0; i < 4; ++i) {
		_leds[i] = _createAndAddSubitem(QString("led") + QString::number(i+1));
		_leds[i]->setVisible(true);
	}

	_buttonA = _createAndAddSubitem("aButtonDown");
	_buttonA->setVisible(true);
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
	//fitInView(_wiimote, Qt::KeepAspectRatio);
}

QGraphicsItem * QWiimoteWidget::_createAndAddSubitem(QString const& id) {
	//QGraphicsSvgItem * ret = new QGraphicsSvgItem(ACTIVESVG);
	QGraphicsSvgItem * sub = new QGraphicsSvgItem;
	sub->setSharedRenderer(_activated);
	sub->setElementId(id);
	sub->setFlags(QGraphicsItem::ItemClipsToShape);
	sub->setCacheMode(QGraphicsItem::NoCache);
	QMatrix mat = _activated->matrixForElement(id);
	QRectF bbox =  (_activated->boundsOnElement(id) * mat).boundingRect();

	QString info = QString::number(bbox.topLeft().x()) + QString(", ") + QString::number(bbox.topLeft().x());
	QMessageBox::information(this, id, info);
	//double scale = 1.0; //-0.1;
	QGraphicsItemGroup * ret = new QGraphicsItemGroup;
	ret->addToGroup(sub);
	//ret->setTransform(QTransform(mat));
	//ret->setPos(mat.dx() * scale, mat.dy() * scale);
	ret->setPos(bbox.topLeft());
	ret->setZValue(1);
	ret->setVisible(false);

	scene()->addItem(ret);
	return ret;
}
