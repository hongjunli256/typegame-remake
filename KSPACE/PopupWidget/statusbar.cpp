#include "statusbar.h"
#include <QFile>
#include <QPainter>
const QFont StatusBar::fontSmall("黑体", 15, QFont::Bold);
const QPixmap &StatusBar::pixStatusBar()
{
	static const QPixmap pix(":/imagePng/PNG/POLICE_INPUT.png"); // 替换为你的图片路径
	return pix;
}
StatusBar::StatusBar(QWidget *parent)
	: MyAbstractWidget{parent}
{
	this->move(0, 0);
	this->resize(800, 40);
	this->initLabels();
	this->initProgressBar();
	//this->init();
}
// void StatusBar::init()
// {

// }
void StatusBar::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.drawPixmap(0, 0, this->pixStatusBar());
}
// 新增：实时更新状态栏信息
void StatusBar::refresh(int &score)
{
	this->scoreString->setText(QString::number(score));
	remainingTime--;
	if (remainingTime <= 10 && remainingTime > 0)
	{
		this->information->show();
	}
	else if (remainingTime <= 0)
	{
		this->information->hide();
		this->remainingTime = 120;
		emit needOperator(operatorType::GAMEHARDER_ONE);
	}
	int minutes = remainingTime / 60;
	int seconds = remainingTime % 60;
	timeString->setText(QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0')));
}
void StatusBar::initLabels()
{
	scorePix = new QLabel(this);
	scorePix->setPixmap(QPixmap(":/imagePng/PNG/SPACE_LABEL_SCORE.png"));
	this->scorePix->move(100, 10);

	lifePix = new QLabel(this);
	lifePix->setPixmap(QPixmap(":/imagePng/PNG/SPACE_LABEL_LIFE.png"));
	this->lifePix->move(350, 10);

	timePix = new QLabel(this);
	timePix->setPixmap(QPixmap(":/imagePng/PNG/SPACE_LABEL_TIME.png"));
	this->timePix->move(600, 10);

	timeString = new QLabel(this);
	remainingTime = 120;
	int minutes = remainingTime / 60;
	int seconds = remainingTime % 60;
	timeString->setText(QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0')));
	timeString->setFont(fontSmall);

	QPalette palette = timeString->palette();
	palette.setColor(QPalette::Text, QColorConstants::Svg::orange);
	timeString->setPalette(palette);
	this->timeString->move(650, 10);

	this->information = new QLabel("难度即将上升", this);

	this->information->setFont(QFont("黑体", 10, QFont::Bold));
	information->setPalette(palette);
	this->information->move(710, 15);
	this->information->hide();

	scoreString = new QLabel(this);
	scoreString->setPalette(palette);
	scoreString->setText(0);
	scoreString->setFont(fontSmall);
	scoreString->move(150, 10);
}
// 初始化进度条（核心修复部分）
void StatusBar::initProgressBar()
{
	this->lifeBar = new QProgressBar(this);
	this->lifeBar->move(400, 10);
	lifeBar->setRange(0, 180);
	lifeBar->setValue(10);
	lifeBar->setFixedSize(181, 22); // 你的图片尺寸
	lifeBar->setTextVisible(false);
	lifeBar->setStyleSheet(R"(
    QProgressBar {
        border-image: url(:/imagePng/PNG/SPACE_LIFE.png) 0 0 0 0 stretch stretch;
        background: transparent;
        border: none;
        padding: 3px 0;
    }

    QProgressBar::chunk {
		  margin: 0 4px; 
        border-image: url(:/imagePng/PNG/SPACE_LIFE_OVER.png) 0 0 0 0 round stretch;
        background: transparent;
        border-radius: 0;
    }
)");
}
void StatusBar::init()
{
	this->lifeBar->setValue(180);
	this->remainingTime = 120;
	this->scoreString->setText(0);
}
void StatusBar::loseHp()
{
	int value = this->lifeBar->value() - 10;
	this->lifeBar->setValue(value);
}
void StatusBar::addHp()
{
	int value = this->lifeBar->value() + 30;
	this->lifeBar->setValue(value);
}
bool StatusBar::isDie()
{
	if (this->lifeBar->value() <= 5)
	{
		return true;
	}
	else
	{
		return false;
	}
}
