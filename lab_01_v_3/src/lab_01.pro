QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    canvas.cpp \
    change_figure.cpp \
    change_point.cpp \
    controller.cpp \
    draw_figure.cpp \
    error_list.cpp \
    main.cpp \
    model.cpp \
    read_figure.cpp \
    view.cpp

HEADERS += \
    auxiliary_ads.h \
    canvas.h \
    change_figure.h \
    change_point.h \
    controller.h \
    draw_figure.h \
    error_list.h \
    model.h \
    read_figure.h \
    view.h

FORMS += \
    view.ui

TRANSLATIONS += \
    lab_01_en_GB.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
