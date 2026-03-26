#include "widgetfail.h"
#include <QKeyEvent>
#include <QPainter>
const QPixmap &WidgetFail::pixFail(bool isPolice)
{
	static const QPixmap pixPoliceFail(":/imagePng/PNG/POLICE_LOST_0.png");
	static const QPixmap pixThiefFail(":/imagePng/PNG/POLICE_LOST_1.png");
	if (isPolice)
	{
		return pixPoliceFail;
	}
	else
	{
		return pixThiefFail;
	}
}
WidgetFail::WidgetFail(QWidget *parent)
	: MyAbstractWidget{parent}
{
	this->resize(800, 600);
	this->hide();
}
void WidgetFail::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);
	painter.drawPixmap(0, 0, this->pixFail(this->isPolice));
}
void WidgetFail::keyPressEvent(QKeyEvent *event)
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
void WidgetFail::loadSetUp(bool isPolice)
{
	this->isPolice = isPolice;
}
