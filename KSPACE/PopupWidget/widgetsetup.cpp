#include "widgetsetup.h"

const QPixmap &WidgetSetUp::pixSetUp()
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
	this->initCheckbox();
	this->setFixedSize(this->pixSetUp().size());
	this->hide();

	connect(this->m_sliderEnemyNum, &QSlider::valueChanged, this,
			[this]()
			{
				this->m_labelEnemyNumValue->setText(QString::number(this->m_sliderEnemyNum->value()));
				this->m_labelEnemyNumValue->adjustSize();
			});
	connect(this->m_sliderEnemySpeed, &QSlider::valueChanged, this,
			[this]()
			{
				this->m_labelEnemySpeedValue->setText(QString::number(this->m_sliderEnemySpeed->value()));
				this->m_labelEnemySpeedValue->adjustSize();
			});
	connect(this->m_buttonDEFAULT, &ImageButton::clicked, this, &WidgetSetUp::m_buttonDEFAULT_clicked);
	connect(this->m_buttonOK, &ImageButton::clicked, this, &WidgetSetUp::m_buttonYES_clicked);
	connect(this->m_buttonCANCEL, &ImageButton::clicked, this, &WidgetSetUp::m_buttonNO_clicked);
}
void WidgetSetUp::initLabel()
{
	this->m_labelEnemyNum = new QLabel(this);
	this->m_labelEnemySpeed = new QLabel(this);
	this->m_labelEnemyNumValue = new QLabel(this);
	this->m_labelEnemySpeedValue = new QLabel(this);

	QFont font1("黑体", 10, 10);
	this->m_labelEnemyNum->setFont(font1);
	this->m_labelEnemySpeed->setFont(font1);

	this->m_labelEnemyNumValue->setFont(font1);
	this->m_labelEnemySpeedValue->setFont(font1);

	this->m_labelEnemyNum->move(120, 80);
	this->m_labelEnemySpeed->move(120, 140);

	this->m_labelEnemyNumValue->move(400, 80);
	this->m_labelEnemySpeedValue->move(400, 140);

	this->m_labelEnemyNum->setText("敌人数量:");
	this->m_labelEnemySpeed->setText("敌人速度:");
	this->m_labelEnemyNumValue->setText(QString::number(this->m_sliderEnemyNum->value()));
	this->m_labelEnemySpeedValue->setText(QString::number(this->m_sliderEnemySpeed->value()));
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
void sliderSetStyleSheet(QSlider *slider)
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
	this->m_sliderEnemyNum = new QSlider(Qt::Horizontal, this);
	this->m_sliderEnemyNum->setRange(1, 15);
	this->m_sliderEnemyNum->setFixedWidth(200);
	this->m_sliderEnemyNum->move(200, 80);

	this->m_sliderEnemySpeed = new QSlider(Qt::Horizontal, this);
	this->m_sliderEnemySpeed->setRange(0, 10);
	this->m_sliderEnemySpeed->setFixedWidth(200);
	this->m_sliderEnemySpeed->move(200, 140);

	QList<QSlider *> sliderList = {this->m_sliderEnemyNum, this->m_sliderEnemySpeed};
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
void WidgetSetUp::initCheckbox()
{
	this->m_checkboxReward = new QCheckBox("是否开启奖励模式", this);
	this->m_checkboxReward->move(200, 200);
	m_checkboxReward->setStyleSheet(R"(
		QCheckBox:focus {
            outline: none; /* 移除默认焦点轮廓 */
        }
		QCheckBox { spacing: 8px; }
		QCheckBox::indicator {
			width: 20px; height: 20px;
			border: none;
		}
		QCheckBox::indicator:unchecked {
			border-image: url(:/imagePng/PNG/CHECKBOX_BUTTON.png) 0 60 0 0 stretch;
		}
		QCheckBox::indicator:unchecked:hover {
			border-image: url(:/imagePng/PNG/CHECKBOX_BUTTON.png) 0 40 0 20 stretch;
		}
		QCheckBox::indicator:checked {
			border-image: url(:/imagePng/PNG/CHECKBOX_BUTTON.png) 0 20 0 40 stretch;
		}
		QCheckBox::indicator:checked:hover {
			border-image: url(:/imagePng/PNG/CHECKBOX_BUTTON.png) 0 0 0 60 stretch;
		}
		)");
}
void WidgetSetUp::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);
	painter.drawPixmap(0, 0, this->pixSetUp());
	this->m_buttonDEFAULT->draw(&painter);
	this->m_buttonOK->draw(&painter);
	this->m_buttonCANCEL->draw(&painter);
}
void WidgetSetUp::m_buttonNO_clicked()
{
	this->hide();
	emit allhide();
}
void WidgetSetUp::m_buttonYES_clicked()
{
	this->hide();
	emit this->changeSetUp(m_sliderEnemyNum->value(), m_sliderEnemySpeed->value(), m_checkboxReward->isChecked());
	emit this->needOperator(operatorType::GAMESETUP_SURE_POP);
}
void WidgetSetUp::m_buttonDEFAULT_clicked()
{
	this->m_sliderEnemyNum->setValue(3);
	this->m_sliderEnemySpeed->setValue(3);
	this->m_checkboxReward->setCheckState(Qt::Checked);
}
void WidgetSetUp::loadSetUp(int enemyNum, float enemySpeed, bool isReward)
{
	this->m_sliderEnemyNum->setValue(enemyNum);
	this->m_sliderEnemySpeed->setValue(enemySpeed);
	if (isReward)
	{
		this->m_checkboxReward->setCheckState(Qt::CheckState::Checked);
	}
	else
	{
		this->m_checkboxReward->setCheckState(Qt::CheckState::Unchecked);
	}
}
