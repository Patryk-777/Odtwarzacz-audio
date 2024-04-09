#include "odtwarzacz.h"
#include "ui_odtwarzacz.h"
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>

Odtwarzacz::Odtwarzacz(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Odtwarzacz)
{
    ui->setupUi(this);
    p=new QMediaPlayer;

    connect(p, &QMediaPlayer::positionChanged, this, &Odtwarzacz::on_positionChanged);
    connect(p, &QMediaPlayer::durationChanged, this, &Odtwarzacz::on_durationChanged);


    audioOutput = new QAudioOutput;
    p->setAudioOutput(audioOutput);
//    connect(p, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    audioOutput->setVolume(1);
    ui->glosnosc->setValue(100);

}

Odtwarzacz::~Odtwarzacz()
{

    delete ui;
    delete p;

}

void Odtwarzacz::otworz(QString nazwa)
{


     p->setSource(QUrl::fromLocalFile(nazwa));
     p->play();
     ui->play_button->setText("Pause");

}




void Odtwarzacz::on_play_button_clicked()
{
    ;
    if(ui->play_button->text()=="Play")
    {
        p->play();
        ui->play_button->setText("Pause");

    }
   else
   {
       p->pause();
       ui->play_button->setText("Play");
   }
}


void Odtwarzacz::on_glosnosc_valueChanged(int value)
{
    audioOutput->setVolume(0.01*value);
}





void Odtwarzacz::on_mute_clicked()
{
    if(ui->mute->text()=="Mute")
    {
        audioOutput->setMuted(1);
        ui->mute->setText("Unmute");
    }
    else
    {
        audioOutput->setMuted(0);
        ui->mute->setText("Mute");
    }

}





void Odtwarzacz::on_sliderProgress_sliderMoved(int position)
{
    p->setPosition(position);
}

void Odtwarzacz::on_positionChanged(qint64 position)
{
    ui->sliderProgress->setValue(position);
}

void Odtwarzacz::on_durationChanged(qint64 position)
{
    ui->sliderProgress->setMaximum(position);
}


void Odtwarzacz::on_przewinTyl_clicked()
{
    qint64 czas_trwania=p->duration();
    ui->sliderProgress->setSliderPosition(ui->sliderProgress->sliderPosition()-czas_trwania/20);
    p->setPosition(ui->sliderProgress->sliderPosition());


}


void Odtwarzacz::on_przewinPrzod_clicked()
{
    qint64 czas_trwania=p->duration();
    ui->sliderProgress->setSliderPosition(ui->sliderProgress->sliderPosition()+czas_trwania/20);
    p->setPosition(ui->sliderProgress->sliderPosition());
}


void Odtwarzacz::on_do_przodu_clicked()
{
    emit nastepny();
}




void Odtwarzacz::on_cofnij_clicked()
{
    ui->sliderProgress->setSliderPosition(0);
    p->setPosition(ui->sliderProgress->sliderPosition());
}

