#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QLabel>
#include "myabstractwidget.h"
class StatusBar : public MyAbstractWidget
{
	Q_OBJECT
public:
	explicit StatusBar(QWidget *parent = nullptr);
	void loadSetUp(bool isPolice, QString StringPath);
	bool receiveHit(QString &c);
	void init();
	void draw(QPainter *painter);

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	static const QPixmap &pixStatusBar();
	static const QPixmap &pixSliderBarBlue();
	static const QPixmap &pixSliderBarYellow();

	void refresh();
	// 状态栏相关成员（新增）
	static const QFont fontSmall;
	QString textString;
	QString subTextString;
	int currentIndex;
	QString stringPath;
	bool isPolice;
	void drawString(QPainter *painter);
signals:
	void timeout(); //文章打完了
};

#endif // STATUSBAR_H
