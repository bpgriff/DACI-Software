#ifndef CUSTOMMEASWIN_H
#define CUSTOMMEASWIN_H

#include <QDialog>

namespace Ui {
class CustomMeasWin;
}

class CustomMeasWin : public QDialog
{
    Q_OBJECT

public:
    explicit CustomMeasWin(QWidget *parent = nullptr);
    ~CustomMeasWin();

private:
    Ui::CustomMeasWin *ui;
};

#endif // CUSTOMMEASWIN_H
