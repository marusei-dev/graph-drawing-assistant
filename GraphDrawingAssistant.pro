QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    canvaswidget.cpp \
    edge.cpp \
    edgewidget.cpp \
    graph.cpp \
    main.cpp \
    mainwindow.cpp \
    vertex.cpp \
    vertexwidget.cpp

HEADERS += \
    canvaswidget.h \
    edge.h \
    edgewidget.h \
    graph.h \
    mainwindow.h \
    vertex.h \
    vertexwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
