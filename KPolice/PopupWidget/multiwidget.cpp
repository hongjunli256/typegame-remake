#include "multiwidget.h"
const QPixmap &MultiWidget::pixExit()
{
	static const QPixmap pix(":/imagePng/PNG/POLICE_SERVERLIST_BG.png"); // 替换为你的图片路径
	return pix;
}
MultiWidget::MultiWidget(QWidget *parent)
	: MyAbstractWidget{parent}
{
	this->move(0, 0);
	this->resize(pixExit().size());
	initButton();
	this->hide();
}

void MultiWidget::initButton()
{
	this->m_buttonCreate = new ImageButton(":/imagePng/PNG/POLICE_CREATE.png", this, QPoint(30, 100), 3);
	connect(this->m_buttonCreate, &ImageButton::clicked, this, &::MultiWidget::m_buttonCreate_clicked);

	this->m_buttonJoin = new ImageButton(":/imagePng/PNG/POLICE_JOIN.png", this, QPoint(30, 200), 3);
	connect(this->m_buttonJoin, &ImageButton::clicked, this, &::MultiWidget::m_buttonJoin_clicked);

	this->m_buttonRefresh = new ImageButton(":/imagePng/PNG/POLICE_REFRESH.png", this, QPoint(30, 300), 3);
	connect(this->m_buttonRefresh, &ImageButton::clicked, this, &::MultiWidget::m_buttonRefresh_clicked);

	this->m_buttonReturn = new ImageButton(":/imagePng/PNG/POLICE_RETURN.png", this, QPoint(30, 400), 3);
	connect(this->m_buttonReturn, &ImageButton::clicked, this, &::MultiWidget::m_buttonReturn_clicked);

	QList<ImageButton *> btnList = {this->m_buttonCreate, this->m_buttonJoin, this->m_buttonRefresh, this->m_buttonReturn};
	for (ImageButton *btn : btnList)
	{
		connect(btn, &ImageButton::needSound, this, &MyAbstractWidget::needSound);
	}
}
void MultiWidget::m_buttonCreate_clicked()
{
	this->hide();
	emit allhide();
	//emit needOperator(operatorType::GAMERESUME);
}
void MultiWidget::m_buttonJoin_clicked()
{
	this->hide();
	emit allhide();
	//QApplication::quit();
}

void MultiWidget::m_buttonRefresh_clicked()
{
	this->hide();
	emit allhide();
	//emit needOperator(operatorType::GAMERESUME);
}
void MultiWidget::m_buttonReturn_clicked()
{
	this->hide();
	emit allhide();
	//emit needOperator(operatorType::GAMERESUME);
}

void MultiWidget::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);
	painter.drawPixmap(0, 0, this->pixExit());
	this->m_buttonJoin->draw(&painter);
	this->m_buttonCreate->draw(&painter);
	this->m_buttonRefresh->draw(&painter);
	this->m_buttonReturn->draw(&painter);
}
