QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    checkboxwordwrap.cpp \
    clickablelabel.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot-source/qcustomplot.cpp \
    savedata.cpp \
    testinput.cpp

HEADERS += \
    checkboxwordwrap.h \
    clickablelabel.h \
    mainwindow.h \
    qcustomplot-source/qcustomplot.h \
    savedata.h \
    testinput.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target