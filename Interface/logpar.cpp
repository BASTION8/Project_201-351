#include "logpar.h"
#include "ui_logpar.h"

LogPar::LogPar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogPar)
{
    ui->setupUi(this);
}

LogPar::~LogPar()
{
    delete ui;
}
