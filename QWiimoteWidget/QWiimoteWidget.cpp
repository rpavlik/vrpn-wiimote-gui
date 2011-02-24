#include "QWiimoteWidget.h"
#include "ui_QWiimoteWidget.h"

#include <QGraphicsSvgItem>

QWiimoteWidget::QWiimoteWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QWiimoteWidget)
{
    ui->setupUi(this);
	_scene = new QGraphicsScene(ui->graphicsView);
	ui->graphicsView->setScene(_scene);
	QGraphicsSvgItem * svgItem = new QGraphicsSvgItem(":/wiimote-full.svg");
	_scene->addItem(svgItem);
	_scene->setSceneRect(svgItem->boundingRect().adjusted(-10, -10, 10, 10));
}

QWiimoteWidget::~QWiimoteWidget()
{
    delete ui;
	delete _scene;
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
