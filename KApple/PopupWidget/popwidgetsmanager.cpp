#include "popwidgetsmanager.h"

PopWidgetsManager::PopWidgetsManager(QWidget *parent)
	: MyAbstractWidget{parent}
{
	this->move(0, 0);
	this->resize(800, 600);

	//创建子界面
	this->createWidgetSetUp();
	this->createWidgetSetUpSure();

	this->createWidgetExit();

	this->createWidgetWin();
	this->createWidgetFail();
	this->hide();
}
void PopWidgetsManager::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
}
void PopWidgetsManager::createWidgetSetUp()
{
	this->m_widgetSetUp = new WidgetSetUp(this);
	connect(this->m_widgetSetUp, &MyAbstractWidget::needOperator, this, &MyAbstractWidget::needOperator);
	connect(this->m_widgetSetUp, &MyAbstractWidget::needChangeGameCondition, this, &MyAbstractWidget::needChangeGameCondition);
	connect(this->m_widgetSetUp, &MyAbstractWidget::needSound, this, &MyAbstractWidget::needSound);
	connect(this->m_widgetSetUp, &WidgetSetUp::allhide, this, &PopWidgetsManager::hide);
	connect(this->m_widgetSetUp, &WidgetSetUp::changeSetUp, this, &PopWidgetsManager::changeSetUp);
}

void PopWidgetsManager::createWidgetSetUpSure()
{
	this->m_widgetSetUpSure = new widgetSetUpSure(this);
	connect(this->m_widgetSetUpSure, &MyAbstractWidget::needOperator, this, &MyAbstractWidget::needOperator);
	connect(this->m_widgetSetUpSure, &MyAbstractWidget::needChangeGameCondition, this, &MyAbstractWidget::needChangeGameCondition);
	connect(this->m_widgetSetUpSure, &MyAbstractWidget::needSound, this, &MyAbstractWidget::needSound);
	connect(this->m_widgetSetUpSure, &widgetSetUpSure::allhide, this, &PopWidgetsManager::hide);
}

void PopWidgetsManager::createWidgetExit()
{
	this->m_widgetExit = new WidgetExit(this);
	connect(this->m_widgetExit, &MyAbstractWidget::needOperator, this, &MyAbstractWidget::needOperator);
	connect(this->m_widgetExit, &MyAbstractWidget::needChangeGameCondition, this, &MyAbstractWidget::needChangeGameCondition);
	connect(this->m_widgetExit, &MyAbstractWidget::needSound, this, &MyAbstractWidget::needSound);
	connect(this->m_widgetExit, &WidgetExit::allhide, this, &PopWidgetsManager::hide);
}

void PopWidgetsManager::createWidgetWin()
{
	this->m_widgetWin = new WidgetWin(this);
	connect(this->m_widgetWin, &MyAbstractWidget::needOperator, this, &MyAbstractWidget::needOperator);
	connect(this->m_widgetWin, &MyAbstractWidget::needChangeGameCondition, this, &MyAbstractWidget::needChangeGameCondition);
	connect(this->m_widgetWin, &MyAbstractWidget::needSound, this, &MyAbstractWidget::needSound);
	connect(this->m_widgetWin, &WidgetWin::allhide, this, &PopWidgetsManager::hide);
}

void PopWidgetsManager::createWidgetFail()
{
	this->m_widgetFail = new WidgetFail(this);
	connect(this->m_widgetFail, &MyAbstractWidget::needOperator, this, &MyAbstractWidget::needOperator);
	connect(this->m_widgetFail, &MyAbstractWidget::needChangeGameCondition, this, &MyAbstractWidget::needChangeGameCondition);
	connect(this->m_widgetFail, &MyAbstractWidget::needSound, this, &MyAbstractWidget::needSound);
	connect(this->m_widgetFail, &WidgetFail::allhide, this, &PopWidgetsManager::hide);
}
void PopWidgetsManager::loadSetUp(int winNum, int failNum, int gameLevel)
{
	this->m_widgetSetUp->loadSetUp(winNum, failNum, gameLevel);
}
void PopWidgetsManager::PopUp(operatorType type)
{
	this->show();
	emit needOperator(operatorType::GAMERESUME);
	switch (type)
	{
	case operatorType::GAMESETUP_POP:

		this->m_widgetSetUp->show();
		break;

	case operatorType::GAMESETUP_SURE_POP:

		this->m_widgetSetUpSure->show();
		break;

	case operatorType::GAMEEXIT_POP:

		this->m_widgetExit->show();
		break;

	case operatorType::GAMEWIN_POP:

		this->m_widgetWin->show();
		break;

	case operatorType::GAMEFAIL_POP:

		this->m_widgetFail->show();
		break;

	default:
		break;
	}
}
