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
#include <unistd.h>


using namespace std;

QByteArray qb_rec_arr;

audio_in_from_wav::audio_in_from_wav()
{

}

void audio_in_from_wav::load_selected_file(QString filename, int next_frame)
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
    int qb_size = qb_rec_arr.size();
    // strip the header convert to float
    QByteArray temp = qb_rec_arr.slice(44, qb_size - 44);
    for (int i=0; i < qb_size - 44; i += 2)
    {
        int t = abs(temp[i]) + temp[i+1] * 255;
        float t1 = (float) t/1000;
        rec_arr[i] = t1;
        rec_arr_cnt++;
        //qDebug() << i << "->" << t1;
    }
    qDebug() << rec_arr_cnt;
    frame_total = rec_arr_cnt/frame_width -1;    

    FftStuff test;    
    qDebug() << "-->" << next_frame;
    test.DoIt(next_frame*frame_width,next_frame*frame_width+frame_width);

    cout << "data length on input = " << qb_rec_arr.size() << endl;
    cout << "data length on output = " << rec_arr_cnt << endl;
    qDebug() << frame_total;
    qDebug() << "filename..." <<  filename;
    cout << "exiting..." << endl;
}

void audio_in_from_wav::process_next_frame(int frame_no)
{
    FftStuff test;
    qDebug() << "-->" << frame_no;
    test.DoIt(frame_no*frame_width,frame_no*frame_width+frame_width);
}
