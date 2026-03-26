#ifndef WIDGETWIN_H
#define WIDGETWIN_H

#include <QLabel>
#include "imagebutton.h"
#include "myabstractwidget.h"
class WidgetWin : public MyAbstractWidget
{

    Q_OBJECT
public:
	explicit WidgetWin(QWidget *parent = nullptr);

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	QLabel *label;
	ImageButton *m_buttonREPLAY = nullptr;
	ImageButton *m_buttonEND = nullptr;
	ImageButton *m_buttonNEXT = nullptr;

	static const QPixmap &pixFail();
	void initLabel();
	void initButton();

public slots:
    void m_buttonResume_clicked();
    void m_buttonNext_clicked();
    void m_buttonEnd_clicked();
signals:
    void endGame();
    void startGame();
    void nextGame();
	void allhide();
};

#endif // WIDGETWIN_H
