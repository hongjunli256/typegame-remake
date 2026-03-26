#ifndef ITEMPOOL_H
#define ITEMPOOL_H
#include <QJsonObject>
#include <QRandomGenerator>
#include "PopupWidget/myabstractwidget.h"
#include "frog.h"
#include "leaf.h"
class ItemPool : public MyAbstractWidget //负责对象的管理以及统计
{
	Q_OBJECT
public:
	explicit ItemPool(QWidget *parent = nullptr);
	~ItemPool();
	void loadSetUp(int gameLevel, QString selectedDifficulty);
	void hitWord(QString targetChar);
	//三大功能
	void init();
	void timer_start();
	void timer_pause();
	void refresh();

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	void drawItem(QPainter *painter);

	int nowPos = 0;		   //0,1,2,3,4//当为4的时候这个青蛙结束，finishFrogNum++,刷新单词再来
	int finishFrogNum = 0; //0,1,2,3,4,5,当为5的时候游戏胜利
	QList<Leaf *> frogPath;

	QJsonObject m_wordDictionary;
	QJsonObject loadWordDictionary(const QString &filePath);
	QString generateRandomString();
	QString m_selectedDifficulty = "easy";
	TextBox *textBoxFinal = nullptr;

	void initLeaf();
	void createLeaf();
	QList<Leaf *> m_LeafList; //其实也就9个
	void cleanUp(Leaf *leaf);

	void initFrog();
	void createFrog();
	QList<Frog *> m_frogList;		   //其实也就5个
	void changeFrogPos(int direction); //青蛙转向

	double m_slideTime = 10.0; //设置相关
	int m_gameLevel = 3;
};

#endif // ITEMPOOL_H
