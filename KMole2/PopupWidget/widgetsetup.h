#ifndef WIDGETSETUP_H
#define WIDGETSETUP_H

#include <QLabel>
//#include <QSettings>
#include <QSlider>
#include "imagebutton.h"
#include "myabstractwidget.h"

class WidgetSetUp : public MyAbstractWidget
{
    Q_OBJECT
public:
    explicit WidgetSetUp(QWidget *parent = nullptr);
	void setUpforNextLevel();

protected:
    void paintEvent(QPaintEvent *event)override;

private:
	QSlider *m_sliderGameTime = nullptr;
	QSlider *m_sliderSpareTimeforMouse = nullptr;
	QSlider *m_sliderStayTime = nullptr;

	QLabel *m_labelSetUpGameTime = nullptr;
	QLabel *m_labelSetUpSpareTimeforMouse = nullptr;
	QLabel *m_labelSetUpStayTime = nullptr;

	QLabel *m_labelGameTimeValue = nullptr;
	QLabel *m_labelSpareTimeforMouseValue = nullptr;
	QLabel *m_labelStayTimeValue = nullptr;

	ImageButton *m_buttonOK = nullptr;
	ImageButton *m_buttonCANCEL = nullptr;
	ImageButton *m_buttonDEFAULT = nullptr;

	static const QPixmap &pixSetUp();
	void initLabel();
	void initButton();
	void initSlider();

public slots:
    void m_buttonYES_clicked();
    void m_buttonNO_clicked();
    void m_buttonDEFAULT_clicked();
	void loadSetUp(int stayTime, int spareTimeforMouse, int gameTime);
signals:
	void changeSetUp(int stayTime, int spareTimeforMouse, int gameTime);
	void allhide();
};
#endif // WIDGETSETUP_H
