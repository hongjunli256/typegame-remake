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
	void toBeginofContinue()
	{
		emit needChangeGameCondition(gameCondition::START);
		emit needOperator(operatorType::GAMEMAP_POP);
	}
signals:
	void needOperator(operatorType type);
	void needSound(soundType type);
	void needChangeGameCondition(gameCondition condition);
	void allhide();
};

#endif // MYABSTRACTWIDGET_H
