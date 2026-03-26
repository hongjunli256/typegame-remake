#ifndef GAMEMEDIA_H
#define GAMEMEDIA_H

#include <QAudioOutput>
#include <QMap>
#include <QMediaPlayer>
#include <QObject>
#include <QSoundEffect>
#include "PopupWidget/public_enum.h"
class GameMedia : public QObject
{
	Q_OBJECT
public:
	explicit GameMedia(QObject *parent = nullptr);

private:
	void initMediaPlayer();
	void initSoundEffect(soundType type, const QString &resourcePath, int volumn);
	void initSoundEffectMap();

public slots:
	void playSound(soundType type);
	void playBGM(BGMtype type);
	void pauseBGM();

private:
	QMediaPlayer *m_mediaPlayerBG;
	QAudioOutput *m_audioOutput;
	QMap<soundType, QSoundEffect *> m_mapSoundEffect;

signals:
};

#endif // GAMEMEDIA_H
