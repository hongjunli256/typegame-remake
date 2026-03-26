#ifndef WIDGETSETUP_H
#define WIDGETSETUP_H

#include <QComboBox>
#include <QJsonObject>
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
    void paintEvent(QPaintEvent *event)override;

private:
	QSlider *m_sliderGameLevel = nullptr;

	QLabel *m_labelGameLevel = nullptr;

	QLabel *m_labelGameLevelValue = nullptr;

	ImageButton *m_buttonOK = nullptr;
	ImageButton *m_buttonCANCEL = nullptr;
	ImageButton *m_buttonDEFAULT = nullptr;

	QJsonObject loadWordDictionary(const QString &filePath);
	QComboBox *m_difficultyCombo;
	QJsonObject m_wordDictionary;
	QString m_selectedDifficulty = "easy";

	static const QPixmap &pixSetUp();
	void initLabel();
	void initButton();
	void initSlider();

public slots:
    void m_buttonYES_clicked();
    void m_buttonNO_clicked();
    void m_buttonDEFAULT_clicked();
	void loadSetUp(int gameLevel, QString selectedDifficulty);
signals:
	void changeSetUp(int gameLevel, QString selectedDifficulty);
	void allhide();
};

#endif // WIDGETSETUP_H
