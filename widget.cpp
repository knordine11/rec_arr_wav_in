#include "widget.h"
#include "ui_widget.h"
#include "audio_in_from_wav.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug() << ui->cboWaveFile->currentText();
    filename = ui->cboWaveFile->currentText();
    QObject::connect(ui->cboWaveFile, &QComboBox::currentTextChanged, this, &Widget::soundNew);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnGetWav_clicked()
{
    filename = ui->cboWaveFile->currentText();
    audio_in_from_wav target;
    target.load_selected_file(filename);
}

void Widget::soundNew()
{
    filename = ui->cboWaveFile->currentText();
    qDebug () << filename;
    audio_in_from_wav target;
    target.load_selected_file(filename);
}
