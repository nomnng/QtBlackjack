#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QObject>
#include <QSoundEffect>

class AudioManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AudioManager)

public:
    static AudioManager& instance();

    static void playCardSound();
    static void playButtonSound();
    static void startBgMusic();
    static void setVolume(float volume);

signals:

private:
    AudioManager(QObject* parent = nullptr);
    QSoundEffect* createSoundEffect(QString filename);

    static constexpr char CARD_SOUND_FILE[] = ":/assets/audio/card.wav";
    static constexpr char BUTTON_SOUND_FILE[] = ":/assets/audio/button.wav";
    static constexpr char BACKGROUND_MUSIC_FILE[] = ":/assets/audio/bg.wav";

    QSoundEffect* cardSound;
    QSoundEffect* buttonSound;
    QSoundEffect* bgMusic;

    QList<QSoundEffect*> sounds;
};

#endif // AUDIOMANAGER_H
