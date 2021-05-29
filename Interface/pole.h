#ifndef POLE_H
#define POLE_H

#include <QWidget>

namespace Ui {
class pole;
}

class pole : public QWidget
{
    Q_OBJECT

public:
    explicit pole(QWidget *parent = nullptr);
    ~pole();

private:
    Ui::pole *ui;
};

#endif // POLE_H
