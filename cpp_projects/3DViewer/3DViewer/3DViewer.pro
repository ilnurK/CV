QT += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 -fopenmp

QMAKE_CXXFLAGS += -fopenmp

ICON = icon.png

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

VERSION = 1.0
QMAKE_TARGET_COMPANY = School 21
QMAKE_TARGET_PRODUCT = 3DViewer
QMAKE_TARGET_DESCRIPTION = Программа для визуализации каркасной модели в трёхмерном пространстве
QMAKE_TARGET_COPYRIGHT = Delena Leeanna, Krustofski Kwaltz, Suzann Pipe

SOURCES += \
    ../backend/error_handle.c \
    ../backend/get_matrices.c \
    ../backend/get_vertices_index.c \
    ../backend/get_vertices_matrix.c \
    ../backend/move.c \
    connections.cpp \
    gif.cpp \
    main.cpp \
    mainwindow.cpp \
    mouse.cpp \
    settings.cpp \
    settingsdialog.cpp \
    widget.cpp

HEADERS += \
    ../backend/s21_3DViewer.h \
    gif.h \
    mainwindow.h \
    settingsdialog.h \
    widget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
