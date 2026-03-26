#include "widgetranklist.h"
#include <QSettings>
const QPixmap &WidgetRankList::pixExit()
{
	static const QPixmap pix(":/imagePng/PNG/SPACE_HISCORE_BG.png"); // 替换为你的图片路径
	return pix;
}
WidgetRankList::WidgetRankList(QWidget *parent)
	: MyAbstractWidget{parent}
{
	this->move(0, 0);
	this->resize(pixExit().size());
	initButton();
	initRankListWidget();
	loadRankDataFromIni();
	this->hide();
}

void WidgetRankList::initButton()
{
	this->m_buttonReturn = new ImageButton(":/imagePng/PNG/SPACE_RETURN.png", this, QPoint(500, 500), 3);
	connect(this->m_buttonReturn, &ImageButton::clicked, this, &::WidgetRankList::m_buttonReturn_clicked);

	QList<ImageButton *> btnList = {this->m_buttonReturn};
	for (ImageButton *btn : btnList)
	{
		connect(btn, &ImageButton::needSound, this, &MyAbstractWidget::needSound);
	}
}

void WidgetRankList::m_buttonReturn_clicked()
{
	this->hide();
	emit allhide();
}

void WidgetRankList::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);
	painter.drawPixmap(0, 0, this->pixExit());
	this->m_buttonReturn->draw(&painter);
}
void WidgetRankList::initRankListWidget()
{
	m_rankListWidget = new QListWidget(this);
	m_rankListWidget->move(243, 153);
	m_rankListWidget->setFixedWidth(350);

	// ========== 核心样式调整 ==========
	m_rankListWidget->setStyleSheet(R"(
		QListWidget {
			background: transparent; /* 完全透明背景，贴合原有背景 */
			border: none; /* 隐藏ListWidget边框 */
			padding: 0; /* 去掉内边距 */
			color: yellow; /* 字体颜色，可根据背景调整（如white/gold） */
		}
		QListWidget::item {
			height: 35px; /* 行高（适配背景每行高度，自行调整） */
			margin: 0; /* 去掉条目间距 */
			font-family: "微软雅黑"; /* 字体，可替换为黑体/游戏字体 */
		}
		/* 即使意外选中，也无视觉变化（双重保障） */
		QListWidget::item:selected {
			background: transparent;
			color: yellow; /* 与默认字体颜色一致 */
		}
		QScrollBar:vertical {
			width: 0; /* 隐藏滚动条（如需保留可改为8px并调整样式） */
			background: transparent;
		}
	)");

	// ========== 字体设置 ==========
	QFont listFont = m_rankListWidget->font();
	listFont.setPointSize(16); // 字体大小，适配背景
	listFont.setBold(true);	   // 字体加粗，更醒目
	m_rankListWidget->setFont(listFont);

	// ========== 禁用选择的关键设置（多重保障） ==========
	// 1. 禁止编辑（原有）
	m_rankListWidget->setEditTriggers(QListWidget::NoEditTriggers);
	// 2. 禁用焦点（无法通过键盘选中）
	m_rankListWidget->setFocusPolicy(Qt::NoFocus);
	// 3. 禁用所有选择模式（核心：彻底禁止选择）
	m_rankListWidget->setSelectionMode(QAbstractItemView::NoSelection);
	// 4. 禁用鼠标跟踪（可选：避免鼠标悬浮时的视觉变化）
	m_rankListWidget->setMouseTracking(false);
}

// 从INI文件加载排行榜数据
void WidgetRankList::loadRankDataFromIni()
{
	QSettings settings("game_rank.ini", QSettings::IniFormat);
	// 获取排行榜条目数量
	int count = settings.value("Rank/Count", 0).toInt();
	m_rankData.clear();

	// 遍历读取每个条目
	for (int i = 0; i < count; ++i)
	{
		RankItem item;
		item.name = settings.value(QString("Rank/%1/Name").arg(i)).toString();
		item.score = settings.value(QString("Rank/%1/Score").arg(i)).toInt();
		m_rankData.append(item);
	}

	// 加载数据后更新显示
	updateRankList();
}

// 将排行榜数据保存到INI文件
void WidgetRankList::saveRankDataToIni()
{
	QSettings settings("game_rank.ini", QSettings::IniFormat);
	settings.clear(); // 清空原有数据（避免残留旧数据）

	// 保存条目数量
	settings.setValue("Rank/Count", m_rankData.size());

	// 遍历保存每个条目
	for (int i = 0; i < m_rankData.size(); ++i)
	{
		settings.setValue(QString("Rank/%1/Name").arg(i), m_rankData[i].name);
		settings.setValue(QString("Rank/%1/Score").arg(i), m_rankData[i].score);
	}

	settings.sync(); // 立即写入文件（确保数据不丢失）
}

void WidgetRankList::updateRankList()
{
	// 清空列表
	m_rankListWidget->clear();

	// 按分数降序排序
	std::sort(m_rankData.begin(), m_rankData.end());

	// 限制排行榜最大条目数（比如只保留前10名，可根据需求修改）
	int maxRankCount = 10;
	if (m_rankData.size() > maxRankCount)
	{
		m_rankData.resize(maxRankCount);
	}

	// 格式化条目并添加到列表（改为「xxx:10000分」格式）
	for (int i = 0; i < m_rankData.size(); ++i)
	{
		const auto &item = m_rankData[i];
		QString itemText = QString("%1、%2:%3分")
							   .arg(i + 1) // 排名从1开始（可选：删除这部分则无排名）
							   .arg(item.name)
							   .arg(item.score);

		m_rankListWidget->addItem(itemText);
	}
}

// 对外接口：添加游戏分数到排行榜
void WidgetRankList::addGameScore(const QString &name, int score)
{
	if (name.isEmpty() || score < 0)
	{ // 校验输入（分数不允许为负）
		return;
	}
	bool isPlayerExist = false;
	for (auto &item : m_rankData)
	{
		if (item.name == name)
		{
			item.score = qMax(item.score, score); // 保留最高分
			isPlayerExist = true;
			break;
		}
	}
	if (!isPlayerExist)
	{
		m_rankData.append({name, score});
	}

	// 更新显示并保存到INI文件
	updateRankList();
	saveRankDataToIni();
}
