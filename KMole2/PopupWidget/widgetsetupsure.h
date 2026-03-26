#ifndef WIDGETSETUPSURE_H
#define WIDGETSETUPSURE_H

#include <QLabel>
#include "imagebutton.h"
#include "myabstractwidget.h"
class widgetSetUpSure : public MyAbstractWidget
{
    Q_OBJECT
public:
    explicit widgetSetUpSure(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event)override;

private:
	ImageButton *m_buttonNO = nullptr;
	ImageButton *m_buttonYES = nullptr;
	QLabel *label;

	int m_gameTime;
	int m_spareTimeforMouse;
	int m_stayTime;

	static const QPixmap &pixSetUpSure();

	void initLabel();
	void initButton();

public slots:
    void m_buttonYES_clicked();
    void m_buttonNO_clicked();
signals:
	//void changeSetUp(int winNum, int failNum, int gameLevel);
	void allhide();
};

#endif // WIDGETSETUPSURE_H
