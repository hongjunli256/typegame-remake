#ifndef APPLE_H
#define APPLE_H

#include <QPainter>
#include <QTimer>
#include <QWidget>
#include "PopupWidget/public_enum.h"
class Apple : public QWidget
{
    Q_OBJECT
public:
	explicit Apple(QWidget* parent, char targetChar, int fallTime, int posX);
	~Apple();
	enum condition
	{
		NORMAL,
		BAD,
		DIE
	};

	char m_targetChar = 'A';

	bool m_isCanHit = false;

	int m_fallTime = 0;
	QTimer* m_timer = nullptr;
	condition m_condition;
	void draw(QPainter* painter);
	void beHitten();
	void changeState(char targetChar, int fallTime, int posX);

private:
	void drawChar(QPainter* painter);
	static const QFont fontBig;
	static const QPixmap& pixBad();
	static const QPixmap& pixNormal();

private slots:
	void refresh();

public slots:
	void toDie();

signals:
	void needSound(soundType type);
	void appleBroken();
};

#endif // APPLE_H
