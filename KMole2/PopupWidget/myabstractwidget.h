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
		emit needChangeGameCondition(gameCondition::CONTINUE);
		emit needOperator(operatorType::GAMEINIT);
		emit needOperator(operatorType::GAMETIMER_START);
	}
	void toBeginofReadytoPlay()
	{
		emit needChangeGameCondition(gameCondition::READYTOPLAY);
		emit needOperator(operatorType::GAMEINIT);
		emit needOperator(operatorType::GAMETIMER_STOP);
	}
signals:
	void needOperator(operatorType type);
	void needSound(soundType type);
	void needChangeGameCondition(gameCondition condition);
};

#endif // MYABSTRACTWIDGET_H
