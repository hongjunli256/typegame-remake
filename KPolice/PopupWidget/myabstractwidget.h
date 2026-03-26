#ifndef MYABSTRACTWIDGET_H
#define MYABSTRACTWIDGET_H

#include <QWidget>
#include "public_enum.h"
class MyAbstractWidget : public QWidget
{
	Q_OBJECT
public:
	explicit MyAbstractWidget(QWidget *parent = nullptr)
		: QWidget(parent) {};

protected:
signals:
	void needOperator(operatorType type);
	void needSound(soundType type);
	void allhide();
};

#endif // MYABSTRACTWIDGET_H
