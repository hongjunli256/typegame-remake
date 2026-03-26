#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QLabel>
#include <QPainter>
#include "PopupWidget/myabstractwidget.h"
#include "applepool.h"
class GameMap : public MyAbstractWidget
{
    Q_OBJECT
public:
    ~GameMap();
    explicit GameMap(QWidget *parent = nullptr);

    void hitApple(char targetChar);
protected:
    void paintEvent(QPaintEvent *event)override;
private:

    static const QPixmap& pixBasket();
    static const QPixmap& pixBackground();

    void drawBackground(QPainter*painter);
    void drawBasket(QPainter*painter);

	void initApplePool();

	ApplePool *m_applePool;
	QTimer *m_timerRefresh = nullptr;
	QTimer *m_timerUpdate = nullptr;
signals:
public slots:
	void timer_pause();
	void timer_start();
	void init();

	void loadSetUp(int winNum, int failNum, int gameLevel);

private slots:
	void refresh();
};

#endif // GAMEMAP_H
