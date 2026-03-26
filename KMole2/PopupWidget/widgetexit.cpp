#include "widgetexit.h"
#include<QApplication>
const QPixmap& WidgetExit::pixExit() {
	static const QPixmap pix(":/imagePng/PNG/MAIN_DLG_BG.png"); // 替换为你的图片路径
	return pix;
}
WidgetExit::WidgetExit(QWidget *parent)
	: MyAbstractWidget{parent}
{
	this->move(240, 200);

	initButton();
	initLabel();

	this->hide();
}
//页面初始化
void WidgetExit::initButton()
{
	this->m_buttonREPLAY = new ImageButton(":/imagePng/PNG/MAIN_DLG_REPLAY.png", this, QPoint(200, 130), 3);
	connect(this->m_buttonREPLAY, &ImageButton::clicked, this, &WidgetExit::m_buttonCancel_clicked);

	this->m_buttonExit = new ImageButton(":/imagePng/PNG/MAIN_DLG_EXIT.png", this, QPoint(30, 130), 3);
	connect(this->m_buttonExit, &ImageButton::clicked, this, &WidgetExit::m_buttonExit_clicked);

	QList<ImageButton *> btnList = {this->m_buttonREPLAY, this->m_buttonExit};
	for (ImageButton *btn : btnList)
	{
		connect(btn, &ImageButton::needSound, this, &WidgetExit::needSound);
	}
}

void WidgetExit::initLabel()
{
    this->label=new QLabel(this);
    label->setText("你真的要离开吗");
    label->move(115,80);
}

void WidgetExit::m_buttonExit_clicked()
{
    QApplication::quit();
}
void WidgetExit::m_buttonCancel_clicked()
{
    this->hide();
	emit allhide();
	emit needOperator(operatorType::GAMERESUME);
}

void WidgetExit::paintEvent(QPaintEvent *event){
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.drawPixmap(0,0,this->pixExit());
	this->m_buttonExit->draw(&painter);
	this->m_buttonREPLAY->draw(&painter);
}
