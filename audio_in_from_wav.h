#ifndef AUDIO_IN_FROM_WAV_H
#define AUDIO_IN_FROM_WAV_H

#include <QObject>

class audio_in_from_wav
{
public:
    audio_in_from_wav();
    void load_selected_file(QString filename);
    QString filenameChosen;
    QString filename;
};

#endif // AUDIO_IN_FROM_WAV_H
