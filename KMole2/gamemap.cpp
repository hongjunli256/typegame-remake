#include "gamemap.h"
//包括全图全资源的状态更新函数，但函数的调用依托于widget
const QPixmap &GameMap::pixLife()
{
	static const QPixmap pix(":/imagePng/PNG/MOLE_RADISH.png"); // 替换为你的图片路径
	return pix;
}
const QPixmap &GameMap::pixBackground()
{
	static const QPixmap pix(":/imagePng/PNG/MOLE_BACKGROUND.png"); // 替换为你的图片路径
	return pix;
}

void GameMap::loseVegetable()
{
	this->m_lifeNum--;
	if (this->m_lifeNum == 0)
	{
		emit needOperator(operatorType::GAMEFAIL_POP);
	}
}
GameMap::GameMap(QWidget *parent)
	: MyAbstractWidget{parent}
{
	this->move(0, 0);
	this->setFixedSize(this->pixBackground().size());

	this->m_timerRefresh = new QTimer(this);
	this->m_timerUpdate = new QTimer(this);
	connect(this->m_timerUpdate, &QTimer::timeout, this,
			[this]()
			{
				this->update();
			});
	connect(this->m_timerRefresh, &QTimer::timeout, this,
			[this]()
			{
				this->refresh();
			});
	this->initMousePool();
}

void GameMap::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);
	this->drawBackground(&painter);
	this->drawLifeNum(&painter);
	this->m_mousepool->drawMouse(&painter);
}
void GameMap::drawBackground(QPainter *painter)
{
	painter->drawPixmap(0, 0, this->pixBackground());
}
void GameMap::drawLifeNum(QPainter *painter)
{
	for (int i = 0; i < this->m_lifeNum; i++)
	{
		painter->drawPixmap(150 + i * (10 + this->pixLife().size().rwidth()), 500, this->pixLife());
	}
}
GameMap::~GameMap()
{

}
void GameMap::refresh()
{
	this->m_mousepool->cleanup(); //清理死老鼠
}
void GameMap::hitMouse(char targetChar)
{
	bool isHit_temp = this->m_mousepool->hitMouse(targetChar);
	emit isHit(isHit_temp);
}
void GameMap::timer_pause()
{
	this->m_timerRefresh->stop();
	this->m_timerUpdate->stop();
	this->m_mousepool->pause();
}
void GameMap::timer_start()
{
	this->m_timerRefresh->start(500);
	this->m_timerUpdate->start(100);
	this->m_mousepool->resume();
}

void GameMap::init()
{
	this->m_mousepool->init();
	this->m_lifeNum = 6;
}
void GameMap::loadSetUp(int gameTime, int spareTimeforMouse, int stayTime)
{
	this->m_mousepool->loadSetUp(gameTime, spareTimeforMouse, stayTime);
}
void GameMap::initMousePool()
{
	this->m_mousepool = new MousePool(this);
	connect(this->m_mousepool, &MousePool::stealVegetable, this, &GameMap::loseVegetable);
	connect(this->m_mousepool, &MousePool::needSound, this, &GameMap::needSound);
}
#include "gamemap.h"
//包括全图全资源的状态更新函数，但函数的调用依托于widget
