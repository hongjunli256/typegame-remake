#include "rat.h"
//老鼠图像的状态更新
const QFont Rat::fontBig("黑体", 25, QFont::Bold);
const QFont Rat::fontsmall("黑体", 12, QFont::Normal);
const QPixmap& Rat::pixAppear()
{
	static const QPixmap pix(":/imagePng/PNG/MOLE_APPEAR.png");
	return pix;
}

const QPixmap& Rat::pixHide()
{
	static const QPixmap pix(":/imagePng/PNG/MOLE_HIDE.png");
	return pix;
}

const QPixmap& Rat::pixHit()
{
	static const QPixmap pix(":/imagePng/PNG/MOLE_HIT.png");
	return pix;
}

const QPixmap& Rat::pixNormal()
{
	static const QPixmap pix(":/imagePng/PNG/MOLE_NORMAL.png");
	return pix;
}
Rat::Rat(QWidget* parent, char targetChar, int stayTime, int posForArray)
	: QWidget(parent)
{
	this->setFixedSize(pixNormal().size());

	this->m_targetChar = targetChar;

	this->m_stayTime = stayTime;
	QPoint point;
	point.setX(posForArray / 2 * 126 + 20);
	point.setY(posForArray % 2 * 154 + 150);
	this->move(point);

	this->m_isCanHit = false;

	this->m_timer = new QTimer(this);

	this->m_timer->start(500);

	this->m_condition = condition::APPEAR1;

	this->m_livetime = 0.0;

	this->m_posForArray = posForArray;

	connect(this->m_timer, &QTimer::timeout, this, &Rat::refresh);
}
void Rat::changeState(char targetChar, int stayTime, int posForArray)
{
	this->m_targetChar = targetChar;

	this->m_stayTime = stayTime;

	QPoint point;
	point.setX(posForArray / 2 * 126 + 20);
	point.setY(posForArray % 2 * 154 + 150);
	this->move(point);

	this->m_isCanHit = false;

	this->m_timer->start(500);

	this->m_condition = Rat::condition::APPEAR1;

	this->m_livetime = 0.0;

	this->m_posForArray = posForArray;
	connect(this->m_timer, &QTimer::timeout, this, &Rat::refresh);
}
Rat::~Rat() {}

void Rat::draw(QPainter* painter)
{
	switch (m_condition)
	{
	case condition::APPEAR1:
		painter->drawPixmap(this->pos(), this->pixAppear(), QRect(0, 0, this->size().rwidth(), this->size().rheight()));
		break;
	case condition::APPEAR2:
		painter->drawPixmap(this->pos(), this->pixAppear(), QRect(this->size().rwidth(), 0, this->size().rwidth(), this->size().rheight()));
		break;
	case condition::HIDE1:
		painter->drawPixmap(this->pos(), this->pixHide(), QRect(0, 0, this->size().rwidth(), this->size().rheight()));
		break;
	case condition::HIDE2:
		painter->drawPixmap(this->pos(), this->pixHide(), QRect(this->size().rwidth(), 0, this->size().rwidth(), this->size().rheight()));
		break;
	case condition::HIT:
		painter->drawPixmap(this->pos(), this->pixHit(), QRect(0, 0, this->size().rwidth(), this->size().rheight()));
		break;
	case condition::NORMAL:
		painter->drawPixmap(this->pos(), this->pixNormal(), QRect(0, 0, this->size().rwidth(), this->size().rheight()));
		this->drawChar(painter);
		break;
	default:
		break;
	}
}
void Rat::refresh()
{
	if (m_livetime < 0.5)
	{
		this->m_isCanHit = false;
		this->m_condition = condition::APPEAR1;
	}
	else if (m_livetime < 1)
	{
		this->m_condition = condition::APPEAR2;
		emit needSound(soundType::MOUSEOUT);
	}
	else if (m_livetime < this->m_stayTime + 1)
	{
		this->m_isCanHit = true;
		this->m_condition = condition::NORMAL;
	}
	else if (m_livetime < this->m_stayTime + 1.5)
	{
		this->m_isCanHit = false;
		this->m_condition = condition::HIDE1;
	}
	else if (m_livetime < this->m_stayTime + 2)
	{
		this->m_condition = condition::HIDE2;
		emit stealVegetable();
		emit needSound(soundType::MOUSEAWAY);
	}
	else
	{
		this->toDie();
	}
	if (this->m_condition != condition::DIE)
	{
		m_livetime += 0.5;
	}
	else
	{
		return;
	}
}

void Rat::drawChar(QPainter* painter)
{
	painter->setFont(Rat::fontBig);
	painter->setPen(Qt::black);
	painter->drawText(this->pos() + QPoint(75, 40), QString(this->m_targetChar));
	painter->setFont(Rat::fontsmall);
	painter->setPen(Qt::red);
	painter->drawText(this->pos() + QPoint(100, 40), QString::number(int(this->m_stayTime + 1 - this->m_livetime)));
}
void Rat::beHitten()
{
	this->m_condition = condition::HIT;
	emit this->needSound(soundType::MOUSECLICKED);
	this->m_isCanHit = false;
	this->m_timer->stop();
	disconnect(this->m_timer, &QTimer::timeout, this, nullptr);
	this->m_timer->start(500);
	connect(this->m_timer, &QTimer::timeout, this, &Rat::toDie);
}
void Rat::toDie()
{
	this->m_timer->stop();
	disconnect(this->m_timer, &QTimer::timeout, this, nullptr);
	this->m_condition = condition::DIE;
}
