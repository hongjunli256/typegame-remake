#include "widgetwin.h"
const QPixmap &WidgetWin::pixFail()
{
	static const QPixmap pix(":/imagePng/PNG/MOLE_DLG_BG.png");
	return pix;
}
WidgetWin::WidgetWin(QWidget *parent)
	: MyAbstractWidget{parent}
{
	this->move(240, 200);
	this->initButton();
	this->initLabel();
	this->hide();
}

void WidgetWin::initButton()
{
	this->m_buttonREPLAY = new ImageButton(":/imagePng/PNG/MOLE_DLG_REPLAY.png", this, QPoint(30, 130), 3);
	this->m_buttonEND = new ImageButton(":/imagePng/PNG/MOLE_DLG_END.png", this, QPoint(200, 130), 3);
	this->m_buttonNEXT = new ImageButton(":/imagePng/PNG/MOLE_DLG_NEXT.png", this, QPoint(115, 130), 3);

	connect(this->m_buttonEND, &ImageButton::clicked, this, &WidgetWin::m_buttonEnd_clicked);
	connect(this->m_buttonREPLAY, &ImageButton::clicked, this, &WidgetWin::m_buttonResume_clicked);
	connect(this->m_buttonNEXT, &ImageButton::clicked, this, &WidgetWin::m_buttonNext_clicked);
	QList<ImageButton *> btnList = {this->m_buttonREPLAY, this->m_buttonEND, this->m_buttonNEXT};
	for (ImageButton *btn : btnList)
	{
		connect(btn, &ImageButton::needSound, this, &WidgetWin::needSound);
	}
}
void WidgetWin::initLabel()
{
	this->label = new QLabel(this);
	label->setText("不错！");
	label->move(115, 80);
}
void WidgetWin::m_buttonEnd_clicked()
{
    this->hide();
	emit allhide();
	this->toBeginofReadytoPlay();
}
void WidgetWin::m_buttonResume_clicked()
{
    this->hide();
	emit allhide();
	this->toBeginofContinue();
}

void WidgetWin::m_buttonNext_clicked()
{
    this->hide();
	emit allhide();
	emit needOperator(operatorType::GAMEHARDER_ONE);
	this->toBeginofContinue();
}
void WidgetWin::paintEvent(QPaintEvent *event){
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.drawPixmap(0,0,this->pixFail());
	this->m_buttonEND->draw(&painter);
	this->m_buttonREPLAY->draw(&painter);
	this->m_buttonNEXT->draw(&painter);
}
