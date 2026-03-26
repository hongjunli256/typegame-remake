#include "widgetsetup.h"
#include <QDir>
const QPixmap& WidgetSetUp::pixSetUp()
{
	static const QPixmap pix(":/imagePng/PNG/POLICE_SETTING_BG.png");
	return pix;
}
WidgetSetUp::WidgetSetUp(QWidget *parent)
	: MyAbstractWidget{parent}
{
	this->move(0, 0);
	this->setFixedSize(this->pixSetUp().size());
	this->initButton();
	this->initComBox();

	this->hide();
}
void WidgetSetUp::initComBox()
{
	QString folderPath = "articles";
	QDir dir(folderPath);
	if (!dir.exists())
	{
		qDebug() << "文件夹不存在！";
		return;
	}
	dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
	dir.setNameFilters({"*.txt"});
	QStringList articleNames = dir.entryList();

	articleList = new QListWidget(this);
	articleList->addItems(articleNames);
	articleList->move(572, 40);
	articleList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	articleList->setFocusPolicy(Qt::NoFocus);
	articleList->setFixedSize(220, 543);
	articleList->setMaximumHeight(16);

	articleList->setStyleSheet(R"(
    /* 列表本身：透明背景+黄色边框 */
    QListWidget {
        background: transparent;
        border: 2px solid #FBBF24;
        color: #FBBF24;
        font-size: 14px;
    }

    /* 未选中项：透明背景（显示父窗口背景） */
    QListWidget::item {
        background: transparent;
        padding: 5px 10px;
        height: 25px;
    }

    /* 选中项：黑色背景 */
    QListWidget::item:selected {
        background: black;
        color: #FBBF24;
    }
)");
}
void WidgetSetUp::initButton()
{
	m_buttonPolice = new ImageButton(":/imagePng/PNG/POLICE_POLICE.png", this, QPoint(10, 20), 4);
	m_buttonThief = new ImageButton(":/imagePng/PNG/POLICE_THIEF.png", this, QPoint(295, 20), 4);
	connect(m_buttonPolice, &ImageButton::clicked, this, &WidgetSetUp::m_buttonPolice_clicked);
	connect(m_buttonThief, &ImageButton::clicked, this, &WidgetSetUp::m_buttonThief_clicked);

	m_buttonCar1 = new ImageButton(":/imagePng/PNG/POLICE_CAR.png", this, QPoint(40, 220), 4);
	m_buttonBike1 = new ImageButton(":/imagePng/PNG/POLICE_BIKE.png", this, QPoint(140, 220), 4);
	connect(m_buttonCar1, &ImageButton::clicked, this, &WidgetSetUp::m_buttonCar1_clicked);
	connect(m_buttonBike1, &ImageButton::clicked, this, &WidgetSetUp::m_buttonBike1_clicked);

	m_buttonCar2 = new ImageButton(":/imagePng/PNG/POLICE_CAR.png", this, QPoint(325, 220), 4);
	m_buttonBike2 = new ImageButton(":/imagePng/PNG/POLICE_BIKE.png", this, QPoint(425, 220), 4);
	connect(m_buttonCar2, &ImageButton::clicked, this, &WidgetSetUp::m_buttonCar2_clicked);
	connect(m_buttonBike2, &ImageButton::clicked, this, &WidgetSetUp::m_buttonBike2_clicked);

	m_buttonStart = new ImageButton(":/imagePng/PNG/POLICE_START.png", this, QPoint(220, 520), 3);
	m_buttonCancel = new ImageButton(":/imagePng/PNG/POLICE_CANCEL.png", this, QPoint(320, 520), 3);
	connect(m_buttonStart, &ImageButton::clicked, this, &WidgetSetUp::m_buttonStart_clicked);
	connect(m_buttonCancel, &ImageButton::clicked, this, &WidgetSetUp::m_buttonCancel_clicked);

	QList<ImageButton *> btnList = {m_buttonPolice, m_buttonThief, m_buttonCar1, m_buttonBike1, m_buttonCar2, m_buttonBike2};
	for (ImageButton *btn : btnList)
	{
		connect(btn, &ImageButton::needSound, this, &WidgetSetUp::needSound);
	}
}

void WidgetSetUp::paintEvent(QPaintEvent *event){
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.drawPixmap(0,0,this->pixSetUp());
	m_buttonPolice->draw(&painter);
	m_buttonThief->draw(&painter);
	m_buttonCar1->draw(&painter);
	m_buttonBike1->draw(&painter);
	m_buttonCar2->draw(&painter);
	m_buttonBike2->draw(&painter);
	m_buttonStart->draw(&painter);
	m_buttonCancel->draw(&painter);
}
void WidgetSetUp::m_buttonPolice_clicked()
{
	this->m_buttonPolice->disable();
	this->m_buttonPolice->ForceCondition(2);
	this->m_buttonThief->enable();
	this->isPolice = true;
}
void WidgetSetUp::m_buttonThief_clicked()
{
	this->m_buttonThief->disable();
	this->m_buttonThief->ForceCondition(2);
	this->m_buttonPolice->enable();
	this->isPolice = false;
}
void WidgetSetUp::m_buttonCar1_clicked()
{
	this->m_buttonCar1->disable();
	this->m_buttonCar1->ForceCondition(1);
	this->m_buttonBike1->enable();
	this->isCar1 = true;
}
void WidgetSetUp::m_buttonBike1_clicked()
{
	this->m_buttonBike1->disable();
	this->m_buttonBike1->ForceCondition(1);
	this->m_buttonCar1->enable();
	this->isCar1 = false;
}
void WidgetSetUp::m_buttonCar2_clicked()
{
	this->m_buttonCar2->disable();
	this->m_buttonCar2->ForceCondition(1);
	this->m_buttonBike2->enable();
	this->isCar2 = true;
}
void WidgetSetUp::m_buttonBike2_clicked()
{
	this->m_buttonBike2->disable();
	this->m_buttonBike2->ForceCondition(1);
	this->m_buttonCar2->enable();
	this->isCar2 = false;
}
void WidgetSetUp::m_buttonStart_clicked()
{
	if (articleList->currentItem() != nullptr)
	{
		QString textName = articleList->currentItem()->text();
		this->hide();
		emit changeSetUp(this->isPolice, this->isCar1, this->isCar2, textName);
		emit this->needOperator(operatorType::GAMEMAP_POP);
	}
}
void WidgetSetUp::m_buttonCancel_clicked()
{
	this->hide();
	emit allhide();
}

void WidgetSetUp::loadSetUp(bool isPolice, bool isCar1, bool isCar2)
{
	this->isPolice = isPolice;
	this->isCar1 = isCar1;
	this->isCar2 = isCar2;
	if (isPolice)
	{
		this->m_buttonPolice_clicked();
	}
	else
	{
		this->m_buttonThief_clicked();
	}

	if (isCar1)
	{
		this->m_buttonCar1_clicked();
	}
	else
	{
		this->m_buttonBike1_clicked();
	}
	if (isCar2)
	{
		this->m_buttonCar2_clicked();
	}
	else
	{
		this->m_buttonBike2_clicked();
	}
}
