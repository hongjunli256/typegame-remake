#include "widgetsetup.h"

const QPixmap &WidgetSetUp::pixSetUp()
{
	static const QPixmap pix(":/imagePng/PNG/MOLE_SETUP.png");
	return pix;
}
WidgetSetUp::WidgetSetUp(QWidget *parent)
	: MyAbstractWidget{parent}
{
	this->move(160, 100);
	this->initButton();
    this->initSlider();
    this->initLabel();
    this->setFixedSize(this->pixSetUp().size());
    this->hide();

	connect(this->m_sliderGameTime, &QSlider::valueChanged, this,
			[this]()
			{
				this->m_labelGameTimeValue->setText(QString::number(this->m_sliderGameTime->value()));
				this->m_labelGameTimeValue->adjustSize();
			});
	connect(this->m_sliderStayTime, &QSlider::valueChanged, this,
			[this]()
			{
				this->m_labelStayTimeValue->setText(QString::number(this->m_sliderStayTime->value()));
				this->m_labelStayTimeValue->adjustSize();
			});
	connect(this->m_sliderSpareTimeforMouse, &QSlider::valueChanged, this,
			[this]()
			{
				this->m_labelSpareTimeforMouseValue->setText(QString::number(this->m_sliderSpareTimeforMouse->value()));
				this->m_labelSpareTimeforMouseValue->adjustSize();
			});
	connect(this->m_buttonDEFAULT,&ImageButton::clicked,this,&WidgetSetUp::m_buttonDEFAULT_clicked);
	connect(this->m_buttonOK, &ImageButton::clicked, this, &WidgetSetUp::m_buttonYES_clicked);
	connect(this->m_buttonCANCEL, &ImageButton::clicked, this, &WidgetSetUp::m_buttonNO_clicked);
}

void WidgetSetUp::initLabel()
{
	this->m_labelSetUpGameTime = new QLabel(this);
	this->m_labelSetUpSpareTimeforMouse = new QLabel(this);
	this->m_labelSetUpStayTime = new QLabel(this);
	this->m_labelGameTimeValue = new QLabel(this);
	this->m_labelSpareTimeforMouseValue = new QLabel(this);
	this->m_labelStayTimeValue = new QLabel(this);

	QFont font1("黑体", 10, 10);
	this->m_labelSetUpGameTime->setFont(font1);
	this->m_labelSetUpSpareTimeforMouse->setFont(font1);
	this->m_labelSetUpStayTime->setFont(font1);

	this->m_labelGameTimeValue->setFont(font1);
	this->m_labelSpareTimeforMouseValue->setFont(font1);
	this->m_labelStayTimeValue->setFont(font1);

	this->m_labelSetUpGameTime->move(120, 80);
	this->m_labelSetUpSpareTimeforMouse->move(120, 140);
	this->m_labelSetUpStayTime->move(120, 200);

	this->m_labelGameTimeValue->move(400, 80);
	this->m_labelSpareTimeforMouseValue->move(400, 140);
	this->m_labelStayTimeValue->move(400, 200);

	this->m_labelSetUpGameTime->setText("游戏时间:");
	this->m_labelSetUpSpareTimeforMouse->setText("出现间隔:");
	this->m_labelSetUpStayTime->setText("停留时间:");

	//this->loadConfig();

	this->m_labelGameTimeValue->setText(QString::number(this->m_sliderGameTime->value()));
	this->m_labelSpareTimeforMouseValue->setText(QString::number(this->m_sliderSpareTimeforMouse->value()));
	this->m_labelStayTimeValue->setText(QString::number(this->m_sliderStayTime->value()));
}
void WidgetSetUp::initButton()
{
	this->m_buttonDEFAULT = new ImageButton(":/imagePng/PNG/DEFAULT.png", this, QPoint(360, 270), 3);
	this->m_buttonCANCEL = new ImageButton(":/imagePng/PNG/CANCEL.png", this, QPoint(270, 270), 3);
	this->m_buttonOK = new ImageButton(":/imagePng/PNG/OK.png", this, QPoint(180, 270), 3);
	QList<ImageButton *> btnList = {this->m_buttonDEFAULT, this->m_buttonCANCEL, this->m_buttonOK};
	for (ImageButton *btn : btnList)
	{
		connect(btn, &ImageButton::needSound, this, &WidgetSetUp::needSound);
	}
}
void sliderSetStyleSheet(QSlider*slider)
{
	slider->setStyleSheet(R"(
    QSlider::groove:horizontal {
        background-image: url(:/imagePng/PNG/SLIDER_BG.png);
        height: 4px;
        border: none;
        background-repeat: repeat-x;
    }
    /* 未按住状态：左11px，不拉伸 */
    QSlider::handle:horizontal {
        /* border-image-slice 固定裁剪，none 禁止拉伸 */
        border-image: url(:/imagePng/PNG/SLIDER_SLIDER.png) 0 11 0 0 none none;
        border-width: 0;
        width: 11px; /* 锁定单状态宽度，不放大 */
        height: 23px; /* 锁定原生高度 */
        margin: -9.5px 0;
        border: none;
    }
    /* 按住状态：右11px，不拉伸 */
    QSlider::handle:horizontal:pressed {
        border-image: url(:/imagePng/PNG/SLIDER_SLIDER.png) 0 0 0 11 none none;
        border-width: 0;
    }
)");
}

void WidgetSetUp::initSlider()
{
	this->m_sliderGameTime = new QSlider(Qt::Horizontal, this);
	this->m_sliderGameTime->setRange(1, 30);
	this->m_sliderGameTime->setFixedWidth(200);
	this->m_sliderGameTime->move(200, 80);

	this->m_sliderSpareTimeforMouse = new QSlider(Qt::Horizontal, this);
	this->m_sliderSpareTimeforMouse->setRange(0, 10);
	this->m_sliderSpareTimeforMouse->setFixedWidth(200);
	this->m_sliderSpareTimeforMouse->move(200, 140);

	this->m_sliderStayTime = new QSlider(Qt::Horizontal, this);
	this->m_sliderStayTime->setRange(1, 20);
	this->m_sliderStayTime->setFixedWidth(200);
	this->m_sliderStayTime->move(200, 200);

	QList<QSlider *> sliderList = {this->m_sliderStayTime, this->m_sliderGameTime, this->m_sliderSpareTimeforMouse};
	for (QSlider *slider : sliderList)
	{
		sliderSetStyleSheet(slider);
		connect(slider, &QSlider::valueChanged, this,
				[this]()
				{
					emit this->needSound(soundType::SLIDER);
				});
	}
}

void WidgetSetUp::paintEvent(QPaintEvent *event){
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.drawPixmap(0,0,this->pixSetUp());
    this->m_buttonDEFAULT->draw(&painter);
	this->m_buttonOK->draw(&painter);
	this->m_buttonCANCEL->draw(&painter);
}
void WidgetSetUp::m_buttonNO_clicked()
{
    this->hide();
	emit allhide();
	emit needOperator(operatorType::GAMERESUME);
}
void WidgetSetUp::m_buttonYES_clicked()
{
    this->hide();
	emit this->changeSetUp(m_sliderStayTime->value(), m_sliderSpareTimeforMouse->value(), m_sliderGameTime->value());
	emit needOperator(operatorType::GAMERESUME);
	emit this->needOperator(operatorType::GAMESETUP_SURE_POP);
}
void WidgetSetUp::m_buttonDEFAULT_clicked()
{
	this->m_sliderGameTime->setValue(1);
	this->m_sliderSpareTimeforMouse->setValue(0);
	this->m_sliderStayTime->setValue(6);
}

void WidgetSetUp::loadSetUp(int stayTime, int spareTimeforMouse, int gameTime)
{
	this->m_sliderGameTime->setValue(gameTime);
	this->m_sliderStayTime->setValue(stayTime);
	this->m_sliderSpareTimeforMouse->setValue(spareTimeforMouse);
}
