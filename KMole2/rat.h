#ifndef RAT_H
#define RAT_H

#include <QPainter>
#include <QTimer>
#include <QWidget>
#include "PopupWidget/public_enum.h"
class Rat : public QWidget
{
	Q_OBJECT
public:
	explicit Rat(QWidget* parent, char targetChar, int stayTime, int posForArray);
	~Rat();
	enum condition
	{
		APPEAR1,
		APPEAR2,
		HIDE1,
		HIDE2,
		HIT,
		NORMAL,
		DIE
	};

	char m_targetChar = 'A';
	bool m_isCanHit = false;
	int m_posForArray = 0;
	QTimer* m_timer = nullptr;
	condition m_condition;

	void draw(QPainter* painter);
	void beHitten();
	void changeState(char targetChar, int stayTime, int posForArray);

private:
	int m_stayTime = 0;
	float m_livetime = 0.0;

	void drawChar(QPainter* painter);

	static const QFont fontBig;
	static const QFont fontsmall;

	static const QPixmap& pixAppear();
	static const QPixmap& pixHide();
	static const QPixmap& pixHit();
	static const QPixmap& pixNormal();

private slots:
	void refresh();

public slots:
	void toDie();

signals:
	void needSound(soundType type);

	void stealVegetable();
};

#endif // RAT_H
