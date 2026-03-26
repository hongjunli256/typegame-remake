#include "uilayer.h"
UILayer::UILayer(QWidget *parent)
	: MyAbstractWidget{parent}
{
	this->move(0, 0);
	this->setFixedSize(800, 600);

	//本界面初始化
	this->initButtons();
	this->init();
}
void UILayer::initButtons()
{
	this->m_buttonPause = new ImageButton(":/imagePng/PNG/PUBLIC_PAUSE.png", this, QPoint(118, 514), 3);
	this->m_buttonStart = new ImageButton(":/imagePng/PNG/PUBLIC_START.png", this, QPoint(198, 526), 3);
	this->m_buttonEnd = new ImageButton(":/imagePng/PNG/PUBLIC_END.png", this, QPoint(163, 483), 3);
	this->m_buttonSetUp = new ImageButton(":/imagePng/PNG/PUBLIC_SETUP.png", this, QPoint(150, 552), 3);
	this->m_buttonExit = new ImageButton(":/imagePng/PNG/PUBLIC_EXIT.png", this, QPoint(20, 540), 3);

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

//**********//
//六个状态具体操作
void UILayer::timer_pause() {}
void UILayer::timer_start() {}
void UILayer::init() {}
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

void UILayer::m_buttonSetUpClicked()
{
	emit needOperator(operatorType::GAMESETUP_POP);
}
void UILayer::m_buttonExitClicked()
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
