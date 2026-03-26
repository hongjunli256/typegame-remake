#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QLabel>
#include <QProgressBar>
#include "myabstractwidget.h"
class StatusBar : public MyAbstractWidget
{
	Q_OBJECT
public:
	explicit StatusBar(QWidget *parent = nullptr);
	void draw(QPainter *painter);
	void init();
	void loseHp();
	void addHp();
	bool isDie();
	void refresh(int &score);

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	static const QPixmap &pixStatusBar();
	QLabel *scorePix;
	QLabel *scoreString;
	QLabel *lifePix;
	QLabel *timePix;
	QLabel *timeString;
	QLabel *information;
	void initLabels();

	QProgressBar *lifeBar;
	void initProgressBar();
	int lifeNum;
	int remainingTime = 120;
	//QTimer *timer;

	// 状态栏相关成员（新增）
	static const QFont fontSmall;
signals:
	//void timeout(); //文章打完了
};

#endif // STATUSBAR_H
