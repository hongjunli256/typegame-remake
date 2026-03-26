#include "widget.h"
#include<QKeyEvent>
#include <QSettings>
//widget作为总事件管理器
const QPixmap &Widget::pixWidget()
{
	static const QPixmap pix(":/imagePng/PNG/POLICE_MAINMENU_BG.png");
	return pix;
}
Widget::Widget(QWidget *parent)
	: MyAbstractWidget(parent)
{
	this->move(0, 0);
	this->setFixedSize(800, 600);

	this->initButton();
	connect(this, &Widget::needOperator, this, &Widget::handleOperator);

	this->initPopWidgetManager();
	setMouseTracking(true);

	this->m_gameMedia = new GameMedia(this);

	connect(this, &Widget::needSound, this->m_gameMedia, &GameMedia::playSound);
	connect(this->m_popWidgetsManager, &MyAbstractWidget::needSound, this->m_gameMedia, &GameMedia::playSound);
	this->loadConfig();
	return;
}
Widget::~Widget()
{
	this->saveConfig();
}
void Widget::initButton()
{
	this->m_buttonSinglePlay = new ImageButton(":/imagePng/PNG/POLICE_MAINMENU_SINGLE.png", this, QPoint(438, 336), 3);
	this->m_buttonMulitiPlay = new ImageButton(":/imagePng/PNG/POLICE_MAINMENU_MULTI.png", this, QPoint(438, 394), 3);
	this->m_buttonExit = new ImageButton(":/imagePng/PNG/POLICE_MAINMENU_EXIT.png", this, QPoint(438, 452), 3);
	connect(this->m_buttonSinglePlay, &ImageButton::clicked, this, &Widget::m_buttonSinglePlay_clicked);
	connect(this->m_buttonMulitiPlay, &ImageButton::clicked, this, &Widget::m_buttonMulitiPlay_clicked);
	connect(this->m_buttonExit, &ImageButton::clicked, this, &Widget::m_buttonExit_clicked);

	QList<ImageButton *> btnList = {this->m_buttonSinglePlay, this->m_buttonMulitiPlay, this->m_buttonExit};
	for (ImageButton *btn : btnList)
	{
		connect(btn, &ImageButton::needSound, this, &Widget::needSound);
	}
}
void Widget::initPopWidgetManager()
{
	this->m_popWidgetsManager = new PopWidgetsManager(this);

	connect(this->m_popWidgetsManager, &PopWidgetsManager::needOperator, this, &Widget::handleOperator);
	connect(this->m_popWidgetsManager, &PopWidgetsManager::changeSetUp, this, &Widget::changeSetUp);
}
void Widget::m_buttonSinglePlay_clicked()
{
	emit needOperator(operatorType::GAMESETUP_POP);
}
void Widget::m_buttonMulitiPlay_clicked()
{
	emit needOperator(operatorType::GAMEMULTI_POP);
}
void Widget::m_buttonExit_clicked()
{
	emit needOperator(operatorType::GAMEEXIT_POP);
}
void Widget::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);
	painter.drawPixmap(0, 0, this->pixWidget());
	this->m_buttonExit->draw(&painter);
	this->m_buttonSinglePlay->draw(&painter);
	this->m_buttonMulitiPlay->draw(&painter);
	this->m_popWidgetsManager->update();
}
void Widget::handleOperator(operatorType type)
{
	if (type < operatorType::ISPOP)
	{
		this->m_popWidgetsManager->PopUp(type);
		return;
	}
	else
	{
		switch (type)
		{
		case operatorType::GLOBALSETTING:
			this->globalSetUp();
			break;
		case operatorType::PAUSEBGM: //简单放这了
			this->m_gameMedia->pauseBGM();
			break;
		case operatorType::PLAYBGM:
			this->m_gameMedia->playBGM(BGMtype::NORMAL);
			break;
		default:
			break;
		}
	}
}
//设置相关
void Widget::globalSetUp()
{
	this->m_popWidgetsManager->loadSetUp(isPolice, isCar1, isCar2, "");
}
void Widget::changeSetUp(bool isPolice, bool isCar1, bool isCar2, QString StringPath)
{
	this->isPolice = isPolice;
	this->isCar1 = isCar1;
	this->isCar2 = isCar2;
	this->m_popWidgetsManager->loadSetUp(isPolice, isCar1, isCar2, StringPath);
}
void Widget::loadConfig()
{
	QSettings setting("KPoliceConfig.ini", QSettings::IniFormat);
	this->isPolice = setting.value("isPolice").toBool();
	this->isCar1 = setting.value("isCar1").toBool();
	this->isCar2 = setting.value("isCar2").toBool();
	this->globalSetUp();
}
void Widget::saveConfig()
{
	QSettings setting("KPoliceConfig.ini", QSettings::IniFormat);
	setting.setValue("isPolice", isPolice);
	setting.setValue("isCar1", isCar1);
	setting.setValue("isCar2", isCar2);
}
