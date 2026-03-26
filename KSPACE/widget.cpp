#include "widget.h"
#include <QKeyEvent>
#include <QSettings>
#include "PopupWidget/popwidgetsmanager.h"
//widget作为总事件管理器
//目前进度已经完成了状态栏，明天完成mapview，背景滚动，
//还有子弹类，子弹的曲线设计就算了，正常射过去吧，写完之后相互的联动也就只有setting和score了
//开发完单字部分参考青蛙完成textbar
//然后游戏部分尽量写一个框架，力求周五前完成全部
//好多啊哥们不会写不完吧，单词，单飞机子弹，参考一下apple看能不能解决吧
const QPixmap &Widget::pixWidget()
{
	static const QPixmap pix(":/imagePng/PNG/SPACE_MAINMENU_BG.png");
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

	this->loadConfig();
	return;
}
Widget::~Widget()
{
	this->saveConfig();
}
void Widget::initButton()
{
	this->m_buttonStart = new ImageButton(":/imagePng/PNG/SPACE_START.png", this, QPoint(256, 288), 3);
	this->m_buttonRankList = new ImageButton(":/imagePng/PNG/SPACE_HISCORE.png", this, QPoint(256, 332), 3);
	this->m_buttonSetUp = new ImageButton(":/imagePng/PNG/SPACE_OPTION.png", this, QPoint(256, 376), 3);
	this->m_buttonExit = new ImageButton(":/imagePng/PNG/SPACE_EXIT.png", this, QPoint(256, 420), 3);
	connect(this->m_buttonSetUp, &ImageButton::clicked, this, &Widget::m_buttonSetUp_clicked);
	connect(this->m_buttonRankList, &ImageButton::clicked, this, &Widget::m_buttonRankList_clicked);
	connect(this->m_buttonExit, &ImageButton::clicked, this, &Widget::m_buttonExit_clicked);
	connect(this->m_buttonStart, &ImageButton::clicked, this, &Widget::m_buttonStart_clicked);

	QList<ImageButton *> btnList = {this->m_buttonStart, this->m_buttonRankList, this->m_buttonSetUp, this->m_buttonExit};
	for (ImageButton *btn : btnList)
	{
		connect(btn, &ImageButton::needSound, this, &Widget::needSound);
	}
}

void Widget::initPopWidgetManager()
{
	this->m_popWidgetsManager = new PopWidgetsManager(this);

	connect(this->m_popWidgetsManager, &PopWidgetsManager::needOperator, this, &Widget::handleOperator);
	connect(this->m_popWidgetsManager, &PopWidgetsManager::needChangeGameCondition, this, &Widget::changeGameCondition);
	connect(this->m_popWidgetsManager, &PopWidgetsManager::changeSetUp, this, &Widget::changeSetUp);
	connect(this->m_popWidgetsManager, &MyAbstractWidget::needSound, this, &Widget::needSound);
}
void Widget::m_buttonStart_clicked()
{
	emit needOperator(operatorType::PLAYBGM);
	switch (m_gameCondition)
	{
	case gameCondition::PAUSE:
		emit needOperator(operatorType::GAMEMAP_RETURN);
		break;
	case gameCondition::START:
		emit needOperator(operatorType::GAMEMAP_POP);
		break;
	default:
		break;
	}
}
void Widget::m_buttonRankList_clicked()
{
	emit needOperator(operatorType::RANKLIST_POP);
}
void Widget::m_buttonSetUp_clicked()
{
	emit needOperator(operatorType::GAMESETUP_POP);
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
	this->m_buttonStart->draw(&painter);
	this->m_buttonRankList->draw(&painter);
	this->m_buttonSetUp->draw(&painter);
	this->m_buttonExit->draw(&painter);
	//	this->m_popWidgetsManager->update();
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
		case operatorType::GAMEHARDER_ONE:
			this->nextlevel();
			break;
		default:
			break;
		}
	}
}
void Widget::nextlevel()
{
	if (this->m_enemySpeed < 10)
	{
		this->m_enemySpeed++;
	}
	this->globalSetUp();
}
void Widget::changeGameCondition(gameCondition condition)
{
	if (this->m_gameCondition != condition)
	{
		this->m_gameCondition = condition;
		switch (m_gameCondition)
		{
		case gameCondition::PAUSE:
			this->m_buttonStart->changeImage(":/imagePng/PNG/SPACE_RETURN.png");
			qDebug() << this->m_gameCondition;
			break;
		case gameCondition::START:
			this->m_buttonStart->changeImage(":/imagePng/PNG/SPACE_START.png");
			break;
		default:
			break;
		}
	}
}
// //设置相关
void Widget::globalSetUp()
{
	this->m_popWidgetsManager->loadSetUp(m_enemyNum, m_enemySpeed, m_isReward);
}
void Widget::changeSetUp(int enemyNum, float enemySpeed, bool isReward)
{
	this->m_enemySpeed = enemySpeed;
	this->m_enemyNum = enemyNum;
	this->m_isReward = isReward;
}

void Widget::loadConfig()
{
	QSettings setting("KSPACEConfig.ini", QSettings::IniFormat);
	this->m_enemyNum = setting.value("EnemyNum").toInt();
	this->m_isReward = setting.value("IsReward").toBool();
	this->m_enemySpeed = setting.value("EnemySpeed").toInt();
	this->globalSetUp();
}
void Widget::saveConfig()
{
	QSettings setting("KSPACEConfig.ini", QSettings::IniFormat);
	setting.setValue("EnemyNum", m_enemyNum);
	setting.setValue("IsReward", m_isReward);
	setting.setValue("EnemySpeed", m_enemySpeed);
}
