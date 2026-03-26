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
	QSlider *m_sliderGameLevel = nullptr;
	QSlider *m_sliderFailNum = nullptr;
	QSlider *m_sliderWinNum = nullptr;

	QLabel *m_labelGameLevel = nullptr;
	QLabel *m_labelFailNum = nullptr;
	QLabel *m_labelWinNum = nullptr;

	QLabel *m_labelGameLevelValue = nullptr;
	QLabel *m_labelFailNumValue = nullptr;
	QLabel *m_labelWinNumValue = nullptr;

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
	void loadSetUp(int winNum, int failNum, int gameLevel);
signals:
	void changeSetUp(int winNum, int failNum, int gameLevel);
	void allhide();
};

#endif // WIDGETSETUP_H
