#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QString filename = "";
    QMediaPlayer *m_player = nullptr;
    QAudioOutput *m_audioOutput = nullptr;

private slots:
    void on_btnGetWav_clicked();
    void soundNew();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
