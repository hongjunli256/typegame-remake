#include "mapview.h"
#include <QFile>
//功能主体已经完整实现，
//第一步整理好无用代码，
//第二步加入两人追逐战，
//第三步评估联机对战难度看是否做
//飞机大战看起来挺简单的，到时候套用apple模板做一下

MapView::MapView(QWidget *parent)
	: MyAbstractWidget(parent)
{
	this->move(0, 0);
	this->setFixedSize(800, 600);
	this->createGraphicsView();
	this->createTimers();

	this->statusBar = new StatusBar(this->graphicsView);
	connect(this->statusBar, &StatusBar::timeout, this, &MapView::timeout);
	statusBar->raise();
	this->init();
	this->timer_pause();
	this->hide();
}
void MapView::createTimers()
{
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &MapView::updatePersonPos);
	connect(timer, &QTimer::timeout, this,
			[=]()
			{
				this->update();
				this->statusBar->update();
			});
	this->timerBeatSpeed = new QTimer(this);
	connect(timerBeatSpeed, &QTimer::timeout, this, &MapView::updatebeatSpeed);
}
void MapView::createGraphicsView()
{
	graphicsView = new QGraphicsView(this);
	graphicsView->setFixedSize(800, 600);
	graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	scene = new QGraphicsScene(0, 0, 1600, 1200, this);
	graphicsView->setScene(scene);

	// 3. 加载地图背景（替换为你的地图图片路径）
	mapItem = new QGraphicsPixmapItem(QPixmap(":/imagePng/PNG/POLICE_BACKGROUND.png").scaled(scene->width(), scene->height()));
	scene->addItem(mapItem);

	// 4. 加载人物精灵（替换为你的人物图片路径）
	policeItem = new Person(true);
	thiefItem = new Person(false);
	player = policeItem;  //默认值
	computer = thiefItem; //默认值

	int x = 24;
	int y = 69;
	this->m_pathPoints << QPoint(100 - x, 825 - y) << QPoint(350 - x, 700 - y) << QPoint(220 - x, 635 - y) << QPoint(610 - x, 440 - y) << QPoint(420 - x, 345 - y) << QPoint(670 - x, 220 - y)
					   << QPoint(930 - x, 350 - y) << QPoint(1190 - x, 220 - y) << QPoint(1500 - x, 375 - y) << QPoint(350 - x, 950 - y);
	m_nowtargetPointPolice = 0;
	m_nowtargetPointThief = 1;
	policeItem->setPos(this->m_pathPoints[9]);
	thiefItem->setPos(this->m_pathPoints[0]);

	policeItem->setMoveDirection(true, false, true, false, 0);
	thiefItem->setMoveDirection(true, false, false, true, 0);

	scene->addItem(policeItem);
	scene->addItem(thiefItem);
}

// 键盘按下事件（直接处理，无需转发）
void MapView::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape)
	{
		this->hide();
		this->timer_pause();
		emit needOperator(operatorType::GAMESETUP_POP);
	}
	else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
	{
		this->hide();
		this->timer_pause();
		emit allhide();
	}
	else
	{
		this->timer_start();
		QString string = event->text();
		bool ishit = this->statusBar->receiveHit(string);
		if (ishit)
		{
			emit needSound(soundType::Type);
			this->m_beatCount++;
		}
	}
}
// 键盘释放事件（直接处理）
void MapView::keyReleaseEvent(QKeyEvent *event)
{
	QWidget::keyReleaseEvent(event);
}

void MapView::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
}
void MapView::loadSetUp(bool isPolice, bool isCar1, bool isCar2, QString &StringPath)
{
	this->isPolice = isPolice;
	if (isPolice)
	{
		this->player = policeItem;
		this->computer = thiefItem;
	}
	else
	{
		this->player = thiefItem;
		this->computer = policeItem;
	}
	this->policeItem->loadSetUp(isCar1);
	this->thiefItem->loadSetUp(isCar2);
	this->statusBar->loadSetUp(isPolice, StringPath);
}
void MapView::updatebeatSpeed()
{
	this->m_beatSpeed = this->m_beatCount * 3;
	this->m_beatCount = 0;
}
void MapView::updatePersonPos()
{
	QPointF dir = this->policeItem->pos() - this->m_pathPoints[m_nowtargetPointPolice];
	float distance = dir.x() * dir.x() + dir.y() * dir.y();
	if (distance < 100)
	{
		switch (m_nowtargetPointPolice)
		{
		case 0:
		case 2:
		case 4:
		case 5:
		case 7:
		case 8:
		case 9:
			this->policeItem->setPos(this->m_pathPoints[m_nowtargetPointPolice]);
			this->policeItem->turnDirection(true);

			break;
		default:
			this->policeItem->setPos(this->m_pathPoints[m_nowtargetPointPolice]);
			this->policeItem->turnDirection(false);

			break;
		}
		if (this->policeItem->m_roateDirection == Person::CW)
		{
			this->m_nowtargetPointPolice = (m_nowtargetPointPolice + 1) % this->m_pathPoints.size();
		}
		else
		{
			this->m_nowtargetPointPolice = (m_nowtargetPointPolice - 1 + this->m_pathPoints.size()) % this->m_pathPoints.size();
		}
	}
	QPointF dir2 = this->thiefItem->pos() - this->m_pathPoints[m_nowtargetPointThief];
	float distance2 = dir2.x() * dir2.x() + dir2.y() * dir2.y();
	if (distance2 < 100)
	{
		switch (m_nowtargetPointThief)
		{
		case 0:
		case 2:
		case 4:
		case 5:
		case 7:
		case 8:
		case 9:
			this->thiefItem->setPos(this->m_pathPoints[m_nowtargetPointThief]);
			this->thiefItem->turnDirection(true);

			break;
		default:
			this->thiefItem->setPos(this->m_pathPoints[m_nowtargetPointThief]);
			this->thiefItem->turnDirection(false);

			break;
		}
		if (this->thiefItem->m_roateDirection == Person::CW)
		{
			this->m_nowtargetPointThief = (m_nowtargetPointThief + 1) % this->m_pathPoints.size();
			if ((m_nowtargetPointThief + 1) % this->m_pathPoints.size() == this->m_nowtargetPointPolice)
			{
				//先走两步
				this->player->setMoveDirection(false, false, false, false, m_beatSpeed);
				this->computer->setMoveDirection(false, false, false, false, 20);
				this->thiefItem->changeDirection();
				this->policeItem->changeDirection();
				this->m_nowtargetPointThief = (m_nowtargetPointThief - 1 + this->m_pathPoints.size()) % this->m_pathPoints.size();
				this->m_nowtargetPointPolice = (m_nowtargetPointPolice - 1 + this->m_pathPoints.size()) % this->m_pathPoints.size();
				emit needSound(soundType::TURN);
				return; //跳过失败判断
			}
		}
		else
		{
			this->m_nowtargetPointThief = (m_nowtargetPointThief - 1 + this->m_pathPoints.size()) % this->m_pathPoints.size();
			if ((m_nowtargetPointThief - 1 + this->m_pathPoints.size()) % this->m_pathPoints.size() == this->m_nowtargetPointPolice)
			{
				this->player->setMoveDirection(false, false, false, false, m_beatSpeed);
				this->computer->setMoveDirection(false, false, false, false, 20);
				this->thiefItem->changeDirection();
				this->policeItem->changeDirection();
				this->m_nowtargetPointThief = (m_nowtargetPointThief + 1) % this->m_pathPoints.size();
				this->m_nowtargetPointPolice = (m_nowtargetPointPolice + 1) % this->m_pathPoints.size();
				emit needSound(soundType::TURN);
				return;
			}
		}
	}
	this->player->setMoveDirection(false, false, false, false, m_beatSpeed);
	this->computer->setMoveDirection(false, false, false, false, 12);

	if (m_nowtargetPointThief == m_nowtargetPointPolice)
	{
		QPointF dir3 = this->thiefItem->pos() - this->policeItem->pos();
		float distance3 = dir3.x() * dir3.x() + dir3.y() * dir3.y();
		if (distance3 < 100)
		{
			this->hide();
			this->timer_pause();
			emit needSound(soundType::POLICEWIN);
			if (this->isPolice)
			{
				emit needOperator(operatorType::GAMEWIN_POP);
			}
			else
			{
				emit needOperator(operatorType::GAMEFAIL_POP);
			}
		}
	}

	graphicsView->centerOn(player->x(), player->y());
}
//槽函数
void MapView::timeout()
{
	if (this->isPolice)
	{
		this->hide();
		this->timer_pause();
		emit needOperator(operatorType::GAMEFAIL_POP);
		emit needSound(soundType::THIEFWIN);
	}
	else
	{
		this->hide();
		this->timer_pause();
		emit needOperator(operatorType::GAMEWIN_POP);
		emit needSound(soundType::POLICEWIN);
	}
}
void MapView::timer_pause()
{
	emit needOperator(operatorType::PAUSEBGM);
	this->timer->stop();
	this->timerBeatSpeed->stop();
}
void MapView::timer_start()
{
	emit needOperator(operatorType::PLAYBGM);
	this->timer->start(100);
	this->timerBeatSpeed->start(500);
}
void MapView::init()
{
	if (isPolice)
	{
		emit needSound(soundType::POLICE_ENTRY);
		this->player = policeItem;
		this->computer = thiefItem;
	}
	else
	{
		emit needSound(soundType::THIEF_ENTRY);
		this->player = thiefItem;
		this->computer = policeItem;
	}
	m_nowtargetPointPolice = 0;
	m_nowtargetPointThief = 1;
	policeItem->setPos(this->m_pathPoints[9]);
	thiefItem->setPos(this->m_pathPoints[0]);
	policeItem->init();
	thiefItem->init();
	this->m_beatSpeed = 0;
	this->m_beatCount = 0;

	policeItem->setMoveDirection(true, false, true, false, 0);
	thiefItem->setMoveDirection(true, false, false, true, 0);

	this->statusBar->init();
	graphicsView->centerOn(player->x(), player->y());

	//this->timer_start();
}
