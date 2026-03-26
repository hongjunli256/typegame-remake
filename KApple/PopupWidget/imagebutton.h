#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QWidget>
#include "public_enum.h"
class ImageButton : public QWidget {
    Q_OBJECT
public:
    // 构造函数：传入三种状态的图片路径
    explicit ImageButton(const QString& srcPath,QWidget* parent,QPoint pos,int conditionNum);
	void draw(QPainter* painter);
	void enable();
	void disable();
signals:
    void clicked();
	void enter();
	void needSound(soundType type);

protected:
    void enterEvent(QEnterEvent *event)override;

    void leaveEvent(QEvent*) override;

    void mousePressEvent(QMouseEvent* e) override;

    void mouseReleaseEvent(QMouseEvent* e) override;

private:
	enum condition
	{
		NORMAL = 0,
		HOVER = 1,
		PRESS = 2,
		FORBIDDEN = 3
	};
	QPixmap m_srcPix;
	condition m_condition=condition::NORMAL;
    int m_conditionNum;
};

#endif // IMAGEBUTTON_H
