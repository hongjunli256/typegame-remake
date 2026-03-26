#ifndef WIDGETEXIT_H
#define WIDGETEXIT_H

#include <QLabel>
#include "imagebutton.h"
#include "myabstractwidget.h"
class WidgetExit : public MyAbstractWidget
{
    Q_OBJECT
public:
    explicit WidgetExit(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event)override;

private:
	//界面元素
	ImageButton *m_buttonREPLAY = nullptr;
	ImageButton *m_buttonExit = nullptr;
	void initButton();
	QLabel *label;
	void initLabel();

	static const QPixmap &pixExit();

public slots:
    void m_buttonExit_clicked();
    void m_buttonCancel_clicked();
signals:
	void allhide();
};

#endif // WIDGETEXIT_H
