/********************************************************************************
** Form generated from reading UI file 'custommeaswin.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMMEASWIN_H
#define UI_CUSTOMMEASWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_CustomMeasWin
{
public:

    void setupUi(QDialog *CustomMeasWin)
    {
        if (CustomMeasWin->objectName().isEmpty())
            CustomMeasWin->setObjectName("CustomMeasWin");
        CustomMeasWin->resize(400, 300);

        retranslateUi(CustomMeasWin);

        QMetaObject::connectSlotsByName(CustomMeasWin);
    } // setupUi

    void retranslateUi(QDialog *CustomMeasWin)
    {
        CustomMeasWin->setWindowTitle(QCoreApplication::translate("CustomMeasWin", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CustomMeasWin: public Ui_CustomMeasWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMMEASWIN_H
