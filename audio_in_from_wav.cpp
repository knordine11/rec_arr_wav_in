#include "audio_in_from_wav.h"
#include <QFile>
#include <QTimer>
#include <QDebug>
#include <iostream>
#include <QUrl>


using namespace std;
int frame_no = 100;
QByteArray rec_arr;

audio_in_from_wav::audio_in_from_wav()
{    

}

void audio_in_from_wav::load_selected_file(QString filename)
{
    //filename = "v43.wav";
    filenameChosen = "C:/QtWorking/rec_arr_wav_in/v_sounds/" + filename;
    QFile in(filenameChosen);
    if (!in.open(QIODevice::ReadOnly))
    {
        cout << "not opened" << endl;
    }
    rec_arr = in.readAll();
    qDebug() << rec_arr.size();
    // shows the header
    QByteArray temp = rec_arr.slice(44 + frame_no * 1024, (frame_no * 1024) + 1024);
    for (int i=0; i < 1024; i += 2)
    {
        int t = abs(temp[i]) + temp[i+1] * 255;
        float t1 = (float) t/1000;
        qDebug() << i << "->" << t1;
    }
    cout << "data length = " << rec_arr.size() << endl;
    qDebug() << "filename..." <<  filename;
    cout << "exiting..." << endl;
}
