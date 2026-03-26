#include "widgetsetup.h"
#include <QFile>
#include <QJsonArray>
#include <QMessageBox>
const QPixmap& WidgetSetUp::pixSetUp()
{
	static const QPixmap pix(":/imagePng/PNG/FROG_SETUP.png");
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

	m_wordDictionary = loadWordDictionary("words.json");
	this->loadWordDictionary("words.json");

	m_difficultyCombo = new QComboBox(this);
	m_difficultyCombo->move(100, 100);
	m_difficultyCombo->setFocusPolicy(Qt::NoFocus); // 禁用焦点
	QStringList difficultyOptions = m_wordDictionary.keys();
	m_difficultyCombo->addItems(difficultyOptions);

	connect(this->m_sliderGameLevel, &QSlider::valueChanged, this,
			[this]()
			{
				this->m_labelGameLevelValue->setText(QString::number(this->m_sliderGameLevel->value()));
				this->m_labelGameLevelValue->adjustSize();
			});
	connect(this->m_buttonDEFAULT,&ImageButton::clicked,this,&WidgetSetUp::m_buttonDEFAULT_clicked);
	connect(this->m_buttonOK, &ImageButton::clicked, this, &WidgetSetUp::m_buttonYES_clicked);
	connect(this->m_buttonCANCEL, &ImageButton::clicked, this, &WidgetSetUp::m_buttonNO_clicked);
}
void WidgetSetUp::initLabel()
{
	this->m_labelGameLevel = new QLabel(this);
	this->m_labelGameLevelValue = new QLabel(this);
	QFont font1("黑体", 10, 10);
	this->m_labelGameLevel->setFont(font1);
	this->m_labelGameLevelValue->setFont(font1);
	this->m_labelGameLevel->move(120, 80);
	this->m_labelGameLevelValue->move(400, 80);
	this->m_labelGameLevel->setText("游戏等级:");
	this->m_labelGameLevelValue->setText(QString::number(this->m_sliderGameLevel->value()));
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

	QList<QSlider *> sliderList = {this->m_sliderGameLevel};
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
	emit this->changeSetUp(m_sliderGameLevel->value(), this->m_difficultyCombo->currentText());
	emit needOperator(operatorType::GAMERESUME);
	emit this->needOperator(operatorType::GAMESETUP_SURE_POP);
}
void WidgetSetUp::m_buttonDEFAULT_clicked()
{
	this->m_sliderGameLevel->setValue(3);
}
void WidgetSetUp::loadSetUp(int gameLevel, QString selectedDifficulty)
{
	this->m_sliderGameLevel->setValue(gameLevel);
	this->m_selectedDifficulty = selectedDifficulty;
	m_difficultyCombo->setCurrentText(m_selectedDifficulty);
}
QJsonObject WidgetSetUp::loadWordDictionary(const QString &filePath)
{
	QFile file(filePath);
	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::warning(this, "警告", QString("未找到单词文件：%1").arg(filePath));
		// 返回默认难度配置
		QJsonObject defaultDict;
		defaultDict["easy"] = QJsonArray({"cat", "dog", "sun"});
		defaultDict["medium"] = QJsonArray({"apple", "banana", "table"});
		defaultDict["hard"] = QJsonArray({"computer", "elephant", "beautiful"});
		return defaultDict;
	}

	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
	if (error.error != QJsonParseError::NoError)
	{
		QMessageBox::warning(this, "警告", QString("单词文件格式错误：%1").arg(error.errorString()));
		// 返回默认配置
		QJsonObject defaultDict;
		defaultDict["easy"] = QJsonArray({"cat", "dog", "sun"});
		defaultDict["medium"] = QJsonArray({"apple", "banana", "table"});
		defaultDict["hard"] = QJsonArray({"computer", "elephant", "beautiful"});
		return defaultDict;
	}

	file.close();
	return doc.object();
}
