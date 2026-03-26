#include "widgetsetupsure.h"

const QPixmap& widgetSetUpSure::pixExit() {
	static const QPixmap pix(":/imagePng/PNG/MAIN_DLG_BG.png");
	return pix;
}
widgetSetUpSure::widgetSetUpSure(QWidget *parent)
	: MyAbstractWidget{parent}
{
	this->move(240, 200);

	initButton();
    initLabel();
    this->hide();
}
void widgetSetUpSure::initButton()
{
	this->m_buttonNO = new ImageButton(":/imagePng/PNG/NO.png", this, QPoint(30, 130), 3);
	this->m_buttonYES = new ImageButton(":/imagePng/PNG/YES.png", this, QPoint(200, 130), 3);

	connect(this->m_buttonYES, &ImageButton::clicked, this, &widgetSetUpSure::m_buttonYES_clicked);
	connect(this->m_buttonNO, &ImageButton::clicked, this, &widgetSetUpSure::m_buttonNO_clicked);
	QList<ImageButton *> btnList = {this->m_buttonNO, this->m_buttonYES};
	for (ImageButton *btn : btnList)
	{
		connect(btn, &ImageButton::needSound, this, &widgetSetUpSure::needSound);
	}
}
void widgetSetUpSure::initLabel()
{
	this->label = new QLabel(this);
	label->setText("设置立刻生效吗?");
	label->move(115, 80);
}
void widgetSetUpSure::m_buttonYES_clicked()
{
    this->hide();
	emit allhide();
	emit needOperator(operatorType::GLOBALSETTING);
	this->toBeginofContinue();
}
void widgetSetUpSure::m_buttonNO_clicked()
{
    this->hide();
	emit allhide();
	emit needOperator(operatorType::GAMERESUME);
}
void widgetSetUpSure::paintEvent(QPaintEvent *event){
	QWidget::paintEvent(event);
	QPainter painter(this);
	painter.drawPixmap(0,0,this->pixExit());
	this->m_buttonYES->draw(&painter);
	this->m_buttonNO->draw(&painter);
}
