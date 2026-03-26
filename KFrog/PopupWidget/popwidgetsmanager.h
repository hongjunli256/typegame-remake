#ifndef POPWIDGETSMANAGER_H
#define POPWIDGETSMANAGER_H

#include "widgetexit.h"
#include "widgetfail.h"
#include "widgetsetup.h"
#include "widgetsetupsure.h"
#include "widgetwin.h"

class PopWidgetsManager : public MyAbstractWidget
{
	Q_OBJECT
public:
	explicit PopWidgetsManager(QWidget *parent = nullptr);

	void loadSetUp(int gameLevel, QString selectedDifficulty);

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	WidgetSetUp *m_widgetSetUp = nullptr;
	void createWidgetSetUp();

	widgetSetUpSure *m_widgetSetUpSure = nullptr;
	void createWidgetSetUpSure();

	WidgetExit *m_widgetExit = nullptr;
	void createWidgetExit();

	WidgetFail *m_widgetFail = nullptr;
	void createWidgetFail();

	WidgetWin *m_widgetWin = nullptr;
	void createWidgetWin();

signals:
	void changeSetUp(int gameLevel, QString selectedDifficulty);

public slots:
	void PopUp(operatorType type);
};

#endif // POPWIDGETSMANAGER_H
