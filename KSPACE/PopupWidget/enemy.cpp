#include "enemy.h"
#include <QFont>
#include <QPainter>
const QFont Enemy::fontBig("黑体", 15, QFont::Bold);
const QPixmap &Enemy::pixChar()
{
	static const QPixmap pix(":/imagePng/PNG/SPACE_CAPTION_BACK.png");
	return pix;
}
const QPixmap &Enemy::pixNormal()
{
	static const QPixmap pix(":/imagePng/PNG/SPACE_ENEMY_0.png");
	return pix;
}
const QPixmap &Enemy::pixExplosion()
{
	static const QPixmap pix(":/imagePng/PNG/SPACE_EXPLOSION_0.png");
	return pix;
}
void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QGraphicsPixmapItem::paint(painter, option, widget);
	if (this->m_condition == condition::LIVE)
	{
		painter->save();
		QRectF baseRect = QGraphicsPixmapItem::boundingRect();
		QPointF imagePos = baseRect.topLeft() + QPointF(19, 0);
		painter->drawPixmap(imagePos, pixChar());
		QRectF charRect = QRectF(imagePos.x() + 4, imagePos.y(), 20, 20);
		painter->setPen(Qt::green);
		painter->setFont(fontBig);
		painter->drawText(charRect, Qt::AlignCenter, QString(this->m_targetChar));
		painter->restore();
	}
}
Enemy::Enemy(char targetChar, float moveSpeed, QPoint pos)
{
	this->m_MoveFrames = cropSpriteFrames(pixNormal(), 11);
	this->m_explosionFrames = cropSpriteFrames(pixExplosion(), 11);
	this->setPixmap(m_MoveFrames.value(0));

	this->m_condition = condition::LIVE;
	this->m_currentIndex = 0;
	this->m_targetChar = targetChar;
	this->m_speedVertical = moveSpeed;
	this->setPos(pos);
}
QVector<QPixmap> Enemy::cropSpriteFrames(const QPixmap &sprite, int frameCount)
{
	QVector<QPixmap> frames;
	if (sprite.isNull() || frameCount <= 0)
	{
		return frames;
	}
	int rowCount = (frameCount + 2) / 3;
	int frameWidth = sprite.width() / 3;
	int frameHeight = sprite.height() / rowCount;

	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			QRect frameRect(j * frameWidth, i * frameHeight, frameWidth, frameHeight);
			QPixmap frame = sprite.copy(frameRect);
			frames.append(frame);
			if (frames.size() >= frameCount)
			{
				return frames;
			}
		}
	}
	return frames;
}
void Enemy::updatePos()
{
	switch (this->m_condition)
	{
	case LIVE:
		this->moveHorizontal();
		this->moveVertical();
		m_currentIndex = (m_currentIndex + 1) % (this->m_MoveFrames.size());
		setPixmap(m_MoveFrames.value(m_currentIndex));
		break;
	case DIE:

		if (m_currentIndex != m_explosionFrames.size() - 1)
		{
			m_currentIndex = (m_currentIndex + 1) % (m_explosionFrames.size());
			setPixmap(m_explosionFrames.value(m_currentIndex));
		}
		break;
	}
}
bool Enemy::isNeedRemove()
{
	if (this->m_condition == condition::DIE && this->m_currentIndex == 10)
	{
		return true;
	}
	else if (this->y() >= 600)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Enemy::isAlive()
{
	switch (this->m_condition)
	{
	case condition::LIVE:
		return true;
		break;
	default:
		return false;
		break;
	}
}
void Enemy::toCollision()
{
	this->m_condition = condition::DIE;
}
void Enemy::toDie()
{
	this->m_condition = condition::DIE;
	m_currentIndex = m_explosionFrames.size() - 1;
}
void Enemy::moveHorizontal()
{
	switch (m_direction)
	{
	case LEFT:
		this->moveBy(-this->m_speedHorizontal, 0);
		if (this->pos().x() <= 0)
		{
			this->m_direction = RIGHT;
		}
		break;
	case RIGHT:
		this->moveBy(this->m_speedHorizontal, 0);
		if (this->pos().x() >= 780)
		{
			this->m_direction = LEFT;
		}
		break;
	}
}
void Enemy::moveVertical()
{
	this->moveBy(0, this->m_speedVertical);
	if (this->m_isCanHit == false && this->pos().y() >= 0)
	{
		this->m_isCanHit = true;
	}
}
bool Enemy::beHitten(char c)
{
	if (this->m_targetChar == c && this->m_isCanHit == true)
	{
		this->m_isCanHit = 0;
		this->m_condition = DIE;
		this->m_currentIndex = 0;
		return true;
	}
	return false;
}
void Enemy::changeState(char targetChar, float movespeed, QPoint pos)
{
	this->m_condition = condition::LIVE;

	this->m_targetChar = targetChar;

	this->m_speedVertical = movespeed;
	this->setPos(pos);

	this->m_isCanHit = false;
}
