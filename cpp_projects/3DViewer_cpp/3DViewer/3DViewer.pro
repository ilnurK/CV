QT += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

darwin {
    ICON = viewer.png
}
linux {
    ICON = :viewer.ico
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

VERSION = 2.0
QMAKE_TARGET_COMPANY = School 21
QMAKE_TARGET_PRODUCT = 3DViewer
QMAKE_TARGET_DESCRIPTION = Программа для визуализации каркасной модели в трёхмерном пространстве
QMAKE_TARGET_COPYRIGHT = Delena Leeanna, Krustofski Kwaltz, Suzann Pipe

SOURCES += \
    ../Model/s21_viewer_model.cc \
    connections.cc \
    gif.cc \
    main.cc \
    mainwindow.cc \
    mouse.cc \
    settings.cc \
    settingsdialog.cc \
    widget.cc

HEADERS += \
    ../Controller/s21_viewer_controller.h \
    ../Model/s21_viewer_model.h \
    gif.h \
    mainwindow.h \
    settingsdialog.h \
    widget.h

FORMS += \
    mainwindow.ui

linux {
    LIBS += -lGLU
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    viewer.ico

DISTFILES += \
    viewer.ico
