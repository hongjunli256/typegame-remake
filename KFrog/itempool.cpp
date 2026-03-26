#include "itempool.h"
#include <QFile>
#include <QJsonArray>
#include <QMessageBox>
#include <QSettings>
#define holeLength 5 //至少是2
//功能已经实现，但是现在逻辑判断不利于维护，需要优化一下表达或者是做好switch（反正不多）
QString ItemPool::generateRandomString()
{
	if (!m_wordDictionary.contains(m_selectedDifficulty))
		return QString("abcd1");
	QJsonValue difficultyValue = m_wordDictionary[m_selectedDifficulty];
	if (!difficultyValue.isArray())
		return QString("abcd2");
	QJsonArray wordArray = difficultyValue.toArray();
	if (wordArray.isEmpty())
		return QString("abcd3");

	static QList<QChar> last10Chars;
	const int MaxHistory = 10;

	QList<QString> candidates;
	for (const QJsonValue &val : std::as_const(wordArray))
	{
		if (val.isString())
		{
			QString word = val.toString();
			if (!word.isEmpty() && !last10Chars.contains(word.at(0)))
				candidates.append(word);
		}
	}

	if (candidates.isEmpty())
	{
		for (const QJsonValue &val : std::as_const(wordArray))
		{
			if (val.isString() && !val.toString().isEmpty())
				candidates.append(val.toString());
		}
		if (candidates.isEmpty())
			return QString("abcd4");
	}

	int idx = QRandomGenerator::global()->bounded(candidates.size());
	QString selected = candidates[idx];

	if (!selected.isEmpty())
	{
		last10Chars.append(selected.at(0));
		if (last10Chars.size() > MaxHistory)
			last10Chars.removeFirst();
	}

	return selected;
}

ItemPool::ItemPool(QWidget *parent)
	: MyAbstractWidget(parent)
{
	this->move(0, 0);
	this->resize(800, 600);
	this->createFrog();
	this->createLeaf();
	this->init();
	m_wordDictionary = loadWordDictionary("words.json");
	this->timer_pause();
}
QJsonObject ItemPool::loadWordDictionary(const QString &filePath)
{
	QFile file(filePath);
	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::warning(this, "警告", QString("未找到单词文件：%1").arg(filePath));
		QJsonObject defaultDict;
		defaultDict["easy"] = QJsonArray({"cat", "dog", "sun"});
		defaultDict["medium"] = QJsonArray({"apple", "banana", "table"});
		defaultDict["hard"] = QJsonArray({"computer", "elephant", "beautiful"});
		return defaultDict;
	}

	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
	if (error.error != QJsonParseError::NoError)
	{
		QMessageBox::warning(this, "警告", QString("单词文件格式错误：%1").arg(error.errorString()));
		QJsonObject defaultDict;
		defaultDict["easy"] = QJsonArray({"cat", "dog", "sun"});
		defaultDict["medium"] = QJsonArray({"apple", "banana", "table"});
		defaultDict["hard"] = QJsonArray({"computer", "elephant", "beautiful"});
		return defaultDict;
	}

	file.close();
	return doc.object();
}
ItemPool::~ItemPool() {}
void ItemPool::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	this->drawItem(&painter);
}
void ItemPool::drawItem(QPainter *painter)
{
	for (Leaf *leaf : std::as_const(this->m_LeafList))
	{
		leaf->draw(painter);
	}
	for (Frog *frog : std::as_const(this->m_frogList))
	{
		frog->draw(painter);
	}
	this->textBoxFinal->draw(painter);
}
void ItemPool::initLeaf()
{
	this->frogPath.clear();
	for (Leaf *leaf : std::as_const(m_LeafList))
	{
		leaf->changeState(generateRandomString(), this->m_slideTime);
	}
	this->textBoxFinal->changeState(generateRandomString());
}
void ItemPool::createLeaf()
{
	int direction = -1;
	for (int j = 0; j < holeLength - 2; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			Leaf *leaf = new Leaf(this, "", this->m_slideTime, QPoint(i * 316, 400 - j * 100), direction);
			this->m_LeafList.append(leaf);
		}
		direction = -1 * direction;
		if (this->m_LeafList.size() >= 3 * (holeLength - 2))
		{
			break;
		}
	}

	for (Leaf *leaf : std::as_const(m_LeafList))
	{
		connect(leaf, &Leaf::finishSpell, this,
				[this, leaf]()
				{
					emit needSound(soundType::FROG_JUMP);
					this->changeFrogPos(1);
				});
		connect(leaf, &Leaf::frogDrop, this,
				[this, leaf]()
				{
					emit needSound(soundType::FROG_BACK);
					this->changeFrogPos(-1);
				});
		connect(leaf, &Leaf::timeOut, this, &ItemPool::cleanUp);
	}

	this->textBoxFinal = new TextBox(generateRandomString(), this);
	this->textBoxFinal->move(400, 50);
	connect(this->textBoxFinal, &TextBox::finishSpell, this,
			[this]()
			{
				this->changeFrogPos(1);
			});
}
void ItemPool::changeFrogPos(int direction)
{
	switch (direction)
	{
	case 1:
		this->nowPos++;						//往前一格
		if (this->nowPos == holeLength - 1) //holeLength-1是最后一个
		{
			this->m_frogList[finishFrogNum]->move(50 + finishFrogNum * 100, 100);
			this->m_frogList[finishFrogNum]->changeCondition(Frog::condition::FRONT1);
			this->nowPos = 0;
			this->finishFrogNum++;
			if (this->finishFrogNum == 5)
			{
				emit needOperator(operatorType::GAMEWIN_POP);
			}
			this->initLeaf();
		}
		else if (this->nowPos == 1)
		{
			this->frogPath.back()->getFrog(this->m_frogList[finishFrogNum]);
		}
		else
		{
			this->frogPath[nowPos - 2]->getFrog(nullptr);
			this->frogPath.back()->getFrog(this->m_frogList[finishFrogNum]);
		}
		break;
	case -1:
		this->nowPos--; //往后一格
		while (this->frogPath.size() > this->nowPos)
		{
			this->frogPath.back()->getFrog(nullptr);
			this->frogPath.back()->m_textBox->clear();
			this->frogPath.pop_back();
		}
		if (this->nowPos == 0) //0就是起点
		{
			this->m_frogList[finishFrogNum]->move(QPoint(300, 500));
		}
		else
		{
			this->frogPath.back()->getFrog(this->m_frogList[finishFrogNum]);
		}
		break;
	default:
		break;
	}
}

void ItemPool::hitWord(QString targetChar)
{
	if (this->nowPos < 3)
	{
		if (this->frogPath.size() <= this->nowPos)
		{
			for (int i = 0; i < 3; i++)
			{
				if (this->m_LeafList[this->nowPos * 3 + i]->m_textBox->receiveHit(targetChar))
				{
					this->frogPath.append(this->m_LeafList[this->nowPos * 3 + i]);
					return;
				}
			}
		}
		else
		{
			this->frogPath.back()->m_textBox->receiveHit(targetChar);
		}
	}
	else if (this->nowPos == 3)
	{
		this->textBoxFinal->receiveHit(targetChar);
	}
}

void ItemPool::initFrog()
{
	for (int i = 0; i < 5; i++)
	{
		this->m_frogList[i]->move(QPoint(300 + i * 100, 500));
		this->m_frogList[i]->changeCondition(Frog::condition::BACK1);
	}
}
void ItemPool::createFrog()
{
	for (int i = 0; i < 5; i++)
	{
		Frog *frog = new Frog(QPoint(300 + i * 100, 500), this);
		this->m_frogList.append(frog);
	}
}

void ItemPool::init()
{
	this->finishFrogNum = 0; //0,1,2,3,4,5当为5的时候游戏胜利
	this->nowPos = 0;		 //0,1,2,3,4//当为4的时候这个青蛙结束，finishFrogNum++,刷新单词再来
	this->initLeaf();
	this->initFrog();
}
void ItemPool::timer_pause()
{
	for (Leaf *leaf : std::as_const(this->m_LeafList))
	{
		leaf->m_timer->stop();
	}
}
void ItemPool::timer_start()
{
	for (Leaf *leaf : std::as_const(this->m_LeafList))
	{
		leaf->m_timer->start(5 * this->m_slideTime);
	}
}

void ItemPool::loadSetUp(int gameLevel, QString selectedDifficulty)
{
	this->m_selectedDifficulty = selectedDifficulty;
	this->m_gameLevel = gameLevel;
	this->m_slideTime = 4 + (9 - this->m_gameLevel);
}
void ItemPool::refresh() {}
void ItemPool::cleanUp(Leaf *leaf)
{
	if (this->frogPath.contains(leaf))
	{
	}
	else
	{
		leaf->m_textBox->clear();
	}
}
