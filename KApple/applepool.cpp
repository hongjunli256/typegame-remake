#include "applepool.h"
#include<QSettings>
char ApplePool::generateRandomLetter()
{
	int randomNum = QRandomGenerator::global()->bounded(26); // 生成 0~25（左闭右开区间 [0,26)）
	return (randomNum + 'A');
}
double ApplePool::generateSpeedFactor()
{
	int randomNum = QRandomGenerator::global()->bounded(5); // 生成 0~25（左闭右开区间 [0,26)）
	return randomNum;
}
int ApplePool::generateSuitablePosX()
{
	int randomNum = QRandomGenerator::global()->bounded(700);
	return randomNum;
}

ApplePool::ApplePool(QWidget *parent)
	: MyAbstractWidget(parent)
{
	this->init();
}

ApplePool::~ApplePool() {}

void ApplePool::addApple()
{
	int fallTime = this->m_fallTime + this->generateSpeedFactor();
	Apple *apple;
	char targetChar = this->generateRandomLetter();
	int posX = this->generateSuitablePosX();
	if (this->m_appleWaitList.isEmpty())
	{
		apple = new Apple(this, targetChar, fallTime, posX);
		connect(apple, &Apple::needSound, this, &ApplePool::needSound);
		connect(apple, &Apple::appleBroken, this, &ApplePool::appleBroken);
	}
	else
	{
		apple = this->m_appleWaitList.first();
		this->m_appleWaitList.removeFirst();
		apple->changeState(targetChar, fallTime, posX);
	}
	this->m_appleList.append(apple);
	return;
}

void ApplePool::removeApple(Apple *apple)
{
	this->m_appleList.removeOne(apple);
	this->m_appleWaitList.append(apple);
}

void ApplePool::cleanup()
{
	QList<Apple *> mouseDie;
	for (Apple *apple : std::as_const(this->m_appleList))
	{
		if (apple->m_condition == Apple::condition::DIE)
		{
			mouseDie.append(apple);
		}
	}
	for (Apple *apple : mouseDie)
	{
		this->removeApple(apple);
		this->addApple();
	}
}
void ApplePool::drawApple(QPainter *painter)
{
	for (Apple *apple : std::as_const(this->m_appleList))
	{
		apple->draw(painter);
	}
}
void ApplePool::hitMouse(char targetChar)
{
	for (Apple *apple : std::as_const(this->m_appleList))
	{
		if (apple->m_targetChar == targetChar && apple->m_isCanHit == true)
		{
			apple->beHitten();
			this->m_pickCount++;
			if (this->m_pickCount >= this->m_winNum)
			{
				emit needOperator(operatorType::GAMEWIN_POP);
			}
			return;
		}
	}
	return;
}
void ApplePool::pause()
{
	for (Apple *apple : std::as_const(this->m_appleList))
	{
		apple->m_timer->stop();
	}
}
void ApplePool::resume()
{
	for (Apple *apple : std::as_const(this->m_appleList))
	{
		apple->m_timer->start(5 * m_fallTime);
	}
}
void ApplePool::init()
{
	QList<Apple *> appleDie(this->m_appleList);
	for (Apple *apple : std::as_const(appleDie))
	{
		apple->toDie();
	}
	this->m_breakCount = 0;
	this->m_pickCount = 0;
	while (this->m_appleList.size() < 5) //这里的初始数量能够作为难度依据
	{
		this->addApple();
	}
}
void ApplePool::loadSetUp(int winNum, int failNum, int gameLevel)
{
	this->m_winNum = winNum;
	this->m_failNum = failNum;
	this->m_gameLevel = gameLevel;
	this->m_fallTime = 2 + 0.5 * (9 - this->m_gameLevel);
}
void ApplePool::appleBroken()
{
	this->m_breakCount++;
	if (this->m_breakCount >= this->m_failNum)
	{
		emit needOperator(operatorType::GAMEFAIL_POP);
	}
}
