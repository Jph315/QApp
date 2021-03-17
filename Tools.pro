#-------------------------------------------------
#
# Project created by QtCreator 2021-02-27T16:33:24
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tools
TEMPLATE = app
DESTDIR = ./tools

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        data/net/inetdata.cpp \
        main.cpp \
        network/tcpclient.cpp \
        network/tcpsocket.cpp \
        ui/login/loginui.cpp \
        ui/login/registerui.cpp \
        ui/login/welcomeui.cpp \
        ui/mainui.cpp \
        ui/selfwidget/titlebar.cpp \
        ui/tool/toolui.cpp

HEADERS += \
        data/net/inetdata.h \
        network/tcpclient.h \
        network/tcpsocket.h \
        ui/login/loginui.h \
        ui/login/registerui.h \
        ui/login/welcomeui.h \
        ui/mainui.h \
        ui/selfwidget/titlebar.h \
        ui/tool/toolui.h

FORMS += \
    ui/login/loginui.ui \
    ui/login/registerui.ui \
    ui/login/welcomeui.ui \
    ui/mainui.ui \
    ui/tool/toolui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
