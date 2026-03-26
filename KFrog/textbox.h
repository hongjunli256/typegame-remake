#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <QPainter>
#include <QWidget>
class TextBox : public QWidget
{
	Q_OBJECT
public:
	explicit TextBox(QString string, QWidget* parent = nullptr);
	QString m_string = "abcd";
	QString m_substring = "ab";
	// bool m_isCanHit = false;
	bool receiveHit(QString c);
	void changeState(QString string);

	static const QFont fontSmall;
	static const QPixmap& pixNormal();
	int currentIndex = 0;
	void draw(QPainter* painter);
	void clear();

private:
	void drawString(QPainter* painter);
signals:

	void finishSpell();
};

#endif // TEXTBOX_H
