QT       += core gui
QT += sql #数据库
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    stuadd.cpp \
    stualter.cpp \
    studelete.cpp

HEADERS += \
    mainwindow.h \
    stuadd.h \
    stualter.h \
    studelete.h

FORMS += \
    mainwindow.ui \
    stuadd.ui \
    stualter.ui \
    studelete.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../../Qrc/20240822_Mine1.qrc

RC_ICONS = L_S_E-1_1.ico #设置.exe的图标#.ico文件要放在.pro文件同一目录下
