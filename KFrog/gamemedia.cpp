#include "gamemedia.h"

GameMedia::GameMedia(QObject *parent)
	: QObject{parent}
{
	initMediaPlayer();

	initSoundEffectMap();
}
void GameMedia::initMediaPlayer()
{
	this->m_mediaPlayerBG = new QMediaPlayer(this);
	this->m_audioOutput = new QAudioOutput(this);
	this->m_audioOutput->setVolume(50);
	this->m_mediaPlayerBG->setAudioOutput(this->m_audioOutput);
	this->m_mediaPlayerBG->setLoops(QMediaPlayer::Infinite);
}
void GameMedia::initSoundEffectMap()
{
	this->initSoundEffect(soundType::BUTTONCLICK, "qrc:/soundWav/WAVE/ANIBTN_CLICK.wav", 30);
	this->initSoundEffect(soundType::BUTTONENTER, "qrc:/soundWav/WAVE/ANIBTN_ENTER.wav", 30);

	this->initSoundEffect(soundType::Type, "qrc:/soundWav/WAVE/TYPE.wav", 5);
	this->initSoundEffect(soundType::SLIDER, "qrc:/soundWav/WAVE/GLIDE.wav", 30);

	this->initSoundEffect(soundType::FROG_BACK, "qrc:/soundWav/WAVE/FROG_BACK.wav", 30);
	this->initSoundEffect(soundType::FROG_JUMP, "qrc:/soundWav/WAVE/FROG_JUMP.wav", 30);
}
void GameMedia::initSoundEffect(soundType type, const QString &resourcePath, int volumn)
{
	QSoundEffect *soundEffect = new QSoundEffect(this);

	soundEffect->setSource(QUrl(resourcePath));

	soundEffect->setVolume(volumn);

	soundEffect->setLoopCount(1);

	this->m_mapSoundEffect.insert(type, soundEffect);
}
void GameMedia::playSound(soundType type)
{
	QSoundEffect *soundEffect = this->m_mapSoundEffect.value(type);
	soundEffect->play();
}
void GameMedia::playBGM(BGMtype type)
{
	QString resourcePath = "qrc:/soundWav/WAVE/FROG_BG.wav";
	switch (type)
	{
	case BGMtype::NORMAL:
		break;
	default:
		break;
	}
	this->m_mediaPlayerBG->pause();
	if (this->m_mediaPlayerBG->source().toString() != resourcePath)
	{
		this->m_mediaPlayerBG->setSource(QUrl(resourcePath));
	}
	this->m_mediaPlayerBG->play();
}
void GameMedia::pauseBGM()
{
	this->m_mediaPlayerBG->pause();
}
