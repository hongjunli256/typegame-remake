#ifndef MOUSEPOOL_H
#define MOUSEPOOL_H
#include<QRandomGenerator>
#include "PopupWidget/myabstractwidget.h"
#include "rat.h"
class MousePool : public MyAbstractWidget //负责对象的管理以及统计
{
    Q_OBJECT
public:
	explicit MousePool(QWidget *parent = nullptr);
	~MousePool();
	void cleanup();
	void drawMouse(QPainter *painter);
	bool hitMouse(char targetChar);
	void pause();
	void resume();
	void init();
	void loadSetUp(int stayTime, int spareTimeforMouse, int gameTime);

private:
	QTimer *m_timerAddMouse;

	int m_stayTime = 6;
	int m_spareTimeforMouse = 0;

	char generateRandomLetter();
	int generateSuitablePos();
	bool isThereRat[10] = {false};
	QList<Rat *> m_ratList;
	QList<Rat *> m_ratWaitList; //墓地
	void addRat(int stayTime);
	void removeRat(Rat *rat);

signals:
	void stealVegetable();
public slots:
};

#endif // MOUSEPOOL_H
