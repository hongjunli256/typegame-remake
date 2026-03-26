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

	int m_gameLevel;
	int m_failNum;
	int m_winNum;

	static const QPixmap &pixExit();

	void initLabel();
	void initButton();

public slots:
    void m_buttonYES_clicked();
    void m_buttonNO_clicked();
signals:
};


#endif // WIDGETSETUPSURE_H
