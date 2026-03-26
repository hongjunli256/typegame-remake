#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
class Player : public QGraphicsPixmapItem
{
public:
	Player();
	void init();

private:
	float m_speedHorizontal = 10;
	void moveHorizontal();
	enum direction
	{
		LEFT,
		RIGHT
	};
	direction m_direction = LEFT;
	static const QPixmap &pixNormal();
	int m_currentIndex;
	QVector<QPixmap> m_MoveFrames;
	QVector<QPixmap> cropSpriteFrames(const QPixmap &sprite, int frameCount);
public slots:
	void updatePos();
};

#endif // PLAYER_H
