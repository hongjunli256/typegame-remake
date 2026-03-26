#include "uilayer.h"
UILayer::UILayer(QWidget *parent)
	: MyAbstractWidget{parent}
{
	this->move(0, 0);
	this->setFixedSize(800, 600);

	//本界面初始化
	this->initButtons();
	this->initLabels();
	this->initTimers();
	this->init();
}
void UILayer::initButtons()
{
	this->m_buttonPause = new ImageButton(":/imagePng/PNG/PUBLIC_PAUSE.png", this, QPoint(405, 510), 3);
	this->m_buttonStart = new ImageButton(":/imagePng/PNG/PUBLIC_START.png", this, QPoint(485, 525), 3);
	this->m_buttonEnd = new ImageButton(":/imagePng/PNG/PUBLIC_END.png", this, QPoint(450, 480), 3);
	this->m_buttonSetUp = new ImageButton(":/imagePng/PNG/PUBLIC_SETUP.png", this, QPoint(440, 550), 3);
	this->m_buttonExit = new ImageButton(":/imagePng/PNG/PUBLIC_EXIT.png", this, QPoint(30, 520), 3);

	connect(this->m_buttonEnd, &ImageButton::clicked, this, &UILayer::m_buttonEndClicked);
	connect(this->m_buttonPause, &ImageButton::clicked, this, &UILayer::m_buttonPauseClicked);
	connect(this->m_buttonStart, &ImageButton::clicked, this, &UILayer::m_buttonStartClicked);
	connect(this->m_buttonSetUp, &ImageButton::clicked, this, &UILayer::m_buttonSetUpClicked);
	connect(this->m_buttonExit, &ImageButton::clicked, this, &UILayer::m_buttonExitClicked);
	QList<ImageButton *> btnList = {this->m_buttonPause, this->m_buttonStart, this->m_buttonEnd, this->m_buttonSetUp, this->m_buttonExit};
	for (ImageButton *btn : btnList)
	{
		connect(btn, &ImageButton::needSound, this, &UILayer::needSound);
	}
}
void UILayer::initLabels()
{
	QFont font1("黑体", 10, 10);
	this->m_labelTimeLimited = new QLabel(this);
	this->m_labelAccuracyRate = new QLabel(this);
	this->m_labelCountDown = new QLabel(this);
	this->m_labelHitCount = new QLabel(this);

	this->m_labelTimeLimited->move(610, 525);
	this->m_labelAccuracyRate->move(610, 550);
	this->m_labelCountDown->move(740, 525);
	this->m_labelHitCount->move(740, 550);

	this->m_labelTimeLimited->setFont(font1);
	this->m_labelAccuracyRate->setFont(font1);
	this->m_labelCountDown->setFont(font1);
	this->m_labelHitCount->setFont(font1);
	return;
}
void UILayer::initTimers()
{
	this->m_timerRefresh = new QTimer(this);
	connect(this->m_timerRefresh, &QTimer::timeout, this, &UILayer::refresh);
}
//**********//
//六个状态具体操作
void UILayer::timer_pause()
{
	this->m_timerRefresh->stop();
}
void UILayer::timer_start()
{
	this->m_timerRefresh->start(1000);
}
void UILayer::init()
{
	this->m_CountDown = 60 * m_timeLimited;
	this->m_HitCount = 0;
	this->m_pressCount = 0;
	this->m_labelTimeLimited->setText("");
	this->m_labelAccuracyRate->setText("");
	this->m_labelCountDown->setText("");
	this->m_labelHitCount->setText("");
}
//**********//
//五个按钮点击处理
void UILayer::changeGameCondition(gameCondition condition)
{
	switch (condition)
	{
	case CONTINUE:
	case PAUSE:
		this->m_buttonEnd->enable();
		this->m_buttonPause->enable();
		this->m_buttonSetUp->enable();
		this->m_buttonStart->disable();
		this->m_buttonExit->enable();
		break;
	case READYTOPLAY:
		this->m_buttonEnd->disable();
		this->m_buttonPause->disable();
		this->m_buttonSetUp->enable();
		this->m_buttonStart->enable();
		this->m_buttonExit->enable();
		break;

	default:
		break;
	}
}
//**********//
void UILayer::m_buttonEndClicked() //就是结束，所以懒得写结束就直接用了这个
{
	this->toBeginofReadytoPlay();
	emit needPauseBGM();
}
void UILayer::m_buttonStartClicked() //就是重开，所以没写重开函数就用了这个
{
	emit needChangeGameCondition(gameCondition::CONTINUE);
	emit needOperator(operatorType::GAMEINIT);
	emit needOperator(operatorType::GAMETIMER_START);
	emit needBGM(BGMtype::NORMAL);
}
void UILayer::m_buttonPauseClicked()
{
	emit needOperator(operatorType::GAMERESUME);
}

void UILayer::m_buttonSetUpClicked() //小设置界面
{
	emit needOperator(operatorType::GAMESETUP_POP);
}
void UILayer::m_buttonExitClicked() //小退出界面
{
	emit needOperator(operatorType::GAMEEXIT_POP);
}

void UILayer::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	this->m_buttonEnd->draw(&painter);
	this->m_buttonPause->draw(&painter);
	this->m_buttonStart->draw(&painter);
	this->m_buttonSetUp->draw(&painter);
	this->m_buttonExit->draw(&painter);
}
//**********//
void UILayer::refresh() //四个标签的更新
{
	this->m_labelTimeLimited->setText(QString::number(this->m_timeLimited));
	this->m_labelTimeLimited->adjustSize();
	if (this->m_pressCount != 0)
	{
		this->m_labelAccuracyRate->setText(QString::number(this->m_HitCount * 100 / this->m_pressCount) + "%");
		this->m_labelAccuracyRate->adjustSize();
	}
	this->m_labelCountDown->setText(QString::number(this->m_CountDown));
	this->m_labelCountDown->adjustSize();
	this->m_labelHitCount->setText(QString::number(this->m_HitCount));
	this->m_labelHitCount->adjustSize();
	this->m_CountDown--;
	if (this->m_CountDown < 0)
	{
		emit needOperator(operatorType::GAMEWIN_POP);
	}
}

void UILayer::isHitMouse(bool isHit_temp)
{
	this->m_pressCount++;
	if (isHit_temp)
	{
		this->m_HitCount++;
		if (this->m_HitCount >= 20)
		{
			emit this->needBGM(BGMtype::ACTIVE);
		}
	}
}
