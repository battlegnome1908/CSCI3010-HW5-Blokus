QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    board.cpp \
    game.cpp \
    main.cpp \
    player.cpp \
    plotwindow.cpp \
    shape.cpp \
    shapecreationdialog.cpp \
    shapefactory.cpp \
    shapeitem.cpp \
    startupdialog.cpp

HEADERS += \
    board.h \
    game.h \
    player.h \
    plotwindow.h \
    shape.h \
    shapecreationdialog.h \
    shapefactory.h \
    shapeitem.h \
    startupdialog.h

FORMS += \
    plotwindow.ui \
    shapecreationdialog.ui \
    startupdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
