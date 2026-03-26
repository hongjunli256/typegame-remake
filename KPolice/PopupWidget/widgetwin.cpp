#include "widgetwin.h"
#include <QPainter>
const QPixmap &WidgetWin::pixWin(bool isPolice)
{
	static const QPixmap pixPoliceWin(":/imagePng/PNG/POLICE_WIN_0.png");
	static const QPixmap pixThiefWin(":/imagePng/PNG/POLICE_WIN_1.png");
	if (isPolice)
	{
		return pixPoliceWin;
	}
	else
	{
		return pixThiefWin;
	}
}
WidgetWin::WidgetWin(QWidget *parent)
	: MyAbstractWidget{parent}
{
	this->resize(800, 600);
	this->hide();
}
void WidgetWin::paintEvent(QPaintEvent *event){
    QWidget::paintEvent(event);
    QPainter painter(this);
	painter.drawPixmap(0, 0, this->pixWin(this->isPolice));
}
void WidgetWin::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape)
	{
		this->hide();
		emit needOperator(operatorType::GAMESETUP_POP);
	}
	else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
	{
		this->hide();
		emit allhide();
	}
}
void WidgetWin::loadSetUp(bool isPolice)
{
	this->isPolice = isPolice;
}
