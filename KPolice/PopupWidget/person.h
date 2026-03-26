#ifndef PERSON_H
#define PERSON_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QRectF>
#include <QTimer>
#include <QVector>
// 8个移动方向 + 静止

class Person : public QGraphicsPixmapItem
{
public:
	Person(bool isPolice = true);
	enum Direction
	{
		UpLeft,	  // 左上（你当前的精灵图=9帧）
		UpRight,  // 右上（1张精灵图=9帧）
		DownLeft, // 左下（1张精灵图=9帧）
		DownRight // 右下（1张精灵图=9帧）
	};
	enum roateDirection
	{
		CW, //顺时针
		CCW //逆时针
	};
	void changeDirection();
	roateDirection m_roateDirection;
	void setMoveDirection(bool up, bool down, bool left, bool right, int beatSpeed);
	void stopMove();
	QPointF getCenterPos() const;
	void turnDirection(bool direction);
	void loadSetUp(bool isCar);
	void init();
private slots:
	void updateAnimationFrame(float beatSpeed); // 9帧循环切换
	void updatePosition();						// 移动+斜向速度归一化

private:
	bool isCar;

	int m_currentFrameIndex;
	void loadAllDirectionSprites(bool isPolice = true);
	QVector<QPixmap> cropSpriteFrames(const QPixmap& sprite, int frameCount);

	// 移动相关
	float m_moveSpeed; // 基础移动速度
	Direction m_direction;

	QVector<QPixmap> m_upLeftSpeed0Frames;
	QVector<QPixmap> m_upRightSpeed0Frames;
	QVector<QPixmap> m_downLeftSpeed0Frames;
	QVector<QPixmap> m_downRightSpeed0Frames;

	QVector<QPixmap> m_upLeftFrames;
	QVector<QPixmap> m_upRightFrames;
	QVector<QPixmap> m_downLeftFrames;
	QVector<QPixmap> m_downRightFrames;

	QVector<QPixmap> m_upLeftBikeFrames;
	QVector<QPixmap> m_upRightBikeFrames;
	QVector<QPixmap> m_downLeftBikeFrames;
	QVector<QPixmap> m_downRightBikeFrames;

	QVector<QPixmap> m_upLeftCarFrames;
	QVector<QPixmap> m_upRightCarFrames;
	QVector<QPixmap> m_downLeftCarFrames;
	QVector<QPixmap> m_downRightCarFrames;
};

#endif // PERSON_H
