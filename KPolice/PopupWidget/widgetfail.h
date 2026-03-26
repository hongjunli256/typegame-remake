#ifndef WIDGETFAIL_H
#define WIDGETFAIL_H

#include "myabstractwidget.h"
class WidgetFail : public MyAbstractWidget
{
    Q_OBJECT
public:
    explicit WidgetFail(QWidget *parent = nullptr);
	void loadSetUp(bool isPolice);

protected:
	void paintEvent(QPaintEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;

private:
	bool isPolice = true;
	static const QPixmap &pixFail(bool isPolice = true);

public slots:

signals:
};

#endif // WIDGETFAIL_H
