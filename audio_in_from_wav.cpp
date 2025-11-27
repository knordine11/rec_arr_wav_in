#include "audio_in_from_wav.h"
#include "fftstuff.h"
#include <QFile>
#include <QTimer>
#include <QDebug>
#include <iostream>
#include <QUrl>
#include <QMediaPlayer>
#include <QAudioDevice>
#include <QAudioOutput>
#include <QMediaDevices>


using namespace std;
int frame_no = 100;
QByteArray qb_rec_arr;

audio_in_from_wav::audio_in_from_wav()
{

}

void audio_in_from_wav::load_selected_file(QString filename)
{
    filenameChosen = "C:/QtWorking/rec_arr_wav_in/v_sounds/" + filename;

    // Create a media player object
    m_player = new QMediaPlayer();
    m_audioOutput = new QAudioOutput();
    m_player->setAudioOutput(m_audioOutput);
    m_player->setSource(filenameChosen);

    QFile in(filenameChosen);
    if (!in.open(QIODevice::ReadOnly))
    {
        cout << "not opened" << endl;
    }
    qb_rec_arr = in.readAll();
    qDebug() << qb_rec_arr.size();
    // shows the header
    QByteArray temp = qb_rec_arr.slice(44 + frame_no * 1024, (frame_no * 1024) + 1024);
    for (int i=0; i < 1024; i += 2)
    {
        int t = abs(temp[i]) + temp[i+1] * 255;
        float t1 = (float) t/1000;
        rec_arr[i] = t1;
        rec_arr_cnt++;
        qDebug() << i << "->" << t1;
    }
    for (int i = 0; i < 512; i += 2)
    {
        qDebug() << rec_arr[i];
    }
    qDebug() << rec_arr_cnt;
    FftStuff test;
    test.DoIt(80,100);

    cout << "data length = " << qb_rec_arr.size() << endl;
    qDebug() << "filename..." <<  filename;
    cout << "exiting..." << endl;
}
