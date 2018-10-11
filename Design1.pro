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
    dialog.cpp \
    tf_cert_mngr/src/tf_cert_util.cpp \
    tf_cert_mngr/src/TFCertificate.cpp \
    tf_cert_mngr/src/sqlite3.c \
    view.cpp

HEADERS += \
        mainwindow.h \
    gencsr.h \
    gencsr.h \
    import.h \
    export.h \
    dialog.h \
    tf_cert_mngr/include/sqlite3.h \
    tf_cert_mngr/include/sqlite3ext.h \
    tf_cert_mngr/include/tf_cert_util.h \
    tf_cert_mngr/include/TFCertificate.h \
    view.h


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

#INCLUDEPATH += C:\Users\Stacy\Documents\qt\Design1\tf_cert_mngr
INCLUDEPATH += C:\Users\Stacy\Documents\qt\Design1\tf_cert_mngr\include
INCLUDEPATH += C:\Users\Stacy\Documents\qt\Design1\tf_cert_mngr\src
INCLUDEPATH += C:\Users\Stacy\Documents\qt\Design1\tf_cert_mngr\openssl\include

LIBS += C:\Users\Stacy\Documents\qt\Design1\tf_cert_mngr\openssl\lib\libcrypto.lib
LIBS += C:\Users\Stacy\Documents\qt\Design1\tf_cert_mngr\openssl\lib\libssl.lib



DISTFILES += \
    countries.txt \


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/tf_cert_mngr/openssl/lib/ -llibcrypto
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/tf_cert_mngr/openssl/lib/ -llibcryptod

INCLUDEPATH += $$PWD/tf_cert_mngr/openssl/include
DEPENDPATH += $$PWD/tf_cert_mngr/openssl/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/tf_cert_mngr/openssl/lib/ -llibssl
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/tf_cert_mngr/openssl/lib/ -llibssld

INCLUDEPATH += $$PWD/tf_cert_mngr/openssl/include
DEPENDPATH += $$PWD/tf_cert_mngr/openssl/include
