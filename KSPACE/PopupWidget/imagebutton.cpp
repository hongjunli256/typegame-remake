#include "imagebutton.h"

ImageButton::ImageButton(const QString& srcPath,QWidget* parent,QPoint pos,int conditionNum):QWidget(parent) {
    m_srcPix = QPixmap(srcPath);
	this->move(pos);
	setFixedSize(m_srcPix.size().rwidth()/conditionNum,m_srcPix.size().height());
    m_condition=condition::NORMAL;
    setMouseTracking(true);
    this->m_conditionNum=conditionNum;
}


void ImageButton::draw(QPainter*painter){
    if(this->m_condition<this->m_conditionNum)
    {
        int posFromSrcPix=this->size().rwidth()*this->m_condition;
		painter->drawPixmap(this->pos(), this->m_srcPix, QRect(posFromSrcPix, 0, this->size().rwidth(), this->size().rheight()));
	}
	else
    {
		painter->drawPixmap(this->pos(), this->m_srcPix, QRect(0, 0, this->size().rwidth(), this->size().rheight()));
	}
}
void ImageButton::enterEvent(QEnterEvent*event){
	if (this->isEnabled())
	{
		this->m_condition = condition::HOVER;
		parentWidget()->update();
		emit this->enter();
		emit this->needSound(soundType::BUTTONENTER);
	}
}

void ImageButton::leaveEvent(QEvent*){
	if (this->isEnabled())
	{
		this->m_condition = condition::NORMAL;
		parentWidget()->update();
	}
}

void ImageButton::mousePressEvent(QMouseEvent* e){
	if (this->isEnabled())
	{
		if (e->button() == Qt::LeftButton)
		{
			this->m_condition = condition::PRESS;
			parentWidget()->update();
		}
	}
}

void ImageButton::mouseReleaseEvent(QMouseEvent* e){
	if (this->isEnabled())
	{
		if (e->button() == Qt::LeftButton && rect().contains(e->pos()))
		{
			this->m_condition = condition::HOVER;
			parentWidget()->update();
			emit clicked();
			emit this->needSound(soundType::BUTTONCLICK);
		}
		else
		{
			this->m_condition = condition::NORMAL;
			parentWidget()->update();
		}
	}
}
void ImageButton::enable()
{
    this->m_condition=condition::NORMAL;
    this->setEnabled(true);
}
void ImageButton::disable()
{
	this->m_condition = condition::FORBIDDEN;
	this->setEnabled(false);
}
void ImageButton::ForceCondition(int num)
{
	this->m_condition = (condition) num;
}
void ImageButton::changeImage(const QString& srcPath)
{
	this->m_srcPix = QPixmap(srcPath);
}
