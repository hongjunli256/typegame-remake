#ifndef MAPVIEW_H
#define MAPVIEW_H
#include <QApplication>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QLabel>
#include <QTimer>
#include <QVector>
#include "myabstractwidget.h"
#include "person.h"
#include "statusbar.h"
class MapView : public MyAbstractWidget
{
	Q_OBJECT
public:
	MapView(QWidget *parent = nullptr);
	void loadSetUp(bool isPolice, bool isCar1, bool isCar2, QString &StringPath);
	void timer_pause();
	void timer_start();
	void init();

protected:
	// 重写键盘事件（直接处理，无需转发）
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;
	void paintEvent(QPaintEvent *event) override;

private slots:
	void updatePersonPos();
	void updatebeatSpeed();

private:
	QVector<QPoint> m_pathPoints;
	int m_nowtargetPointPolice = 0;
	int m_nowtargetPointThief = 0;
	void createGraphicsView();

	Person *policeItem;
	Person *thiefItem;
	Person *player;
	Person *computer;
	QGraphicsPixmapItem *mapItem;
	QGraphicsScene *scene;
	QGraphicsView *graphicsView; // 地图视图（作为成员变量）

	QTimer *timer;
	QTimer *timerBeatSpeed;
	void createTimers();

	int m_beatCount = 0;
	float m_beatSpeed = 0;

	StatusBar *statusBar;

	//设置相关
	bool isPolice = true;

private slots:
	void timeout();
signals:
};
#endif // MAPVIEW_H
