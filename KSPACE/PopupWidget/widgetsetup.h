#ifndef WIDGETSETUP_H
#define WIDGETSETUP_H

#include <QCheckBox>
#include <QLabel>
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
	void paintEvent(QPaintEvent *event) override;

private:
	QSlider *m_sliderEnemyNum = nullptr;
	QSlider *m_sliderEnemySpeed = nullptr;

	QLabel *m_labelEnemyNum = nullptr;
	QLabel *m_labelEnemySpeed = nullptr;

	QLabel *m_labelEnemyNumValue = nullptr;
	QLabel *m_labelEnemySpeedValue = nullptr;

	QCheckBox *m_checkboxReward = nullptr;

	ImageButton *m_buttonOK = nullptr;
	ImageButton *m_buttonCANCEL = nullptr;
	ImageButton *m_buttonDEFAULT = nullptr;

	static const QPixmap &pixSetUp();
	void initLabel();
	void initButton();
	void initSlider();
	void initCheckbox();

public slots:
	void m_buttonYES_clicked();
	void m_buttonNO_clicked();
	void m_buttonDEFAULT_clicked();
	void loadSetUp(int enemyNum, float enemySpeed, bool isReward);
signals:
	void changeSetUp(int enemyNum, float enemySpeed, bool isReward);
};

#endif // WIDGETSETUP_H
