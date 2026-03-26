#include "widgetfail.h"

const QPixmap &WidgetFail::pixFail()
{
	static const QPixmap pix(":/imagePng/PNG/APPLE_DLG_BG.png");
	return pix;
}
WidgetFail::WidgetFail(QWidget *parent)
	: MyAbstractWidget{parent}
{
	this->move(240, 200);
	initButton();
	initLabel();
	this->hide();
}
void WidgetFail::initButton()
{
	this->m_buttonREPLAY = new ImageButton(":/imagePng/PNG/APPLE_DLG_REPLAY.png", this, QPoint(30, 130), 3);
	this->m_buttonEND = new ImageButton(":/imagePng/PNG/APPLE_DLG_END.png", this, QPoint(200, 130), 3);

	connect(this->m_buttonEND, &ImageButton::clicked, this, &WidgetFail::m_buttonEnd_clicked);
	connect(this->m_buttonREPLAY, &ImageButton::clicked, this, &WidgetFail::m_buttonResume_clicked);
	QList<ImageButton *> btnList = {this->m_buttonREPLAY, this->m_buttonEND};
	for (ImageButton *btn : btnList)
	{
		connect(btn, &ImageButton::needSound, this, &WidgetFail::needSound);
	}
}
void WidgetFail::initLabel()
{
	this->label = new QLabel(this);
	label->setText("你认输吧！");
	label->move(115, 80);
}
void WidgetFail::m_buttonEnd_clicked()
{
	this->hide();
	emit allhide();
	this->toBeginofReadytoPlay();
}
void WidgetFail::m_buttonResume_clicked()
{
	this->hide();
	emit allhide();
	this->toBeginofContinue();
}
void WidgetFail::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);
	painter.drawPixmap(0, 0, this->pixFail());
	this->m_buttonEND->draw(&painter);
	this->m_buttonREPLAY->draw(&painter);
}
