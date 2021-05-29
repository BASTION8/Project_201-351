#include "registr.h"
#include "ui_registr.h"

registr::registr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registr)
{
    ui->setupUi(this);
}

registr::~registr()
{
    delete ui;
}
