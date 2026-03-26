#include "person.h"
#include <QDebug>
#include <QTimer>
Person::Person(bool isPolice)
	: m_moveSpeed(4.0f)
{
	// 1. 加载所有方向的精灵图（裁剪9帧）
	loadAllDirectionSprites(isPolice);
	this->init();
}
void Person::init()
{
	this->m_currentFrameIndex = 0;
	this->m_roateDirection = roateDirection::CW;
	this->m_moveSpeed = 0;
}
QVector<QPixmap> Person::cropSpriteFrames(const QPixmap& sprite, int frameCount)
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

// 加载所有方向的精灵图（关键：替换为你的精灵图路径）
void Person::loadAllDirectionSprites(bool isPolice)
{
	if (isPolice)
	{
		QPixmap upLeftSpeed0Sprite(":/imagePng/PNG/POLICE_0_0_0.png"); // 左上
		m_upLeftSpeed0Frames = cropSpriteFrames(upLeftSpeed0Sprite, 8);
		QPixmap downLeftSpeed0Sprite(":/imagePng/PNG/POLICE_0_0_1.png"); // 左上
		m_downLeftSpeed0Frames = cropSpriteFrames(downLeftSpeed0Sprite, 8);
		QPixmap upRightSpeed0Sprite(":/imagePng/PNG/POLICE_0_0_2.png"); // 左上
		m_upRightSpeed0Frames = cropSpriteFrames(upRightSpeed0Sprite, 8);
		QPixmap downRightSpeed0Sprite(":/imagePng/PNG/POLICE_0_0_3.png"); // 左上
		m_downRightSpeed0Frames = cropSpriteFrames(downRightSpeed0Sprite, 8);

		QPixmap upLeftSprite(":/imagePng/PNG/POLICE_0_1_0.png"); // 左上
		m_upLeftFrames = cropSpriteFrames(upLeftSprite, 8);
		QPixmap downLeftSprite(":/imagePng/PNG/POLICE_0_1_1.png"); // 左下
		m_downLeftFrames = cropSpriteFrames(downLeftSprite, 8);
		QPixmap upRightSprite(":/imagePng/PNG/POLICE_0_1_2.png"); // 右上
		m_upRightFrames = cropSpriteFrames(upRightSprite, 8);
		QPixmap downRightSprite(":/imagePng/PNG/POLICE_0_1_3.png"); // 右下
		m_downRightFrames = cropSpriteFrames(downRightSprite, 8);

		QPixmap upLeftBikeSprite(":/imagePng/PNG/POLICE_0_2_0.png");
		m_upLeftBikeFrames = cropSpriteFrames(upLeftBikeSprite, 17);
		QPixmap downLeftBikeSprite(":/imagePng/PNG/POLICE_0_2_1.png");
		m_downLeftBikeFrames = cropSpriteFrames(downLeftBikeSprite, 17);
		QPixmap upRightBikeSprite(":/imagePng/PNG/POLICE_0_2_2.png");
		m_upRightBikeFrames = cropSpriteFrames(upRightBikeSprite, 17);
		QPixmap downRightBikeSprite(":/imagePng/PNG/POLICE_0_2_3.png");
		m_downRightBikeFrames = cropSpriteFrames(downRightBikeSprite, 17);

		QPixmap upLeftCarSprite(":/imagePng/PNG/POLICE_0_3_0.png");
		m_upLeftCarFrames = cropSpriteFrames(upLeftCarSprite, 11);
		QPixmap downLeftCarSprite(":/imagePng/PNG/POLICE_0_3_1.png");
		m_downLeftCarFrames = cropSpriteFrames(downLeftCarSprite, 11);
		QPixmap upRightCarSprite(":/imagePng/PNG/POLICE_0_3_2.png");
		m_upRightCarFrames = cropSpriteFrames(upRightCarSprite, 11);
		QPixmap downRightCarSprite(":/imagePng/PNG/POLICE_0_3_3.png");
		m_downRightCarFrames = cropSpriteFrames(downRightCarSprite, 11);
	}
	else
	{
		QPixmap upLeftSpeed0Sprite(":/imagePng/PNG/POLICE_1_0_0.png"); // 左上
		m_upLeftSpeed0Frames = cropSpriteFrames(upLeftSpeed0Sprite, 11);
		QPixmap downLeftSpeed0Sprite(":/imagePng/PNG/POLICE_1_0_1.png"); // 左上
		m_downLeftSpeed0Frames = cropSpriteFrames(downLeftSpeed0Sprite, 11);
		QPixmap upRightSpeed0Sprite(":/imagePng/PNG/POLICE_1_0_2.png"); // 左上
		m_upRightSpeed0Frames = cropSpriteFrames(upRightSpeed0Sprite, 11);
		QPixmap downRightSpeed0Sprite(":/imagePng/PNG/POLICE_1_0_3.png"); // 左上
		m_downRightSpeed0Frames = cropSpriteFrames(downRightSpeed0Sprite, 11);

		QPixmap upLeftSprite(":/imagePng/PNG/POLICE_1_1_0.png"); // 左上
		m_upLeftFrames = cropSpriteFrames(upLeftSprite, 8);
		QPixmap downLeftSprite(":/imagePng/PNG/POLICE_1_1_1.png"); // 左下
		m_downLeftFrames = cropSpriteFrames(downLeftSprite, 8);
		QPixmap upRightSprite(":/imagePng/PNG/POLICE_1_1_2.png"); // 右上
		m_upRightFrames = cropSpriteFrames(upRightSprite, 8);
		QPixmap downRightSprite(":/imagePng/PNG/POLICE_1_1_3.png"); // 右下
		m_downRightFrames = cropSpriteFrames(downRightSprite, 8);

		QPixmap upLeftBikeSprite(":/imagePng/PNG/POLICE_1_2_0.png");
		m_upLeftBikeFrames = cropSpriteFrames(upLeftBikeSprite, 11);
		QPixmap downLeftBikeSprite(":/imagePng/PNG/POLICE_1_2_1.png");
		m_downLeftBikeFrames = cropSpriteFrames(downLeftBikeSprite, 11);
		QPixmap upRightBikeSprite(":/imagePng/PNG/POLICE_1_2_2.png");
		m_upRightBikeFrames = cropSpriteFrames(upRightBikeSprite, 11);
		QPixmap downRightBikeSprite(":/imagePng/PNG/POLICE_1_2_3.png");
		m_downRightBikeFrames = cropSpriteFrames(downRightBikeSprite, 11);

		QPixmap upLeftCarSprite(":/imagePng/PNG/POLICE_1_3_0.png");
		m_upLeftCarFrames = cropSpriteFrames(upLeftCarSprite, 11);
		QPixmap downLeftCarSprite(":/imagePng/PNG/POLICE_1_3_1.png");
		m_downLeftCarFrames = cropSpriteFrames(downLeftCarSprite, 11);
		QPixmap upRightCarSprite(":/imagePng/PNG/POLICE_1_3_2.png");
		m_upRightCarFrames = cropSpriteFrames(upRightCarSprite, 11);
		QPixmap downRightCarSprite(":/imagePng/PNG/POLICE_1_3_3.png");
		m_downRightCarFrames = cropSpriteFrames(downRightCarSprite, 11);
	}
}

// 外部控制：设置移动方向（MapView调用）
void Person::setMoveDirection(bool up, bool down, bool left, bool right, int beatSpeed)
{
	// 8方向判断（斜向优先）
	if (up && left)
	{
		m_direction = Direction::UpLeft;
	}
	else if (up && right)
	{
		m_direction = Direction::UpRight;
	}
	else if (down && left)
	{
		m_direction = Direction::DownLeft;
	}
	else if (down && right)
	{
		m_direction = Direction::DownRight;
	}

	this->updateAnimationFrame(beatSpeed);
	this->updatePosition();
}

void Person::turnDirection(bool direction) //true就是凸，false就是凹
{
	if (direction)
	{
		switch (this->m_roateDirection)
		{
		case CW:
			if (this->m_direction == Direction::UpLeft)
			{
				m_direction = Direction::UpRight;
			}
			else if (this->m_direction == Direction::DownLeft)
			{
				m_direction = Direction::UpLeft;
			}
			else if (this->m_direction == Direction::UpRight)
			{
				this->m_direction = Direction::DownRight;
			}
			else if (this->m_direction == Direction::DownRight)
			{
				this->m_direction = Direction::DownLeft;
			}
			break;
		case CCW:
			if (this->m_direction == Direction::UpLeft)
			{
				m_direction = Direction::DownLeft;
			}
			else if (this->m_direction == Direction::DownLeft)
			{
				m_direction = Direction::DownRight;
			}
			else if (this->m_direction == Direction::UpRight)
			{
				this->m_direction = Direction::UpLeft;
			}
			else if (this->m_direction == Direction::DownRight)
			{
				this->m_direction = Direction::UpRight;
			}
			break;
		}
	}
	else
	{
		switch (this->m_roateDirection)
		{
		case CCW:
			if (this->m_direction == Direction::UpLeft)
			{
				m_direction = Direction::UpRight;
			}
			else if (this->m_direction == Direction::DownLeft)
			{
				m_direction = Direction::UpLeft;
			}
			else if (this->m_direction == Direction::UpRight)
			{
				this->m_direction = Direction::DownRight;
			}
			else if (this->m_direction == Direction::DownRight)
			{
				this->m_direction = Direction::DownLeft;
			}
			break;
		case CW:
			if (this->m_direction == Direction::UpLeft)
			{
				m_direction = Direction::DownLeft;
			}
			else if (this->m_direction == Direction::DownLeft)
			{
				m_direction = Direction::DownRight;
			}
			else if (this->m_direction == Direction::UpRight)
			{
				this->m_direction = Direction::UpLeft;
			}
			else if (this->m_direction == Direction::DownRight)
			{
				this->m_direction = Direction::UpRight;
			}
			break;
		}
	}
}
// 获取人物中心坐标（视图跟随用）
QPointF Person::getCenterPos() const
{
	QRectF rect = boundingRect();
	return QPointF(pos().x() + rect.width() / 2, pos().y() + rect.height() / 2);
}

// 8帧循环切换
void Person::updateAnimationFrame(float beatSpeed)
{
	if (m_moveSpeed < beatSpeed && m_moveSpeed <= 20)
	{
		m_moveSpeed++;
	}
	else if (m_moveSpeed > beatSpeed)
	{
		m_moveSpeed--;
	}
	if (m_moveSpeed <= 2)
	{
		m_currentFrameIndex = (m_currentFrameIndex + 1) % (m_upLeftSpeed0Frames.size());
		if (m_direction == Direction::UpLeft)
		{
			setPixmap(m_upLeftSpeed0Frames.value(m_currentFrameIndex));
		}
		else if (m_direction == Direction::DownLeft)
		{
			setPixmap(m_downLeftSpeed0Frames.value(m_currentFrameIndex));
		}
		else if (m_direction == Direction::UpRight)
		{
			setPixmap(m_upRightSpeed0Frames.value(m_currentFrameIndex));
		}
		else if (m_direction == Direction::DownRight)
		{
			setPixmap(m_downRightSpeed0Frames.value(m_currentFrameIndex));
		}
	}
	else if (m_moveSpeed <= 10)
	{
		m_currentFrameIndex = (m_currentFrameIndex + 1) % this->m_upLeftFrames.size();
		if (m_direction == Direction::UpLeft)
		{
			setPixmap(m_upLeftFrames.value(m_currentFrameIndex));
		}
		else if (m_direction == Direction::DownLeft)
		{
			setPixmap(m_downLeftFrames.value(m_currentFrameIndex));
		}
		else if (m_direction == Direction::UpRight)
		{
			setPixmap(m_upRightFrames.value(m_currentFrameIndex));
		}
		else if (m_direction == Direction::DownRight)
		{
			setPixmap(m_downRightFrames.value(m_currentFrameIndex));
		}
	}
	else
	{
		if (!isCar)
		{
			m_currentFrameIndex = (m_currentFrameIndex + 1) % m_upLeftBikeFrames.size();
			if (m_direction == Direction::UpLeft)
			{
				setPixmap(m_upLeftBikeFrames.value(m_currentFrameIndex));
			}
			else if (m_direction == Direction::DownLeft)
			{
				setPixmap(m_downLeftBikeFrames.value(m_currentFrameIndex));
			}
			else if (m_direction == Direction::UpRight)
			{
				setPixmap(m_upRightBikeFrames.value(m_currentFrameIndex));
			}
			else if (m_direction == Direction::DownRight)
			{
				setPixmap(m_downRightBikeFrames.value(m_currentFrameIndex));
			}
		}
		else
		{
			m_currentFrameIndex = (m_currentFrameIndex + 1) % m_upLeftCarFrames.size();

			if (m_direction == Direction::UpLeft)
			{
				setPixmap(m_upLeftCarFrames.value(m_currentFrameIndex));
			}
			else if (m_direction == Direction::DownLeft)
			{
				setPixmap(m_downLeftCarFrames.value(m_currentFrameIndex));
			}
			else if (m_direction == Direction::UpRight)
			{
				setPixmap(m_upRightCarFrames.value(m_currentFrameIndex));
			}
			else if (m_direction == Direction::DownRight)
			{
				setPixmap(m_downRightCarFrames.value(m_currentFrameIndex));
			}
		}
	}
}

// 移动更新（斜向速度归一化）
void Person::updatePosition()
{
	float dx = 0, dy = 0;
	int speed = m_moveSpeed;
	if (m_moveSpeed > 10)
	{
		if (isCar)
		{
			speed = 2 * m_moveSpeed;
		}
		else
		{
			speed = 1.5 * m_moveSpeed;
		}
	}
	if (m_direction == Direction::UpLeft)
	{
		dy -= 0.2 * speed;
		dx -= 0.4 * speed;
	}
	else if (m_direction == Direction::DownLeft)
	{
		dy += 0.2 * speed;
		dx -= 0.4 * speed;
	}
	else if (m_direction == Direction::UpRight)
	{
		dy -= 0.2 * speed;
		dx += 0.4 * speed;
	}
	else if (m_direction == Direction::DownRight)
	{
		dy += 0.2 * speed;
		dx += 0.4 * speed;
	}

	float halfWidth = 800;
	float halfHeight = 600;

	this->moveBy(dx, dy);
}
void Person::loadSetUp(bool isCar)
{
	this->isCar = isCar;
}
void Person::changeDirection()
{
	if (this->m_roateDirection == CCW)
	{
		this->m_roateDirection = CW;
	}
	else
	{
		this->m_roateDirection = CCW;
	}

	if (m_direction == Direction::UpLeft)
	{
		m_direction = Direction::DownRight;
	}
	else if (m_direction == Direction::DownLeft)
	{
		m_direction = Direction::UpRight;
	}
	else if (m_direction == Direction::UpRight)
	{
		m_direction = Direction::DownLeft;
	}
	else if (m_direction == Direction::DownRight)
	{
		m_direction = Direction::UpLeft;
	}
}
