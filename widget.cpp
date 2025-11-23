#include "widget.h"
#include "ui_widget.h"
#include "audio_in_from_wav.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnGetWav_clicked()
{
    audio_in_from_wav target;

}

