#include "textbox.h"
const QFont TextBox::fontSmall("黑体", 12, QFont::Bold);
const QPixmap &TextBox::pixNormal()
{
	static const QPixmap pix(":/imagePng/PNG/FROG_LEAF.png");
	static const QRect rect(21, 25, 106, 23);
	static const QPixmap pixCut = pix.copy(rect);
	return pixCut;
}
TextBox::TextBox(QString string, QWidget *parent)
	: QWidget{parent}
{
	this->resize(pixNormal().size());
	this->m_string = string;
	this->m_substring = "";

	//this->m_isCanHit = false;
	this->move(21, 25);
}
bool TextBox::receiveHit(QString c)
{
	//if (this->m_isCanHit == true && this->m_string[currentIndex] == c)
	if (this->m_string[currentIndex] == c)
	{
		if (this->m_substring.size() < this->m_string.size())
		{
			this->m_substring.append(c);
			this->currentIndex = this->m_substring.size();
			if (this->m_substring.size() == this->m_string.size())
			{
				emit finishSpell();
				//this->m_isCanHit = false;
			}
			return true;
		}
	}
	return false;
}
void TextBox::drawString(QPainter *painter)
{
	painter->setFont(TextBox::fontSmall);
	painter->setPen(Qt::black);
	painter->drawText(this->pos() + QPoint(10, 20), this->m_string);

	painter->setPen(Qt::red);
	painter->drawText(this->pos() + QPoint(10, 20), this->m_substring);
}
void TextBox::changeState(QString string)
{
	this->m_string = string;
	this->m_substring = "";
	this->currentIndex = 0;
	//this->m_isCanHit = false;
}
void TextBox::draw(QPainter *painter)
{
	painter->drawPixmap(this->pos(), this->pixNormal(), QRect(0, 0, this->size().rwidth(), this->size().rheight()));
	this->drawString(painter);
}
void TextBox::clear()
{
	this->m_substring = "";
	this->currentIndex = 0;
}
