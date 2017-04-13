#-------------------------------------------------
#
# Project created by QtCreator 2017-04-04T20:17:59
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pamphlet
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/dbmanager.cpp \
    src/customer.cpp \
    src/address.cpp \
    src/dialoghelp.cpp \
    src/adminlogin.cpp

HEADERS  += src/mainwindow.h \
    src/dbmanager.h \
    src/customer.h \
    src/address.h \
    src/dialoghelp.h \
    src/adminlogin.h

FORMS    += src/mainwindow.ui \
    src/dialoghelp.ui \
    src/adminlogin.ui

DISTFILES += \
    pamphletDB.db

RESOURCES += \
    res.qrc
