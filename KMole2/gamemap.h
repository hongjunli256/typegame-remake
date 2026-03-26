#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QLabel>
#include <QPainter>
#include "PopupWidget/myabstractwidget.h"
#include "mousepool.h"
class GameMap : public MyAbstractWidget
{
    Q_OBJECT
public:
    ~GameMap();
    explicit GameMap(QWidget *parent = nullptr);

    void hitMouse(char targetChar);
protected:
    void paintEvent(QPaintEvent *event)override;
private:
	static const QPixmap &pixLife();
	static const QPixmap &pixBackground();
	void drawBackground(QPainter *painter);
	void drawLifeNum(QPainter *painter);
	void initMousePool();
	MousePool *m_mousepool;
	QTimer *m_timerRefresh = nullptr;
	QTimer *m_timerUpdate = nullptr;
	int m_lifeNum = 6;
signals:
	void isHit(bool isHit);
public slots:
	void timer_pause();
	void timer_start();
	void init();
	void loadSetUp(int gameTime, int spareTimeforMouse, int stayTime);
private slots:
	void refresh();
	void loseVegetable();
};

#endif // GAMEMAP_H
