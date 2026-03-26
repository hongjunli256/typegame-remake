#ifndef POPWIDGETSMANAGER_H
#define POPWIDGETSMANAGER_H

#include "mapview.h"
#include "widgetexit.h"
#include "widgetranklist.h"
#include "widgetsetup.h"
#include "widgetsetupsure.h"
class PopWidgetsManager : public MyAbstractWidget
{
	Q_OBJECT
public:
	explicit PopWidgetsManager(QWidget *parent = nullptr);

	void loadSetUp(int enemyNum, float enemySpeed, bool isReward);

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	WidgetRankList *m_widgetRankList = nullptr;
	void createWidgetRankList();

	WidgetSetUp *m_widgetSetUp = nullptr;
	void createWidgetSetUp();

	widgetSetUpSure *m_widgetSetUpSure = nullptr;
	void createWidgetSetUpSure();

	MapView *m_mapView = nullptr;
	void createMapView();

	WidgetExit *m_widgetExit = nullptr;
	void createWidgetExit();

signals:
	void changeSetUp(int enemyNum, float enemySpeed, bool isReward);

public slots:
	void PopUp(operatorType type);
};

#endif // POPWIDGETSMANAGER_H
