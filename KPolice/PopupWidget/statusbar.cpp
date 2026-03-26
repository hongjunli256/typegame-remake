#include "statusbar.h"
#include <QFile>
#include <QPainter>
const QFont StatusBar::fontSmall("黑体", 15, QFont::Bold);
const QPixmap &StatusBar::pixStatusBar()
{
	static const QPixmap pix(":/imagePng/PNG/POLICE_INPUT.png"); // 替换为你的图片路径
	return pix;
}
const QPixmap &StatusBar::pixSliderBarBlue()
{
	static const QPixmap pix(":/imagePng/PNG/POLICE_BLUE.png"); // 替换为你的图片路径
	return pix;
}
const QPixmap &StatusBar::pixSliderBarYellow()
{
	static const QPixmap pix(":/imagePng/PNG/POLICE_YELLOW.png"); // 替换为你的图片路径
	return pix;
}
StatusBar::StatusBar(QWidget *parent)
	: MyAbstractWidget{parent}
{
	this->move(20, 500);
	this->resize(this->pixStatusBar().size());
	this->init();
}
void StatusBar::init()
{
	currentIndex = 0;
	this->subTextString = "";
	this->textString = "";
	if (!this->stringPath.isEmpty())
	{
		QString path = "articles/" + stringPath;
		QFile file(path);
		file.open(QIODevice::ReadOnly | QIODevice::Text); // 直接打开，不判断是否成功
		if (file.isOpen())
		{
			QTextStream in(&file);
			this->textString = in.readAll();
			this->textString = this->textString.remove('\n').remove('\r');
			this->subTextString = "";
		}
		else
		{
			this->textString = "abcdefg";
			this->subTextString = "";
		}

		file.close();
	}
}
void StatusBar::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.drawPixmap(0, 0, this->pixStatusBar());
	this->drawString(&painter);
	if (!this->textString.isEmpty())
	{
		int sliderPosX = (725 - 20) * subTextString.size() / textString.size() + 20;
		int sliderPosY = 50;
		if (isPolice)
		{
			painter.drawPixmap(sliderPosX, sliderPosY, this->pixSliderBarBlue());
		}
		else
		{
			painter.drawPixmap(sliderPosX, sliderPosY, this->pixSliderBarYellow());
		}
	}
}

void StatusBar::drawString(QPainter *painter)
{
	if (!painter)
	{ // 空指针保护
		return;
	}
	painter->setFont(StatusBar::fontSmall);
	const int visibleCharCount = 66;
	const int halfVisibleCount = visibleCharCount / 2;
	const int drawX = 35;
	const int drawY = 35;

	const int strSize = textString.size();
	int start1 = 0, end1 = 0;
	int start2 = 0, end2 = 0;

	if (strSize <= visibleCharCount) //整体少全部显示
	{
		start1 = 0;
		end1 = strSize;
	}
	else
	{
		start1 = std::max(currentIndex - halfVisibleCount, 0);
		end1 = std::min(start1 + visibleCharCount, strSize);
		if (end1 >= strSize) //到了结尾
		{
			start1 = strSize - visibleCharCount;
			end1 = strSize;
		}
	}
	start2 = start1;
	end2 = std::min(currentIndex, strSize);
	const int count1 = end1 - start1;
	const int count2 = end2 - start2;

	painter->setPen(Qt::black);
	if (count1 > 0)
	{
		painter->drawText(drawX, drawY, textString.mid(start1, count1));
	}

	painter->setPen(Qt::blue);
	if (count2 > 0 && !subTextString.isEmpty())
	{
		painter->drawText(drawX, drawY, subTextString.mid(start2, count2));
		QFontMetrics fm(painter->font());
		int subTextWidth = fm.horizontalAdvance(subTextString.mid(start2, count2));
		int cursorX = drawX + subTextWidth;
		int cursorTop = drawY - 15;
		int cursorBottom = drawY + 4;

		painter->setPen(QPen(Qt::black, 1));
		painter->drawLine(cursorX, cursorTop, cursorX, cursorBottom);
		// --------------------------------------------------------------------------------
	}
}
// 新增：实时更新状态栏信息
void StatusBar::refresh()
{

}

bool StatusBar::receiveHit(QString &c)
{
	if (this->currentIndex < this->textString.size())
		if (this->textString[currentIndex] == c)
		{
			if (this->subTextString.size() < this->textString.size())
			{
				this->subTextString.append(c);
				this->currentIndex = this->subTextString.size();
				if (this->textString.size() == this->subTextString.size())
				{
					emit timeout();
				}
				return true;
			}
		}
	return false;
}

void StatusBar::loadSetUp(bool isPolice, QString StringPath)
{
	this->isPolice = isPolice;
	this->stringPath = StringPath;
}
