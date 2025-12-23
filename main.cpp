#include "widget.h"

#include <QApplication>

// double rec_arr[1000000];
// int rec_arr_cnt = 0;
int arr_size = 0;
int frame_total = 0;
int frame_width = 2048;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
