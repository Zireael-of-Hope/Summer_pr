QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    border.cpp \
    collectibleobject.cpp \
    food.cpp \
    foodstorage.cpp \
    human.cpp \
    main.cpp \
    mainwindow.cpp \
    obstacle.cpp \
    ore.cpp \
    orestorage.cpp \
    storage.cpp

HEADERS += \
    border.h \
    collectibleobject.h \
    food.h \
    foodstorage.h \
    human.h \
    mainwindow.h \
    obstacle.h \
    ore.h \
    orestorage.h \
    storage.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
