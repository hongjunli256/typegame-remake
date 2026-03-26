#include "player.h"

const QPixmap &Player::pixNormal()
{
	static const QPixmap pix(":/imagePng/PNG/SPACE_SHIP.png");
	return pix;
}
void Player::init()
{
	this->setPixmap(m_MoveFrames.value(0));
	this->m_currentIndex = 0;
	this->setPos(400, 500);
}
Player::Player()
{
	this->m_MoveFrames = cropSpriteFrames(pixNormal(), 11);
	this->setPixmap(m_MoveFrames.value(0));
	this->m_currentIndex = 0;
	this->setPos(400, 500);
}
QVector<QPixmap> Player::cropSpriteFrames(const QPixmap &sprite, int frameCount)
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
void Player::updatePos()
{
	this->moveHorizontal();

	m_currentIndex = (m_currentIndex + 1) % (this->m_MoveFrames.size());
	setPixmap(m_MoveFrames.value(m_currentIndex));
}

void Player::moveHorizontal()
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
