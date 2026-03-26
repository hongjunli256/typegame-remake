#ifndef WIDGET_H
#define WIDGET_H

#include <QPainter>
#include <QTimer>
#include <QWidget>
#include "PopupWidget/popwidgetsmanager.h"
#include "gamemedia.h"
class Widget : public MyAbstractWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);

    ~Widget();

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	GameMedia *m_gameMedia = nullptr;
	PopWidgetsManager *m_popWidgetsManager;
	void initPopWidgetManager();

	gameCondition m_gameCondition = gameCondition::START;

	ImageButton *m_buttonStart = nullptr;
	ImageButton *m_buttonRankList = nullptr;
	ImageButton *m_buttonSetUp = nullptr;
	ImageButton *m_buttonExit = nullptr;
	void initButton();

	static const QPixmap &pixWidget();
	void nextlevel();
	int m_enemyNum = 4;
	float m_enemySpeed = 1;
	bool m_isReward = false;

	void handleOperator(operatorType type);
	void loadConfig();
	void saveConfig();
	void changeGameCondition(gameCondition condition);
	void globalSetUp();
	void changeSetUp(int enemyNum, float enemySpeed, bool isReward);
private slots:
	void m_buttonStart_clicked();
	void m_buttonRankList_clicked();
	void m_buttonSetUp_clicked();
	void m_buttonExit_clicked();
signals:
};
#endif // WIDGET_H
