#include "pole.h"
#include "ui_pole.h"

pole::pole(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pole)
{
    ui->setupUi(this);
}

pole::~pole()
{
    delete ui;
}
