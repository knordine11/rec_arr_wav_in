#include "audio_in_from_wav.h"
#include <QFile>
#include <QTimer>
#include <QDebug>
#include <iostream>

using namespace std;
int frame_no = 100;

audio_in_from_wav::audio_in_from_wav()
{
    QByteArray rec_arr;
    QFile in("C:/QtWorking/fileTest2/v43.wav");
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
    cout << "exiting..." << endl;
}
