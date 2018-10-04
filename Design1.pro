#-------------------------------------------------
#
# Project created by QtCreator 2018-09-20T15:23:04
#
#-------------------------------------------------

QT       += core gui widgets sql

TARGET = Design1
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    gencsr.cpp \
    import.cpp \
    export.cpp \
    tf_cert_mngr/tf_cert_mngr/tf_cert_mngr/Certificate.cpp \
    tf_cert_mngr/tf_cert_mngr/tf_cert_mngr/tf_cert_util.cpp \
    tf_cert_mngr/tf_cert_mngr/tf_cert_mngr/sqlite3.c \
    dialog.cpp

HEADERS += \
        mainwindow.h \
    gencsr.h \
    gencsr.h \
    import.h \
    export.h \
    tf_cert_mngr/tf_cert_mngr/tf_cert_mngr/Certificate.h \
    tf_cert_mngr/tf_cert_mngr/tf_cert_mngr/sqlite3.h \
    tf_cert_mngr/tf_cert_mngr/tf_cert_mngr/sqlite3ext.h \
    tf_cert_mngr/tf_cert_mngr/tf_cert_mngr/tf_cert_util.h \
    dialog.h


FORMS += \
        mainwindow.ui \
    gencsr.ui \
    import.ui \
    export.ui \
    dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += C:\Users\Stacy\Documents\qt\Design1\tf_cert_mngr\tf_cert_mngr\tf_cert_mngr

LIBS += C:\Users\Stacy\Documents\qt\Design1\tf_cert_mngr\tf_cert_mngr\tf_cert_mngr\openssl-1.1.0a-x86_32\lib\libcrypto.lib
LIBS += C:\Users\Stacy\Documents\qt\Design1\tf_cert_mngr\tf_cert_mngr\tf_cert_mngr\openssl-1.1.0a-x86_32\lib\libssl.lib



DISTFILES += \
    countries.txt



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/tf_cert_mngr/tf_cert_mngr/tf_cert_mngr/openssl-1.1.0a-x86_32/lib/ -llibcrypto
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/tf_cert_mngr/tf_cert_mngr/tf_cert_mngr/openssl-1.1.0a-x86_32/lib/ -llibcryptod

INCLUDEPATH += $$PWD/tf_cert_mngr/tf_cert_mngr/tf_cert_mngr/openssl-1.1.0a-x86_32/include
DEPENDPATH += $$PWD/tf_cert_mngr/tf_cert_mngr/tf_cert_mngr/openssl-1.1.0a-x86_32/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/tf_cert_mngr/tf_cert_mngr/tf_cert_mngr/openssl-1.1.0a-x86_32/lib/ -llibssl
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/tf_cert_mngr/tf_cert_mngr/tf_cert_mngr/openssl-1.1.0a-x86_32/lib/ -llibssld

INCLUDEPATH += $$PWD/tf_cert_mngr/tf_cert_mngr/tf_cert_mngr/openssl-1.1.0a-x86_32/include
DEPENDPATH += $$PWD/tf_cert_mngr/tf_cert_mngr/tf_cert_mngr/openssl-1.1.0a-x86_32/include
