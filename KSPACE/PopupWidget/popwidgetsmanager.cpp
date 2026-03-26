#include "popwidgetsmanager.h"

PopWidgetsManager::PopWidgetsManager(QWidget *parent)
	: MyAbstractWidget{parent}
{
	this->move(0, 0);
	this->resize(800, 600);

	//创建子界面
	this->createWidgetSetUp();
	this->createMapView();
	this->createWidgetRankList();
	this->createWidgetSetUpSure();

	this->createWidgetExit();

	connect(this->m_mapView, &MapView::newScore, this->m_widgetRankList, &WidgetRankList::addGameScore);

	this->hide();
}
void PopWidgetsManager::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
}
void PopWidgetsManager::createWidgetRankList()
{
	this->m_widgetRankList = new WidgetRankList(this);
	connect(this->m_widgetRankList, &MyAbstractWidget::needOperator, this, &MyAbstractWidget::needOperator);
	connect(this->m_widgetRankList, &MyAbstractWidget::needSound, this, &MyAbstractWidget::needSound);
	connect(this->m_widgetRankList, &WidgetSetUp::allhide, this, &PopWidgetsManager::hide);
}
void PopWidgetsManager::createWidgetSetUp()
{
	this->m_widgetSetUp = new WidgetSetUp(this);
	connect(this->m_widgetSetUp, &MyAbstractWidget::needOperator, this, &MyAbstractWidget::needOperator);
	connect(this->m_widgetSetUp, &MyAbstractWidget::needSound, this, &MyAbstractWidget::needSound);
	connect(this->m_widgetSetUp, &WidgetSetUp::allhide, this, &PopWidgetsManager::hide);
	connect(this->m_widgetSetUp, &WidgetSetUp::changeSetUp, this, &PopWidgetsManager::changeSetUp);
}

void PopWidgetsManager::createMapView()
{
	this->m_mapView = new MapView(this);
	connect(this->m_mapView, &MapView::needOperator, this, &MyAbstractWidget::needOperator);
	connect(this->m_mapView, &MapView::needSound, this, &MyAbstractWidget::needSound);
	connect(this->m_mapView, &MapView::allhide, this, &PopWidgetsManager::hide);
	connect(this->m_mapView, &MyAbstractWidget::needChangeGameCondition, this, &MyAbstractWidget::needChangeGameCondition);
}

void PopWidgetsManager::createWidgetExit()
{
	this->m_widgetExit = new WidgetExit(this);
	connect(this->m_widgetExit, &MyAbstractWidget::needOperator, this, &MyAbstractWidget::needOperator);
	connect(this->m_widgetExit, &MyAbstractWidget::needSound, this, &MyAbstractWidget::needSound);
	connect(this->m_widgetExit, &WidgetExit::allhide, this, &PopWidgetsManager::hide);
}

void PopWidgetsManager::createWidgetSetUpSure()
{
	this->m_widgetSetUpSure = new widgetSetUpSure(this);
	connect(this->m_widgetSetUpSure, &MyAbstractWidget::needOperator, this, &MyAbstractWidget::needOperator);
	connect(this->m_widgetSetUpSure, &MyAbstractWidget::needChangeGameCondition, this, &MyAbstractWidget::needChangeGameCondition);
	connect(this->m_widgetSetUpSure, &MyAbstractWidget::needSound, this, &MyAbstractWidget::needSound);
	connect(this->m_widgetSetUpSure, &widgetSetUpSure::allhide, this, &PopWidgetsManager::hide);
}
void PopWidgetsManager::loadSetUp(int enemyNum, float enemySpeed, bool isReward)
{
	this->m_mapView->loadSetUp(enemyNum, enemySpeed, isReward);
	this->m_widgetSetUp->loadSetUp(enemyNum, enemySpeed, isReward);
}
void PopWidgetsManager::PopUp(operatorType type)
{
	this->show();
	emit needOperator(operatorType::GAMERESUME);
	switch (type)
	{
	case operatorType::RANKLIST_POP:

		this->m_widgetRankList->show();
		break;
	case operatorType::GAMESETUP_POP:

		this->m_widgetSetUp->show();
		break;
	case operatorType::GAMESETUP_SURE_POP:

		this->m_widgetSetUpSure->show();
		break;
	case operatorType::GAMEMAP_POP:

		this->m_mapView->init();
		this->m_mapView->timer_start();
		this->m_mapView->setFocus();
		this->m_mapView->show();
		break;
	case operatorType::GAMEMAP_RETURN:

		//this->m_mapView->init();
		this->m_mapView->timer_start();
		this->m_mapView->setFocus();
		this->m_mapView->show();
		break;

	case operatorType::GAMEEXIT_POP:

		this->m_widgetExit->show();
		break;

	default:
		break;
	}
}
