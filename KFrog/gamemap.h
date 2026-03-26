#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QLabel>
#include <QPainter>
#include <QWidget>
#include "PopupWidget/myabstractwidget.h"
#include "itempool.h"
class GameMap : public MyAbstractWidget
{
	Q_OBJECT
public:
	~GameMap();
	explicit GameMap(QWidget *parent = nullptr);

	void hitWord(QString targetChar);

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	static const QPixmap &pixBasket();
	static const QPixmap &pixBackground();

	void drawBackground(QPainter *painter);
	void drawBasket(QPainter *painter);

	void initItemPool();

	ItemPool *m_itemPool;
	QTimer *m_timerRefresh = nullptr;
	QTimer *m_timerUpdate = nullptr;
signals:
	void isHit(bool isHit);
public slots:
	void timer_pause();
	void timer_start();

	void init();

	void loadSetUp(int gameLevel, QString selectedDifficulty);

private slots:
	void refresh();
};

#endif // GAMEMAP_H
