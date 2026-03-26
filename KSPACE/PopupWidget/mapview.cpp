#include "mapview.h"
#include <QFile>
#include <QInputDialog>
#include <QRandomGenerator>
void MapView::BGroll() //背景滚动槽函数
{
	this->mapItem->moveBy(0, 1 + this->EnemySpeed);
	if (this->mapItem->y() >= 600)
	{
		this->mapItem->setPos(this->generateSuitablePosX(), -200);
	}
}
QString MapView::getPlayerNickname()
{
	bool isInputValid;
	// 弹出输入对话框，设置默认提示文字
	QString nickname = QInputDialog::getText(this, "游戏得分记录", "请输入你的昵称：", QLineEdit::Normal,
											 "玩家", // 默认昵称
											 &isInputValid);

	// 输入状态反馈
	if (isInputValid && !nickname.isEmpty() && nickname != "玩家")
	{
		//qDebug() << "[输入成功] 玩家昵称：" << nickname;
		return nickname;
	}
	else
	{
		//qDebug() << "[输入取消/无效] 使用默认昵称：默认玩家";
		return "未输入名称";
	}
}
MapView::MapView(QWidget *parent)
	: MyAbstractWidget(parent)
{
	this->move(0, 0);
	this->setFixedSize(800, 600);
	this->createGraphicsView();

	this->statusBar = new StatusBar(this->graphicsView);
	connect(this->statusBar, &MyAbstractWidget::needOperator, this, &MyAbstractWidget::needOperator);
	connect(this->statusBar, &MyAbstractWidget::needSound, this, &MyAbstractWidget::needSound);

	statusBar->raise();

	this->initTimer();
	this->timer_pause();
	this->init();
	this->hide();
}
void MapView::createGraphicsView()
{
	graphicsView = new QGraphicsView(this);
	graphicsView->setFixedSize(800, 600);
	graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	scene = new QGraphicsScene(0, 0, 800, 600, this);
	scene->setBackgroundBrush(Qt::black);
	graphicsView->setScene(scene);
	this->player = new Player();
	this->scene->addItem(player);
	mapItem = new QGraphicsPixmapItem(QPixmap(":/imagePng/PNG/SPACE_BACKGROUND.png"));
	scene->addItem(mapItem);
	this->mapItem->setZValue(-1);
}
void MapView::initTimer()
{
	this->timerForCleanUp = new QTimer(this);
	this->timerForMove = new QTimer(this);
	connect(timerForCleanUp, &QTimer::timeout, this, &MapView::cleanUp);
	connect(timerForMove, &QTimer::timeout, this, &MapView::planeMove);
}
void MapView::timer_pause()
{
	this->timerForCleanUp->stop();
	this->timerForMove->stop();
}
void MapView::timer_start()
{
	this->timerForCleanUp->start(1000);
	this->timerForMove->start(100);
}
void MapView::cleanUp()
{
	QList<Enemy *> enemyDie;
	for (Enemy *enemy : std::as_const(this->m_enemyList))
	{
		if (enemy->isNeedRemove())
		{
			enemyDie.append(enemy);
		}
	}
	for (Enemy *apple : enemyDie)
	{
		this->removeEnemy(apple);
		this->addEnemy();
	}
	this->statusBar->refresh(this->score);
}
void MapView::init()
{
	QList<Enemy *> appleDie(this->m_enemyList);
	for (Enemy *apple : std::as_const(appleDie))
	{
		apple->toDie();
	}
	this->player->init();
	while (this->m_enemyList.size() < this->EnemyNum) //这里的初始数量能够作为难度依据
	{
		this->addEnemy();
	}
	this->score = 0;
	this->statusBar->init();
}
void MapView::planeMove()
{
	this->player->updatePos();
	for (Enemy *enemy : std::as_const(this->m_enemyList))
	{
		if (enemy->isAlive() && enemy->collidesWithItem(this->player))
		{
			enemy->toCollision();
			this->statusBar->loseHp();
			if (this->statusBar->isDie() && this->isVisible())
			{
				this->timer_pause();
				this->hide();
				emit allhide();
				emit needOperator(operatorType::PAUSEBGM);
				emit needChangeGameCondition(gameCondition::START);
				QString string = this->getPlayerNickname();
				emit newScore(string, this->score);
				emit needSound(soundType::PLANEEXPLOSION);
			}
		}
		if (!enemy->isNeedRemove())
		{
			enemy->updatePos();
		}
	}
	this->BGroll();
}
// 键盘按下事件（直接处理，无需转发）
void MapView::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape)
	{
		this->hide();
		this->timer_pause();
		emit this->allhide();
		emit needChangeGameCondition(gameCondition::PAUSE);
	}
	else
	{
		char c = event->key();
		for (Enemy *apple : std::as_const(this->m_enemyList))
		{
			bool isHit = apple->beHitten(c);
			if (isHit)
			{
				this->score += (this->EnemySpeed + 1);
				emit needSound(soundType::PLANEEXPLOSION);
				break;
			}
			else
			{
			}
		}
	}
}
void MapView::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
}
char MapView::generateRandomLetter()
{
	int randomNum = QRandomGenerator::global()->bounded(26); // 生成 0~25（左闭右开区间 [0,26)）
	return (randomNum + 'A');
}
int MapView::generateSuitablePosX()
{
	int randomNum = QRandomGenerator::global()->bounded(700);
	return randomNum;
}
int MapView::generateSuitablePosY()
{
	int randomNum = QRandomGenerator::global()->bounded(100);
	return -randomNum - 70;
}
void MapView::addEnemy()
{
	Enemy *enemy;
	char targetChar = this->generateRandomLetter();
	float fallTime = 1 + this->EnemySpeed + QRandomGenerator::global()->bounded(5);
	QPoint pos = QPoint(this->generateSuitablePosX(), this->generateSuitablePosY());
	if (this->m_enemyWaitList.isEmpty())
	{
		enemy = new Enemy(targetChar, fallTime, pos);
		enemy->updatePos();
	}
	else
	{
		enemy = this->m_enemyWaitList.first();
		this->m_enemyWaitList.removeFirst();
		enemy->changeState(targetChar, fallTime, pos);
	}
	this->scene->addItem(enemy);
	this->m_enemyList.append(enemy);
	return;
}
void MapView::removeEnemy(Enemy *enemy)
{
	this->m_enemyList.removeOne(enemy);
	this->scene->removeItem(enemy);
	this->m_enemyWaitList.append(enemy);
}
void MapView::loadSetUp(int enemyNum, float enemySpeed, bool isReward)
{
	this->EnemyNum = enemyNum;
	this->EnemySpeed = enemySpeed;
	this->isReward = isReward;
}
