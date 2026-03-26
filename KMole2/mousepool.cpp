#include "mousepool.h"
#include<QSettings>
char MousePool::generateRandomLetter()
{
	int randomNum = QRandomGenerator::global()->bounded(26); // 生成 0~25（左闭右开区间 [0,26)）
	return (randomNum + 'A');
}
int MousePool::generateSuitablePos()
{
	QPoint point;
	QList<int> emptyPos;
	for (int i = 0; i < 10; i++)
	{
		if (isThereRat[i] == 0)
		{
			emptyPos.append(i);
		}
	}
	if (emptyPos.size() == 0)
	{
		return -1;
	}
	int randomNum = QRandomGenerator::global()->bounded(emptyPos.size());
	return emptyPos[randomNum];
}

MousePool::MousePool(QWidget *parent)
	: MyAbstractWidget(parent)
{
	this->m_timerAddMouse = new QTimer(this);
	this->init();
	connect(this->m_timerAddMouse, &QTimer::timeout, this,
			[this]()
			{
				this->addRat(this->m_stayTime);
				this->m_timerAddMouse->stop();
			});
}

MousePool::~MousePool() {}

void MousePool::addRat(int stayTime)
{
	Rat *rat;
	char targetChar = this->generateRandomLetter();
	int posForArray = generateSuitablePos();
	if (posForArray != -1)
	{
		if (this->m_ratWaitList.isEmpty())
		{
			rat = new Rat(this, targetChar, stayTime, posForArray);
			connect(rat, &Rat::stealVegetable, this, &MousePool::stealVegetable);
			connect(rat, &Rat::needSound, this, &MousePool::needSound);
		}
		else
		{
			rat = this->m_ratWaitList.first();
			this->m_ratWaitList.removeFirst();
			rat->changeState(targetChar, stayTime, posForArray);
		}
		this->isThereRat[posForArray] = 1;
		this->m_ratList.append(rat);
		return;
	}
}

void MousePool::removeRat(Rat *rat)
{
	this->m_ratList.removeOne(rat);
	this->m_ratWaitList.append(rat);
}

void MousePool::cleanup()
{
	QList<Rat *> mouseDie;
	for (Rat *rat : std::as_const(this->m_ratList))
	{
		if (rat->m_condition == Rat::condition::DIE)
		{
			mouseDie.append(rat);
			if (this->m_spareTimeforMouse != 0 && !this->m_timerAddMouse->isActive())
			{
				this->m_timerAddMouse->start(this->m_spareTimeforMouse * 1000);
			}
			else if (this->m_spareTimeforMouse == 0)
			{
				this->addRat(this->m_stayTime);
			}
		}
	}
	for (Rat *rat : mouseDie)
	{
		this->isThereRat[rat->m_posForArray] = 0;
		this->removeRat(rat);
	}
}
void MousePool::drawMouse(QPainter *painter)
{
	for (Rat *rat : std::as_const(this->m_ratList))
	{
		rat->draw(painter);
	}
}

bool MousePool::hitMouse(char targetChar)
{
	for (Rat *rat : std::as_const(this->m_ratList))
	{
		if (rat->m_targetChar == targetChar && rat->m_isCanHit == true)
		{
			rat->beHitten();
			return true;
		}
	}
	return false;
}

void MousePool::pause()
{
	for (Rat *rat : std::as_const(this->m_ratList))
	{
		rat->m_timer->stop();
	}
}
void MousePool::resume()
{
	while (this->m_ratList.size() < 4) //这里的初始数量能够作为难度依据
	{
		this->addRat(this->m_stayTime);
	}
	for (Rat *rat : std::as_const(this->m_ratList))
	{
		rat->m_timer->start(500);
	}
}
void MousePool::init()
{
	QList<Rat *> mouseDie(this->m_ratList);
	for (Rat *rat : std::as_const(mouseDie))
	{
		rat->toDie();
	}
}

void MousePool::loadSetUp(int stayTime, int spareTimeforMouse, int gameTime)
{
	this->m_spareTimeforMouse = spareTimeforMouse;
	this->m_stayTime = stayTime;
}
