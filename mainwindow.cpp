#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "odtwarzacz.h"
#include <QFileDialog>
#include <QTextStream>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    o=new Odtwarzacz;

//    connect(o, SIGNAL(nastepny()), this, SLOT(nastepny()));
        connect(o, &Odtwarzacz::nastepny, this, &MainWindow::nastepny);
    QFile fIn(QDir::homePath()+"/Playlista.txt");
    if (fIn.open(QFile::ReadOnly | QFile::Text)) {
      QTextStream sIn(&fIn);
      while (!sIn.atEnd())
      {
          QString nazwaPliku=sIn.readLine();
        QString nazwaUtworu= nazwaPliku.split("/").last();
        lista_utworow += nazwaPliku;
        ui->playlista->addItem(nazwaUtworu);
    }
    }


}

MainWindow::~MainWindow()
{
    delete ui;
    delete o;

    QFile fOut(QDir::homePath()+"/Playlista.txt");
     if (fOut.open(QFile::WriteOnly | QFile::Text)) {

       QTextStream s(&fOut);
       for (int i = 0; i < lista_utworow.size(); ++i)
         s << lista_utworow.at(i) << '\n';
     }
     fOut.close();

}

void MainWindow::on_actionOdtwarzacz_triggered()
{
   o->show();
}


void MainWindow::on_actionWybierz_plik_triggered()
{
    nazwaPliku=QFileDialog::getOpenFileName(this,"Wybierz plik",QDir::homePath());
    o->show();
    o->otworz(nazwaPliku);




}



void MainWindow::on_dodaj_utwor_clicked()
{
    QString nazwaPliku=QFileDialog::getOpenFileName(this,"Wybierz plik",QDir::homePath());
    lista_utworow<<nazwaPliku;
    QString nazwaUtworu= nazwaPliku.split("/").last();
    ui->playlista->addItem(nazwaUtworu);

}


void MainWindow::on_playlista_itemDoubleClicked(QListWidgetItem *item)
{
    int numer=ui->playlista->currentRow();
    QString nazwaUtworu;
    nazwaUtworu=lista_utworow.at(numer);
    o->show();
    o->otworz(nazwaUtworu);

}




void MainWindow::on_usun_clicked()
{
    if(ui->playlista->count()==1)
    {   ui->playlista->clear();
        lista_utworow.clear();
    }
    else if(ui->playlista->count()==0)
    {

    }

    else if((ui->playlista->currentRow()+1)==ui->playlista->count())
    {
        ui->playlista->takeItem(ui->playlista->currentRow());
        lista_utworow.removeLast();
        lista_utworow.squeeze();
    }
    else
    {
        ui->playlista->takeItem(ui->playlista->currentRow());
        lista_utworow.removeAt(ui->playlista->currentRow());
        lista_utworow.squeeze();
    }
}


void MainWindow::on_wyczysc_clicked()
{
    ui->playlista->clear();
    lista_utworow.clear();
}


void MainWindow::on_actionOdtw_rz_plik_z_playlisty_triggered()
{
    int numer=ui->playlista->currentRow();
    QString nazwaUtworu;
    nazwaUtworu=lista_utworow.at(numer);
    o->show();
    o->otworz(nazwaUtworu);

}

void MainWindow::nastepny()
{
    int numer;
    if((ui->playlista->currentRow()+1)==ui->playlista->count())
    {
        ui->playlista->setCurrentRow(0);
        numer=ui->playlista->currentRow();
    }
    else
    {
        numer=ui->playlista->currentRow()+1;
        ui->playlista->setCurrentRow(ui->playlista->currentRow()+1);
    }
    QString nazwaUtworu;
    nazwaUtworu=lista_utworow.at(numer);
    o->show();
    o->otworz(nazwaUtworu);
}

