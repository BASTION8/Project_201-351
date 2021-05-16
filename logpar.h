#ifndef LOGPAR_H
#define LOGPAR_H

#include <QDialog>

namespace Ui {
class LogPar;
}

class LogPar : public QDialog
{
    Q_OBJECT

public:
    explicit LogPar(QWidget *parent = nullptr);
    ~LogPar();

private:
    Ui::LogPar *ui;
};

#endif // LOGPAR_H
