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
#include "enemy.h"
#include "myabstractwidget.h"
#include "player.h"
#include "statusbar.h"
class MapView : public MyAbstractWidget
{
	Q_OBJECT
public:
	MapView(QWidget *parent = nullptr);
	void loadSetUp(int enemyNum, float enemySpeed, bool isReward);
	void timer_pause();
	void timer_start();
	void init();

protected:
	// 重写键盘事件（直接处理，无需转发）
	void keyPressEvent(QKeyEvent *event) override;
	void paintEvent(QPaintEvent *event) override;

private slots:
	// void updatePersonPos();
	// void updatebeatSpeed();

private:
	// QVector<QPoint> m_pathPoints;
	// int m_nowtargetPointPolice = 0;
	// int m_nowtargetPointThief = 0;
	void createGraphicsView();
	QString getPlayerNickname();
	Player *player;
	QList<Enemy *> m_enemyList;
	QList<Enemy *> m_enemyWaitList; //墓地
	void addEnemy();
	void removeEnemy(Enemy *enemy);
	void cleanup();
	QTimer *timerForMove;
	QTimer *timerForCleanUp;
	void initTimer();
	void BGroll();
	float EnemySpeed = 10;
	int EnemyNum = 5;
	int score = 0;
	bool isReward = false;

	QGraphicsPixmapItem *mapItem;
	QGraphicsScene *scene;
	QGraphicsView *graphicsView; // 地图视图（作为成员变量）
	char generateRandomLetter();
	int generateSuitablePosX();
	int generateSuitablePosY();

	// QTimer *timer;
	// QTimer *timerBeatSpeed;
	// void createTimers();

	// int m_beatCount = 0;
	// float m_beatSpeed = 0;

	StatusBar *statusBar;

	// //设置相关
	// bool isPolice = true;

private slots:
	//void timeout();
	void cleanUp();
	void planeMove();

signals:
	void newScore(QString name, int score);
};
#endif // MAPVIEW_H
