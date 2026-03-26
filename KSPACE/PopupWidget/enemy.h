#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsitem>

class Enemy : public QGraphicsPixmapItem
{
public:
	explicit Enemy(char targetChar, float moveSpeed, QPoint pos);
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	void changeState(char targetChar, float movespeed, QPoint pos);
	bool isNeedRemove(); //是否要回收
	bool isAlive();		 ////是否活着
	void toDie();
	void toCollision();
	bool beHitten(char c);

private:
	//水平移动相关
	char m_targetChar = 'A';
	bool m_isCanHit = false;
	enum direction
	{
		LEFT,
		RIGHT
	};
	direction m_direction = LEFT;
	float m_speedHorizontal = 10;
	void moveHorizontal();

	//垂直移动相关
	float m_speedVertical = 1;
	void moveVertical();
	static const QFont fontBig;
	static const QPixmap &pixChar();
	static const QPixmap &pixNormal();
	static const QPixmap &pixExplosion();
	enum condition
	{
		LIVE,
		DIE
	};
	condition m_condition;

	int m_currentIndex;

	QVector<QPixmap> m_MoveFrames;
	QVector<QPixmap> m_explosionFrames;
	QVector<QPixmap> cropSpriteFrames(const QPixmap &sprite, int frameCount);
	//void changeSpeedVertical(float speedVertical);

public slots:
	void updatePos();
signals:
	void needReomove();
};

#endif // ENEMY_H
