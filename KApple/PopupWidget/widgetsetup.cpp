#include "widgetsetup.h"

const QPixmap& WidgetSetUp::pixSetUp()
{
	static const QPixmap pix(":/imagePng/PNG/APPLE_SETUP.png");
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

	connect(this->m_sliderGameLevel, &QSlider::valueChanged, this,
			[this]()
			{
				this->m_labelGameLevelValue->setText(QString::number(this->m_sliderGameLevel->value()));
				this->m_labelGameLevelValue->adjustSize();
			});
	connect(this->m_sliderWinNum, &QSlider::valueChanged, this,
			[this]()
			{
				this->m_labelWinNumValue->setText(QString::number(this->m_sliderWinNum->value()));
				this->m_labelWinNumValue->adjustSize();
			});
	connect(this->m_sliderFailNum, &QSlider::valueChanged, this,
			[this]()
			{
				this->m_labelFailNumValue->setText(QString::number(this->m_sliderFailNum->value()));
				this->m_labelFailNumValue->adjustSize();
			});
	connect(this->m_buttonDEFAULT,&ImageButton::clicked,this,&WidgetSetUp::m_buttonDEFAULT_clicked);
	connect(this->m_buttonOK, &ImageButton::clicked, this, &WidgetSetUp::m_buttonYES_clicked);
	connect(this->m_buttonCANCEL, &ImageButton::clicked, this, &WidgetSetUp::m_buttonNO_clicked);
}
void WidgetSetUp::initLabel()
{
	this->m_labelGameLevel = new QLabel(this);
	this->m_labelFailNum = new QLabel(this);
	this->m_labelWinNum = new QLabel(this);
	this->m_labelGameLevelValue = new QLabel(this);
	this->m_labelFailNumValue = new QLabel(this);
	this->m_labelWinNumValue = new QLabel(this);

	QFont font1("黑体", 10, 10);
	this->m_labelGameLevel->setFont(font1);
	this->m_labelFailNum->setFont(font1);
	this->m_labelWinNum->setFont(font1);

	this->m_labelGameLevelValue->setFont(font1);
	this->m_labelFailNumValue->setFont(font1);
	this->m_labelWinNumValue->setFont(font1);

	this->m_labelGameLevel->move(120, 80);
	this->m_labelFailNum->move(120, 140);
	this->m_labelWinNum->move(120, 200);

	this->m_labelGameLevelValue->move(400, 80);
	this->m_labelFailNumValue->move(400, 140);
	this->m_labelWinNumValue->move(400, 200);

	this->m_labelGameLevel->setText("游戏等级:");
	this->m_labelFailNum->setText("失败苹果数:");
	this->m_labelWinNum->setText("成功苹果数:");

	//	this->loadConfig();

	this->m_labelGameLevelValue->setText(QString::number(this->m_sliderGameLevel->value()));
	this->m_labelFailNumValue->setText(QString::number(this->m_sliderFailNum->value()));
	this->m_labelWinNumValue->setText(QString::number(this->m_sliderWinNum->value()));
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
	this->m_sliderGameLevel = new QSlider(Qt::Horizontal, this);
	this->m_sliderGameLevel->setRange(0, 9);
	this->m_sliderGameLevel->setFixedWidth(200);
	this->m_sliderGameLevel->move(200, 80);

	this->m_sliderFailNum = new QSlider(Qt::Horizontal, this);
	this->m_sliderFailNum->setRange(5, 50);
	this->m_sliderFailNum->setFixedWidth(200);
	this->m_sliderFailNum->move(200, 140);

	this->m_sliderWinNum = new QSlider(Qt::Horizontal, this);
	this->m_sliderWinNum->setRange(100, 900);
	this->m_sliderWinNum->setFixedWidth(200);
	this->m_sliderWinNum->move(200, 200);

	QList<QSlider *> sliderList = {this->m_sliderWinNum, this->m_sliderGameLevel, this->m_sliderFailNum};
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
	emit this->changeSetUp(m_sliderWinNum->value(), m_sliderFailNum->value(), m_sliderGameLevel->value());
	emit needOperator(operatorType::GAMERESUME);
	emit this->needOperator(operatorType::GAMESETUP_SURE_POP);
}
void WidgetSetUp::m_buttonDEFAULT_clicked()
{
	this->m_sliderGameLevel->setValue(3);
	this->m_sliderWinNum->setValue(100);
	this->m_sliderFailNum->setValue(5);
}
void WidgetSetUp::loadSetUp(int winNum, int failNum, int gameLevel)
{
	this->m_sliderGameLevel->setValue(gameLevel);
	this->m_sliderWinNum->setValue(winNum);
	this->m_sliderFailNum->setValue(failNum);
}
