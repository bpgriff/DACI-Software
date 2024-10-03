#include "custommeaswin.h"
#include "ui_custommeaswin.h"

CustomMeasWin::CustomMeasWin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CustomMeasWin)
{
    ui->setupUi(this);
}

CustomMeasWin::~CustomMeasWin()
{
    delete ui;
}
