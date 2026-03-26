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
	ImageButton *m_buttonEnd = nullptr;
	ImageButton *m_buttonPause = nullptr;
	ImageButton *m_buttonStart = nullptr;
	ImageButton *m_buttonSetUp = nullptr;
	ImageButton *m_buttonExit = nullptr;

	void initButtons();

private slots:
	void m_buttonEndClicked();
	void m_buttonPauseClicked();
	void m_buttonStartClicked();
	void m_buttonSetUpClicked();
	void m_buttonExitClicked();
public slots:
signals:
	void needBGM(BGMtype type);
	void needPauseBGM();
};

#endif // UILAYER_H
