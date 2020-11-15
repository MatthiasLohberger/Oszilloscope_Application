QT += core gui
QT += widgets printsupport
QT += bluetooth
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bluetooth_connection.cpp \
    btwindow.cpp \
    commandline_eas_board.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    bluetooth_connection.h \
    btwindow.h \
    commandline_eas_board.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    btwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

ANDROID_ABIS = arm64-v8a
