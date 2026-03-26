#ifndef FROG_H
#define FROG_H

#include <QPainter>
#include <QPoint>
#include <QTimer>
#include <QWidget>
class Frog : public QWidget
{
	Q_OBJECT
public:
	explicit Frog(QPoint pos, QWidget* parent = nullptr);
	enum condition
	{
		BACK1,
		BACK2,
		FRONT1,
		FRONT2
	};
	void draw(QPainter* painter);
	void changeCondition(condition c);

private:
	static const QPixmap& pixBack1();
	static const QPixmap& pixFront1();
	static const QPixmap& pixBack2();
	static const QPixmap& pixFront2();

	QTimer* m_timer = nullptr;
	condition m_condition;

signals:
private slots:
	void refresh();
};

#endif // FROG_H
