QT += core gui
QT += widgets printsupport
QT += bluetooth
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BluetoothServiceFinder.cpp \
    BluetoothSocket.cpp \
    btwindow.cpp \
    commandline_eas_board.cpp \
    main.cpp \
    mainwindow.cpp \
    oscilloscope.cpp \
    qcustomplot.cpp

HEADERS += \
    BluetoothServiceFinder.h \
    BluetoothSocket.h \
    btwindow.h \
    commandline_eas_board.h \
    mainwindow.h \
    oscilloscope.h \
    qcustomplot.h

FORMS += \
    btwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

ANDROID_ABIS = armeabi-v7a

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

RESOURCES += \
    Resource.qrc
