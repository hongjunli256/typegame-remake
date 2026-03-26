#ifndef UILAYER_H
#define UILAYER_H

#include <QLabel>
#include <QTimer>
#include <QWidget>
#include "PopupWidget/imagebutton.h"
#include "PopupWidget/myabstractwidget.h"

class UILayer : public MyAbstractWidget
{
    Q_OBJECT
public:
	explicit UILayer(QWidget *parent = nullptr);
	void timer_pause();
	void timer_start();
	void init();
	void changeGameCondition(gameCondition condition);

protected:
    void paintEvent(QPaintEvent *event)override;

private:
	QLabel *m_labelTimeLimited = nullptr;
	QLabel *m_labelCountDown = nullptr;
	QLabel *m_labelAccuracyRate = nullptr;
	QLabel *m_labelHitCount = nullptr;
	void initLabels();

	ImageButton *m_buttonEnd = nullptr;
	ImageButton *m_buttonPause = nullptr;
	ImageButton *m_buttonStart = nullptr;
	ImageButton *m_buttonSetUp = nullptr;
	ImageButton *m_buttonExit = nullptr;
	void initButtons();

	int m_timeLimited = 1;
	int m_CountDown = 60;
	int m_HitCount = 0;
	int m_pressCount = 0;

	QTimer *m_timerRefresh = nullptr;
	void initTimers();

private slots:

	void refresh();
	void m_buttonEndClicked();
	void m_buttonPauseClicked();
	void m_buttonStartClicked();
	void m_buttonSetUpClicked();
	void m_buttonExitClicked();
public slots:
	void isHitMouse(bool isHit);
signals:
	void needBGM(BGMtype type);
	void needPauseBGM();
};

#endif // UILAYER_H
