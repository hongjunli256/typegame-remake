#ifndef MULTIWIDGET_H
#define MULTIWIDGET_H

#include <QLabel>
#include "imagebutton.h"
#include "myabstractwidget.h"
class MultiWidget : public MyAbstractWidget
{
	Q_OBJECT
public:
	explicit MultiWidget(QWidget *parent = nullptr);

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	//界面元素
	ImageButton *m_buttonCreate = nullptr;
	ImageButton *m_buttonJoin = nullptr;
	ImageButton *m_buttonRefresh = nullptr;
	ImageButton *m_buttonReturn = nullptr;
	void initButton();
	QLabel *label;
	void initLabel();
	static const QPixmap &pixExit();

public slots:
	void m_buttonCreate_clicked();
	void m_buttonJoin_clicked();
	void m_buttonRefresh_clicked();
	void m_buttonReturn_clicked();
signals:
};

#endif // MULTIWIDGET_H
