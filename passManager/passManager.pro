#-------------------------------------------------
#
# Project created by QtCreator 2019-05-28T18:15:24
#
#-------------------------------------------------
QT += xml
QT+=sql
QT += network
QT += widgets
QT+= core
QT       += core gui
CONFIG += c++17
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = passManager
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    authorization_dialog.cpp \
    add_dialog.cpp \
    passGenSettingsDialog.cpp \
    registerdialog.cpp \
    editdialog.cpp \
    getlinedialog.cpp \
    importtemplatesdialog.cpp \
    bmpreaderdialog.cpp \
    virtual_storage.cpp

HEADERS += \
        mainwindow.h \
    authorization_dialog.h \
    user.h \
    service.h \
    optional.h \
    account.h \
    add_dialog.h \
    passGenSettingsDialog.h \
    template.h \
    registerdialog.h \
    editdialog.h \
    getlinedialog.h \
    importtemplatesdialog.h \
    bmpreaderdialog.h \
    virtual_storage.h

FORMS += \
        mainwindow.ui \
    authorization_dialog.ui \
    add_dialog.ui \
    passGenSettingsDialog.ui \
    registerdialog.ui \
    editdialog.ui \
    getlinedialog.ui \
    importtemplatesdialog.ui \
    bmpreaderdialog.ui

DISTFILES +=

LIBS += -L /home/yaroslaw/projects/progbase3/passManager/lib/build-PassFunctions-Desktop-Debug -lpassfunctions
INCLUDEPATH +=  /home/yaroslaw/projects/progbase3/passManager/lib/PassFunctions

INCLUDEPATH += /home/yaroslaw/projects/progbase3/rpclib/include
LIBS += -L/home/yaroslaw/projects/progbase3/rpclib/ -lrpc

#INCLUDEPATH += /home/yaroslaw/projects/progbase3/rpclib/include
#LIBS += -L/home/yaroslaw/projects/progbase3/rpclib/ -lrpc

#PRE_TARGETDEPS += lib/build-PassFunctions-Desktop-Debug/passfunctions.a
