#include "frog.h"
const QPixmap& Frog::pixBack1()
{
	static const QPixmap pix(":/imagePng/PNG/FROG_BACK_1.png");
	return pix;
}
const QPixmap& Frog::pixBack2()
{
	static const QPixmap pix(":/imagePng/PNG/FROG_BACK_2.png");
	return pix;
}

const QPixmap& Frog::pixFront1()
{
	static const QPixmap pix(":/imagePng/PNG/FROG_FRONT_1.png");
	return pix;
}
const QPixmap& Frog::pixFront2()
{
	static const QPixmap pix(":/imagePng/PNG/FROG_FRONT_2.png");
	return pix;
}
Frog::Frog(QPoint pos, QWidget* parent)
	: QWidget{parent}
{
	this->resize(this->pixBack1().size());
	this->m_timer = new QTimer(this);
	this->m_timer->start(1000);
	this->m_condition = condition::BACK1;
	this->move(pos);
	connect(this->m_timer, &QTimer::timeout, this, &Frog::refresh);
}
void Frog::changeCondition(condition c)
{
	this->m_condition = c;
}
void Frog::refresh()
{
	switch (this->m_condition)
	{
	case condition::BACK1:
		this->m_condition = condition::BACK2;
		break;
	case condition::BACK2:
		this->m_condition = condition::BACK1;
		break;
	case condition::FRONT1:
		this->m_condition = condition::FRONT2;
		break;
	case condition::FRONT2:
		this->m_condition = condition::FRONT1;
		break;
	default:
		break;
	}
}
void Frog::draw(QPainter* painter)
{
	switch (m_condition)
	{
	case condition::BACK1:
		painter->drawPixmap(this->pos(), this->pixBack1(), QRect(0, 0, this->size().rwidth(), this->size().rheight()));
		break;
	case condition::BACK2:
		painter->drawPixmap(this->pos(), this->pixBack2(), QRect(0, 0, this->size().rwidth(), this->size().rheight()));
		break;
	case condition::FRONT1:
		painter->drawPixmap(this->pos(), this->pixFront1(), QRect(0, 0, this->size().rwidth(), this->size().rheight()));
		break;
	case condition::FRONT2:
		painter->drawPixmap(this->pos(), this->pixFront2(), QRect(0, 0, this->size().rwidth(), this->size().rheight()));
		break;
	default:
		break;
	}
}
