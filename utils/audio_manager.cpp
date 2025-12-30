#include "audio_manager.h"

#include <QDebug>

AudioManager::AudioManager(QObject *parent)
    : QObject{parent}
{
    cardSound = createSoundEffect(CARD_SOUND_FILE);
    buttonSound = createSoundEffect(BUTTON_SOUND_FILE);
    bgMusic = createSoundEffect(BACKGROUND_MUSIC_FILE);
    bgMusic->setLoopCount(QSoundEffect::Infinite);
}

QSoundEffect* AudioManager::createSoundEffect(QString filepath)
{
    QSoundEffect* effect = new QSoundEffect(this);
    effect->setSource(QUrl::fromLocalFile(filepath));
    sounds.append(effect);
    return effect;
}

AudioManager& AudioManager::instance()
{
    static AudioManager _instance;
    return _instance;
}

void AudioManager::playCardSound()
{
    instance().cardSound->play();
}

void AudioManager::playButtonSound()
{
    instance().buttonSound->play();
}

void AudioManager::startBgMusic()
{
    instance().bgMusic->play();
}

void AudioManager::setVolume(float volume)
{
    QList<QSoundEffect*>& sounds = instance().sounds;
    for (QSoundEffect* sound: sounds) {
        sound->setVolume(volume);
    }
}
