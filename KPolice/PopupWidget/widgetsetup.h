#ifndef WIDGETSETUP_H
#define WIDGETSETUP_H

#include <QLabel>
//#include <QSettings>
#include <QListWidget>
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
	// void showEvent(QShowEvent *event) override;

private:
	ImageButton *m_buttonPolice = nullptr;
	ImageButton *m_buttonThief = nullptr;
	bool isPolice;

	ImageButton *m_buttonCar1 = nullptr;
	ImageButton *m_buttonBike1 = nullptr;
	bool isCar1;

	ImageButton *m_buttonCar2 = nullptr;
	ImageButton *m_buttonBike2 = nullptr;
	bool isCar2;

	ImageButton *m_buttonStart = nullptr;
	ImageButton *m_buttonCancel = nullptr;

	QListWidget *articleList = nullptr;
	static const QPixmap &pixSetUp();

	void initComBox();
	void initButton();

public slots:
	void m_buttonPolice_clicked();
	void m_buttonThief_clicked();
	void m_buttonCar1_clicked();
	void m_buttonBike1_clicked();
	void m_buttonCar2_clicked();
	void m_buttonBike2_clicked();
	void m_buttonStart_clicked();
	void m_buttonCancel_clicked();
	void loadSetUp(bool isPolice, bool isCar1, bool isCar2);
signals:
	void changeSetUp(bool isPolice, bool isCar1, bool isCar2, QString &StringPath);
};

#endif // WIDGETSETUP_H
