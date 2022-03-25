QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

RC_FILE = win_icon.rc

SOURCES += \
    animation.cpp \
    gate_in_manager.cpp \
    infrastructure.cpp \
    main.cpp \
    mainwindow.cpp \
    train.cpp \
    train_maker.cpp

HEADERS += \
    animation.h \
    gate_in_manager.h \
    infrastructure.h \
    mainwindow.h \
    train.h \
    train_maker.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    IconRC.qrc \
    Images.qrc
