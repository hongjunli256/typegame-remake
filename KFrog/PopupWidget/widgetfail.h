#ifndef WIDGETFAIL_H
#define WIDGETFAIL_H

#include <QLabel>
#include "imagebutton.h"
#include "myabstractwidget.h"
class WidgetFail : public MyAbstractWidget
{
    Q_OBJECT
public:
    explicit WidgetFail(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event)override;

private:
	ImageButton *m_buttonREPLAY = nullptr;
	ImageButton *m_buttonEND = nullptr;
	void initButton();

	QLabel *label;
	void initLabel();
	static const QPixmap& pixFail();

public slots:
    void m_buttonResume_clicked();
    void m_buttonEnd_clicked();
signals:
    void endGame();
    void startGame();
	void allhide();
};

#endif // WIDGETFAIL_H
