QT       += core gui
QT       += network
QT       += sql

LIBS += -lWs2_32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    afectiune.cpp \
    clientconnection.cpp \
    cutils.cpp \
    dashboard.cpp \
    disponibilitate_programari.cpp \
    doctor.cpp \
    exception.cpp \
    irequest.cpp \
    iuser.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    pacient.cpp \
    register.cpp \
    requestlogin.cpp \
    requestregister.cpp

HEADERS += \
    afectiune.h \
    clientconnection.h \
    cutils.h \
    dashboard.h \
    disponibilitate_programari.h \
    doctor.h \
    exception.h \
    irequest.h \
    iuser.h \
    login.h \
    mainwindow.h \
    pacient.h \
    register.h \
    requestlogin.h \
    requestregister.h

FORMS += \
    dashboard.ui \
    login.ui \
    mainwindow.ui \
    register.ui

TRANSLATIONS += \
    Clinica_en_GB.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
