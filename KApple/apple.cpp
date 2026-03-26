#include "apple.h"
//苹果图像的状态更新
const QFont Apple::fontBig("黑体", 25, QFont::Bold);

const QPixmap& Apple::pixBad()
{
	static const QPixmap pix(":/imagePng/PNG/APPLE_BAD.png");
	return pix;
}

const QPixmap& Apple::pixNormal()
{
	static const QPixmap pix(":/imagePng/PNG/APPLE_NORMAL.png");
	return pix;
}
Apple::Apple(QWidget* parent, char targetChar, int fallTime, int posX)
	: QWidget(parent)
{
	this->resize(pixNormal().size());

	this->m_condition = condition::NORMAL;

	this->m_targetChar = targetChar;

	this->m_fallTime = fallTime;

	this->move(posX, -80);

	this->m_isCanHit = false;

	this->m_timer=new QTimer(this);

	this->m_timer->start(5 * fallTime);

	connect(this->m_timer, &QTimer::timeout, this, &Apple::refresh);
}
void Apple::changeState(char targetChar, int fallTime, int posX)
{
	this->resize(pixNormal().size());

	this->m_condition = condition::NORMAL;

	this->m_targetChar = targetChar;

	this->m_fallTime = fallTime;

	this->move(posX, -80);

	this->m_isCanHit = false;

	this->m_timer->start(5 * fallTime);

	connect(this->m_timer, &QTimer::timeout, this, &Apple::refresh);
}
Apple::~Apple() {}

void Apple::draw(QPainter* painter)
{
    switch (m_condition) {
	case condition::BAD:
		painter->drawPixmap(this->pos(), this->pixBad(), QRect(0, 0, this->size().rwidth(), this->size().rheight()));
		break;
	case condition::NORMAL:
		painter->drawPixmap(this->pos(), this->pixNormal(), QRect(0, 0, this->size().rwidth(), this->size().rheight()));
		this->drawChar(painter);
		break;
	default:
		break;
	}
}
void Apple::refresh()
{
	if (this->pos().ry() >= 410)
	{
		this->toDie();
	}
	else if (this->pos().ry() >= 400 && this->m_condition == condition::NORMAL)
	{
		this->m_isCanHit = false;
		this->m_condition = condition::BAD;
		this->resize(pixBad().size());
		emit appleBroken();
	}
	else if (this->pos().ry() >= 0)
	{
		this->m_isCanHit = true;
	}
	if (this->m_condition != condition::DIE)
	{
		this->move(pos() + QPoint(0, 2));
	}
	else
	{
		return;
	}
}

void Apple::drawChar(QPainter* painter)
{
	painter->setFont(Apple::fontBig);
	painter->setPen(Qt::white);
	painter->drawText(this->pos() + QPoint(20, 40), QString(this->m_targetChar));
}
void Apple::beHitten()
{
	this->m_condition = condition::DIE;
	emit this->needSound(soundType::APPLEIN);
	this->m_isCanHit = false;
	this->toDie();
}
void Apple::toDie()
{
    this->m_timer->stop();
    disconnect(this->m_timer,&QTimer::timeout,this,nullptr);
    this->m_condition=condition::DIE;
}
