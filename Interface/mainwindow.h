#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logpar.h"
#include "registr.h"
#include "pole.h"




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_butenter_clicked();


    void on_butreg_clicked();

    void on_butguest_clicked();

private:
    Ui::MainWindow *ui;

    LogPar *auth;
    registr *regstr;
    pole *igra;

};
#endif // MAINWINDOW_H
