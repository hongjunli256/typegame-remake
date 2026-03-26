#include "leaf.h"
//苹果图像的状态更新

const QPixmap& Leaf::pixNormal()
{
	static const QPixmap pix(":/imagePng/PNG/FROG_LEAF.png");
	return pix;
}
Leaf::Leaf(QWidget* parent, QString string, int slideTime, QPoint pos, int direction)
	: QWidget(parent)
{
	this->resize(pixNormal().size());
	this->move(pos);

	this->m_slideTime = slideTime;

	this->m_direction = direction;

	this->m_timer = new QTimer(this);

	this->m_timer->start(5 * slideTime);

	connect(this->m_timer, &QTimer::timeout, this, &Leaf::refresh);

	this->m_textBox = new TextBox(string, this);
	connect(this->m_textBox, &TextBox::finishSpell, this, &Leaf::finishSpell);
}
void Leaf::changeState(QString difficulty, int slideTime)
{
	this->resize(pixNormal().size());
	this->frog = nullptr;
	this->m_textBox->changeState(difficulty);
	this->m_slideTime = slideTime;
	this->m_timer->start(5 * slideTime);
}
Leaf::~Leaf() {}

void Leaf::draw(QPainter* painter)
{
	painter->drawPixmap(this->pos(), this->pixNormal(), QRect(0, 0, this->size().rwidth(), this->size().rheight()));
	this->m_textBox->draw(painter);
}
void Leaf::refresh()
{
	if (this->m_direction == 1)
	{
		if (this->pos().rx() >= 800)
		{
			this->move(-148, this->pos().ry());
			this->m_textBox->clear();
			if (this->frog != nullptr)
			{
				emit this->frogDrop();
			}
			else
			{
				emit this->timeOut(this);
			}
		}
	}
	else
	{
		if (this->pos().rx() <= -148)
		{
			this->move(800, this->pos().ry());
			this->m_textBox->clear();
			if (this->frog != nullptr)
			{
				emit this->frogDrop();
			}
			else
			{
				emit this->timeOut(this);
			}
		}
	}
	this->move(pos() + QPoint(2 * m_direction, 0));
	this->m_textBox->move(this->pos() + QPoint(21, 25));
	if (this->frog != nullptr)
	{
		this->frog->move(this->pos() + QPoint(0, 20));
	}
}

void Leaf::getFrog(Frog* frog = nullptr)
{
	this->frog = frog;
}
