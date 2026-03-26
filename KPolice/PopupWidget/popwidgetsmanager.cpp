#include "popwidgetsmanager.h"

PopWidgetsManager::PopWidgetsManager(QWidget *parent)
	: MyAbstractWidget{parent}
{
	this->move(0, 0);
	this->resize(800, 600);

	//创建子界面
	this->createWidgetSetUp();
	this->createMapView();
	this->createMultiWidget();

	this->createWidgetExit();

	this->createWidgetWin();
	this->createWidgetFail();

	this->hide();
}
void PopWidgetsManager::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
}
void PopWidgetsManager::createMultiWidget()
{
	this->m_multiWidget = new MultiWidget(this);
	connect(this->m_multiWidget, &MyAbstractWidget::needOperator, this, &MyAbstractWidget::needOperator);
	connect(this->m_multiWidget, &MyAbstractWidget::needSound, this, &MyAbstractWidget::needSound);
	connect(this->m_multiWidget, &WidgetSetUp::allhide, this, &PopWidgetsManager::hide);
	//connect(this->m_multiWidget, &WidgetSetUp::changeSetUp, this, &PopWidgetsManager::changeSetUp);
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
}

void PopWidgetsManager::createWidgetExit()
{
	this->m_widgetExit = new WidgetExit(this);
	connect(this->m_widgetExit, &MyAbstractWidget::needOperator, this, &MyAbstractWidget::needOperator);
	connect(this->m_widgetExit, &MyAbstractWidget::needSound, this, &MyAbstractWidget::needSound);
	connect(this->m_widgetExit, &WidgetExit::allhide, this, &PopWidgetsManager::hide);
}

void PopWidgetsManager::createWidgetWin()
{
	this->m_widgetWin = new WidgetWin(this);
	connect(this->m_widgetWin, &MyAbstractWidget::needOperator, this, &MyAbstractWidget::needOperator);
	connect(this->m_widgetWin, &MyAbstractWidget::needSound, this, &MyAbstractWidget::needSound);
	connect(this->m_widgetWin, &WidgetWin::allhide, this, &PopWidgetsManager::hide);
}

void PopWidgetsManager::createWidgetFail()
{
	this->m_widgetFail = new WidgetFail(this);
	connect(this->m_widgetFail, &MyAbstractWidget::needOperator, this, &MyAbstractWidget::needOperator);
	connect(this->m_widgetFail, &MyAbstractWidget::needSound, this, &MyAbstractWidget::needSound);
	connect(this->m_widgetFail, &WidgetFail::allhide, this, &PopWidgetsManager::hide);
}
void PopWidgetsManager::loadSetUp(bool isPolice, bool isCar1, bool isCar2, QString StringPath)
{
	this->m_widgetSetUp->loadSetUp(isPolice, isCar1, isCar2);
	this->m_mapView->loadSetUp(isPolice, isCar1, isCar2, StringPath);
	this->m_widgetWin->loadSetUp(isPolice);
	this->m_widgetFail->loadSetUp(isPolice);
}
void PopWidgetsManager::PopUp(operatorType type)
{
	this->show();
	emit needOperator(operatorType::GAMERESUME);
	switch (type)
	{
	case operatorType::GAMEMULTI_POP:

		this->m_multiWidget->show();
		break;
	case operatorType::GAMESETUP_POP:

		this->m_widgetSetUp->show();
		break;
	case operatorType::GAMEMAP_POP:

		this->m_mapView->init();
		this->m_mapView->show();
		this->m_mapView->setFocus();
		break;

	case operatorType::GAMEEXIT_POP:

		this->m_widgetExit->show();
		break;

	case operatorType::GAMEWIN_POP:

		this->m_widgetWin->show();
		this->m_widgetWin->setFocus();
		break;

	case operatorType::GAMEFAIL_POP:

		this->m_widgetFail->show();
		this->m_widgetFail->setFocus();
		break;

	default:
		break;
	}
}
