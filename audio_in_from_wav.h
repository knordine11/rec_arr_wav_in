#ifndef AUDIO_IN_FROM_WAV_H
#define AUDIO_IN_FROM_WAV_H

#include <QIODevice>
#include <QMediaPlayer>
#include <QAudioDevice>
#include <QAudioOutput>
#include <QMediaDevices>

extern double rec_arr[];
extern int rec_arr_cnt;
extern int arr_size;

class audio_in_from_wav
{
public:
    audio_in_from_wav();
    void load_selected_file(QString filename);
    QString filenameChosen;
    QString filename;
    QMediaPlayer *m_player = nullptr;
    QAudioOutput *m_audioOutput = nullptr;
};

#endif // AUDIO_IN_FROM_WAV_H
