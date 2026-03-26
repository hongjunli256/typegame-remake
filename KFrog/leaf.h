#ifndef LEAF_H
#define LEAF_H

#include <QPainter>
#include <QTimer>
#include <QWidget>
#include "PopupWidget/public_enum.h"
#include "frog.h"
#include "textbox.h"
class Leaf : public QWidget
{
	Q_OBJECT
public:
	explicit Leaf(QWidget* parent, QString string, int slideTime, QPoint pos, int direction);
	~Leaf();

	TextBox* m_textBox;

	int m_direction = -1;
	int m_slideTime = 0;

	QTimer* m_timer = nullptr;

	void changeState(QString string, int slideTime);

	void getFrog(Frog* frog);
	void draw(QPainter* painter);

private:
	static const QPixmap& pixNormal();
	Frog* frog = nullptr;
private slots:
	void refresh();

signals:
	void needSound(soundType type);
	void finishSpell();
	void frogDrop();
	void timeOut(Leaf* leaf);
};

#endif // LEAF_H
