#ifndef WIDGETWIN_H
#define WIDGETWIN_H

#include <QKeyEvent>
#include "myabstractwidget.h"
class WidgetWin : public MyAbstractWidget
{

    Q_OBJECT
public:
	explicit WidgetWin(QWidget *parent = nullptr);
	void loadSetUp(bool isPolice);

protected:
	void paintEvent(QPaintEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;

private:
	bool isPolice = true;
	static const QPixmap &pixWin(bool isPolice = true);

public slots:

signals:
};

#endif // WIDGETWIN_H
