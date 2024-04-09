#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "odtwarzacz.h"
#include <QString>
#include <QStringList>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    friend void on_do_przodu_clicked();

private slots:

    void on_actionOdtwarzacz_triggered();

    void on_actionWybierz_plik_triggered();

    void on_dodaj_utwor_clicked();




    void on_playlista_itemDoubleClicked(QListWidgetItem *item);



    void on_usun_clicked();

    void on_wyczysc_clicked();

    void on_actionOdtw_rz_plik_z_playlisty_triggered();
    void nastepny();

private:
    Ui::MainWindow *ui;
    Odtwarzacz *o;
    QString nazwaPliku;
    QStringList lista_utworow;

};
#endif // MAINWINDOW_H
