#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "logpar.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auth = new LogPar();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_butenter_clicked()
{
      auth->show();
}
