#include "widget.h"
#include "ui_widget.h"
#include "audio_in_from_wav.h"
#include <QMediaPlayer>
#include <QUrl>
#include <QAudioDevice>
#include <QAudioOutput>
#include <QMediaDevices>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    // ui->cboWaveFile->addItem("v57.wav");
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
    target.load_selected_file(filename);
    m_player->setSource(QUrl::fromLocalFile("C:/QtWorking/rec_arr_wav_in/v_sounds/" + filename));
    m_player->play();
}

void Widget::soundNew()
{
    filename = ui->cboWaveFile->currentText();
    qDebug () << filename;
    audio_in_from_wav target;
    target.load_selected_file(filename);
    m_player->setSource(QUrl::fromLocalFile("C:/QtWorking/rec_arr_wav_in/v_sounds/" + filename));
    m_player->play();
}
