#ifndef POPWIDGETSMANAGER_H
#define POPWIDGETSMANAGER_H

#include "mapview.h"
#include "multiwidget.h"
#include "widgetexit.h"
#include "widgetfail.h"
#include "widgetsetup.h"
#include "widgetwin.h"
class PopWidgetsManager : public MyAbstractWidget
{
	Q_OBJECT
public:
	explicit PopWidgetsManager(QWidget *parent = nullptr);

	void loadSetUp(bool isPolice, bool isCar1, bool isCar2, QString StringPath);

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	MultiWidget *m_multiWidget = nullptr;
	void createMultiWidget();

	WidgetSetUp *m_widgetSetUp = nullptr;
	void createWidgetSetUp();

	MapView *m_mapView = nullptr;
	void createMapView();

	WidgetExit *m_widgetExit = nullptr;
	void createWidgetExit();

	WidgetFail *m_widgetFail = nullptr;
	void createWidgetFail();

	WidgetWin *m_widgetWin = nullptr;
	void createWidgetWin();

signals:
	void changeSetUp(bool isPolice, bool isCar1, bool isCar2, QString StringPath);

public slots:
	void PopUp(operatorType type);
};

#endif // POPWIDGETSMANAGER_H
