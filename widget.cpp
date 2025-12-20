#include "widget.h"
#include "ui_widget.h"
#include "audio_in_from_wav.h"
#include <QMediaPlayer>
#include <QUrl>
#include <QAudioDevice>
#include <QAudioOutput>
#include <QMediaDevices>

int Frame_no = 0;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->cboWaveFile->addItem("v43.wav");
    ui->cboWaveFile->addItem("v45.wav");
    ui->cboWaveFile->addItem("v47.wav");
    ui->cboWaveFile->addItem("v48.wav");
    ui->cboWaveFile->addItem("v50.wav");
    ui->cboWaveFile->addItem("v52.wav");
    ui->cboWaveFile->addItem("v54.wav");
    ui->cboWaveFile->addItem("v55.wav");
    qDebug() << ui->cboWaveFile->currentText();
    filename = ui->cboWaveFile->currentText();
    // Create a media player object
    m_player = new QMediaPlayer(this);
    m_audioOutput = new QAudioOutput(this);
    m_player->setAudioOutput(m_audioOutput);
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
    rec_arr_cnt = 0;
    Frame_no = 0;
    frame_total = 0;
    target.load_selected_file(filename, Frame_no);
    QString frame_str = QString::number(Frame_no);
    ui->txtFrame->setText(frame_str);
    QString frame_total_str = QString::number(frame_total);
    ui->txtFrameTotal->setText(frame_total_str);
    m_player->setSource(QUrl::fromLocalFile("C:/QtWorking/rec_arr_wav_in/v_sounds/" + filename));
    m_player->play();
}

void Widget::soundNew()
{
    filename = ui->cboWaveFile->currentText();
    qDebug () << filename;
    audio_in_from_wav target;
    rec_arr_cnt = 0;
    Frame_no = 0;
    frame_total = 0;
    target.load_selected_file(filename, Frame_no);
    QString frame_str = QString::number(Frame_no);
    ui->txtFrame->setText(frame_str);
    QString frame_total_str = QString::number(frame_total);
    ui->txtFrameTotal->setText(frame_total_str);

    m_player->setSource(QUrl::fromLocalFile("C:/QtWorking/rec_arr_wav_in/v_sounds/" + filename));
    m_player->play();    
}

void Widget::on_btnNextFrame_clicked()
{
    audio_in_from_wav target;
    Frame_no++;
    QString frame_cnt = QString::number(Frame_no);
    ui->txtFrame->setText(frame_cnt);
    target.load_selected_file(filename, Frame_no);
}
