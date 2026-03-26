#include "gamemap.h"
//包括全图全资源的状态更新函数，但函数的调用依托于widget
const QPixmap &GameMap::pixBasket()
{
	static const QPixmap pix(":/imagePng/PNG/APPLE_BASKET.png"); // 替换为你的图片路径
	return pix;
}
const QPixmap& GameMap::pixBackground()
{
	static const QPixmap pix(":/imagePng/PNG/APPLE_BACKGROUND.png"); // 替换为你的图片路径
	return pix;
}

GameMap::GameMap(QWidget *parent)
	: MyAbstractWidget{parent}
{
	this->move(0, 0);
	this->setFixedSize(this->pixBackground().size());

    this->m_timerRefresh=new QTimer(this);
    this->m_timerUpdate=new QTimer(this);
    connect(this->m_timerUpdate,&QTimer::timeout,this,[this](){
        this->update();
    });
    connect(this->m_timerRefresh,&QTimer::timeout,this,[this](){
        this->refresh();
    });

	this->initApplePool();
}

void GameMap::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    this->drawBackground(&painter);
	this->drawBasket(&painter);
	this->m_applePool->drawApple(&painter);
}
void GameMap::drawBackground(QPainter*painter)
{
    painter->drawPixmap(0,0,this->pixBackground());
}
void GameMap::drawBasket(QPainter *painter)
{
	painter->drawPixmap(600, 450, this->pixBasket());
}
GameMap::~GameMap()
{

}
void GameMap::refresh()
{
	this->m_applePool->cleanup();
}
void GameMap::hitApple(char targetChar)
{
	this->m_applePool->hitMouse(targetChar);
}
void GameMap::timer_pause()
{
    this->m_timerRefresh->stop();
    this->m_timerUpdate->stop();
	this->m_applePool->pause();
}
void GameMap::timer_start()
{
    this->m_timerRefresh->start(500);
    this->m_timerUpdate->start(100);
	this->m_applePool->resume();
}
void GameMap::init()
{
	this->m_applePool->init();
}
void GameMap::loadSetUp(int winNum, int failNum, int gameLevel)
{
	this->m_applePool->loadSetUp(winNum, failNum, gameLevel);
}
void GameMap::initApplePool()
{
	this->m_applePool = new ApplePool(this);
	this->m_applePool->init();
	connect(this->m_applePool, &ApplePool::needOperator, this, &GameMap::needOperator);
	connect(this->m_applePool, &ApplePool::needSound, this, &GameMap::needSound);
}
