#ifndef WIDGET_H
#define WIDGET_H

#include <QPainter>
#include <QTimer>
#include <QWidget>
#include "PopupWidget/popwidgetsmanager.h"
#include "gamemap.h"
#include "gamemedia.h"
#include "uilayer.h"
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);

    ~Widget();

private:
	GameMap *m_gameMap = nullptr;
	UILayer*m_uiLayer=nullptr;
	GameMedia *m_gameMedia = nullptr;
	PopWidgetsManager *m_popWidgetsManager;

	gameCondition m_gameCondition;

	int m_gameTime = 3;
	int m_spareTimeforMouse = 5;
	int m_StayTime = 100;

	void paintEvent(QPaintEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;

	void handleOperator(operatorType type);
	void changeGameCondition(gameCondition condition);

	void loadConfig();
	void saveConfig();

	void timer_start();
	void timer_pause();
	void init();
	void resume();
	void nextlevel();
	void globalSetUp();

	void changeSetUp(int stayTime, int spareTimeforMouse, int gameTime);

signals:
	void needSound(soundType type);
};
#endif // WIDGET_H
