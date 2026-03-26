#include "widget.h"
#include <QKeyEvent>
#include <QSettings>
//widget作为总事件管理器
Widget::Widget(QWidget *parent)
	: QWidget(parent)
{
	this->move(0, 0);
	this->setFixedSize(800, 600);
	this->m_gameMap = new GameMap(this);
	connect(this->m_gameMap, &GameMap::needOperator, this, &Widget::handleOperator);
	connect(this->m_gameMap, &GameMap::needChangeGameCondition, this, &Widget::changeGameCondition);

	this->m_uiLayer = new UILayer(this);
	connect(this->m_uiLayer, &UILayer::needOperator, this, &Widget::handleOperator);
	connect(this->m_uiLayer, &UILayer::needChangeGameCondition, this, &Widget::changeGameCondition);

	this->m_popWidgetsManager = new PopWidgetsManager(this);
	connect(this->m_popWidgetsManager, &PopWidgetsManager::needChangeGameCondition, this, &Widget::changeGameCondition);
	connect(this->m_popWidgetsManager, &PopWidgetsManager::needOperator, this, &Widget::handleOperator);
	connect(this->m_popWidgetsManager, &PopWidgetsManager::changeSetUp, this, &Widget::changeSetUp);

	this->m_gameMedia = new GameMedia(this);

	setMouseTracking(true);

	connect(this->m_uiLayer, &UILayer::needSound, this->m_gameMedia, &GameMedia::playSound);
	connect(this->m_uiLayer, &UILayer::needBGM, this->m_gameMedia, &GameMedia::playBGM);
	connect(this->m_uiLayer, &UILayer::needPauseBGM, this->m_gameMedia, &GameMedia::pauseBGM);
	connect(this->m_gameMap, &GameMap::needSound, this->m_gameMedia, &GameMedia::playSound);
	connect(this, &Widget::needSound, this->m_gameMedia, &GameMedia::playSound);

	this->changeGameCondition(gameCondition::READYTOPLAY);
	this->loadConfig();
	return;
}
Widget::~Widget()
{
	this->saveConfig();
}

void Widget::paintEvent(QPaintEvent *event)
{
	this->m_gameMap->update();
	this->m_popWidgetsManager->update();
	this->m_uiLayer->update();
}
void Widget::keyPressEvent(QKeyEvent *event)
{
	//qDebug() << "Key pressed:" << event->key() << "Game condition:" << this->m_gameCondition << "Has focus:" << this->hasFocus(); // 检查焦点
	if (this->m_gameCondition == gameCondition::CONTINUE)
	{
		if (event->key() >= Qt::Key_A && event->key() <= Qt::Key_Z)
		{
			this->m_gameMap->hitWord(event->text());
		}
	}
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
		case operatorType::GAMEINIT:
			this->init();
			break;
		case operatorType::GAMETIMER_START:
			this->timer_start();
			break;
		case operatorType::GAMETIMER_STOP:
			this->timer_pause();
			break;
		case operatorType::GAMERESUME:
			this->resume();
			break;
		case operatorType::GAMEHARDER_ONE:
			this->nextlevel();
			break;
		case operatorType::GLOBALSETTING:
			this->globalSetUp();
			break;
		default:
			break;
		}
	}
}
void Widget::timer_start()
{
	this->m_gameMap->timer_start();
	this->m_uiLayer->timer_start();
}
void Widget::timer_pause()
{
	this->m_gameMap->timer_pause();
	this->m_uiLayer->timer_pause();
}
void Widget::init()
{
	this->m_gameMap->init();
	this->m_uiLayer->init();
}
void Widget::resume()
{
	if (this->m_gameCondition == gameCondition::CONTINUE)
	{
		this->changeGameCondition(gameCondition::PAUSE);
		this->timer_pause();
	}
	else if (this->m_gameCondition == gameCondition::PAUSE)
	{
		this->changeGameCondition(gameCondition::CONTINUE);
		this->timer_start();
	}
	else if (this->m_gameCondition == gameCondition::READYTOPLAY)
	{
		this->timer_pause();
	}
}
void Widget::nextlevel()
{
	if (this->m_gameLevel < 9)
	{
		this->m_gameLevel++;
	}
	this->globalSetUp();
}
void Widget::changeGameCondition(gameCondition condition)
{
	this->m_gameCondition = condition;
	this->m_uiLayer->changeGameCondition(condition);
}
//设置相关
void Widget::globalSetUp()
{
	this->m_gameMap->loadSetUp(this->m_gameLevel, this->m_selectedDifficulty);
	this->m_popWidgetsManager->loadSetUp(this->m_gameLevel, this->m_selectedDifficulty);
}
void Widget::changeSetUp(int gameLevel, QString selectedDifficulty)
{
	this->m_gameLevel = gameLevel;
	this->m_selectedDifficulty = selectedDifficulty;
}
void Widget::loadConfig()
{
	QSettings setting("KFrogConfig.ini", QSettings::IniFormat);
	this->m_gameLevel = setting.value("GameLevel").toInt();
	this->m_selectedDifficulty = setting.value("GameDifficulty").toString();
	this->globalSetUp();
}
void Widget::saveConfig()
{
	QSettings setting("KFrogConfig.ini", QSettings::IniFormat);
	setting.setValue("GameLevel", m_gameLevel);
	setting.setValue("GameDifficulty", m_selectedDifficulty);
}
