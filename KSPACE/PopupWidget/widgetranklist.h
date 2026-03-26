#ifndef WIDGETRANKLIST_H
#define WIDGETRANKLIST_H

#include <QLabel>
#include <QListWidget>
#include "imagebutton.h"
#include "myabstractwidget.h"
struct RankItem
{
	QString name; // 姓名
	int score;	  // 分数

	// 重载小于运算符，用于按分数降序排序（分数高的排前面）
	bool operator<(const RankItem &other) const { return score > other.score; }
};
class WidgetRankList : public MyAbstractWidget
{
	Q_OBJECT
public:
	explicit WidgetRankList(QWidget *parent = nullptr);

protected:
	void paintEvent(QPaintEvent *event) override;

public slots:
	void addGameScore(const QString &name, int score);

private:
	ImageButton *m_buttonReturn = nullptr;
	QListWidget *m_rankListWidget = nullptr; // 排行榜列表控件
	QVector<RankItem> m_rankData;			 // 存储排行榜原始数据

	void initButton();
	void initRankListWidget();
	void loadRankDataFromIni();
	void saveRankDataToIni();
	void updateRankList();
	static const QPixmap &pixExit();

private slots:
	void m_buttonReturn_clicked();
signals:
};

#endif // WIDGETRANKLIST_H
