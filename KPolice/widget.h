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

private:
	GameMedia *m_gameMedia = nullptr;
	PopWidgetsManager *m_popWidgetsManager;
	void initPopWidgetManager();

	ImageButton *m_buttonSinglePlay = nullptr;
	ImageButton *m_buttonMulitiPlay = nullptr;
	ImageButton *m_buttonExit = nullptr;
	void initButton();

	static const QPixmap &pixWidget();

	bool isPolice = 1;
	bool isCar1 = 1;
	bool isCar2 = 1;

	void paintEvent(QPaintEvent *event) override;

	void handleOperator(operatorType type);
	void loadConfig();
	void saveConfig();

	void globalSetUp();

	void changeSetUp(bool isPolice, bool isCar1, bool isCar2, QString StringPath);
private slots:
	void m_buttonSinglePlay_clicked();
	void m_buttonMulitiPlay_clicked();
	void m_buttonExit_clicked();
signals:
};
#endif // WIDGET_H
