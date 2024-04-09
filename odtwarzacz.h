#ifndef ODTWARZACZ_H
#define ODTWARZACZ_H

#include <QDialog>
#include <QtMultimedia/QMediaPlayer>

namespace Ui {
class Odtwarzacz;
}

class Odtwarzacz : public QDialog
{
    Q_OBJECT


public:
    explicit Odtwarzacz(QWidget *parent = nullptr);
    ~Odtwarzacz();
    void otworz(QString nazwa);
public slots:
    void on_do_przodu_clicked();

private slots:


    void on_play_button_clicked();

    void on_glosnosc_valueChanged(int value);
    void on_mute_clicked();

    void on_sliderProgress_sliderMoved(int position);
    void on_positionChanged(qint64 position);
    void on_durationChanged(qint64 position);


    void on_przewinTyl_clicked();

    void on_przewinPrzod_clicked();

    void on_cofnij_clicked();

signals:
    void nastepny();
//    void koniec();






private:
    Ui::Odtwarzacz *ui;
    QMediaPlayer*p;
    QAudioOutput *audioOutput;
};

#endif // ODTWARZACZ_H
