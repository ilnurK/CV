QT += core gui
greaterThan(QT_MAJOR_VERSION, 4) QT += widgets

CONFIG += c++17 qmake6

pver = 11  # python version
INCLUDEPATH += /usr/include/python3.$$pver
LIBS += -L/usr/lib/python3.$$pver/ -lpython3.$$pver

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../../controllers/race/s21_race_controller.cc \
    ../../../brick_game/snake/s21_apple.cc \
    ../../../brick_game/snake/s21_field.cc \
    ../../../brick_game/snake/s21_snake.cc \
    ../../../brick_game/snake/s21_snake_FSM.cc \
    ../../../brick_game/snake/s21_support.cc \
    ../../../brick_game/tetris/s21_tetris_FSM.c \
    ../../../brick_game/tetris/s21_tetris_field.c \
    ../../../brick_game/tetris/s21_tetris_figures.c \
    ../../../brick_game/s21_brick_games_highscores.c \
    ../../../controllers/tetris/s21_tetris_controller_c.c \
    ../../../controllers/tetris/s21_tetris_controller.cc \
    s21_bg_buttons.cc \
    s21_bg_main.cc \
    s21_bg_window.cc \
    s21_resized_view.cc

HEADERS += \
    ../../../controllers/race/s21_race_controller.h \
    ../../../brick_game/snake/s21_apple.h \
    ../../../brick_game/snake/s21_field.h \
    ../../../brick_game/snake/s21_snake.h \
    ../../../brick_game/snake/s21_snake_FSM.h \
    ../../../brick_game/snake/s21_support.h \
    ../../../brick_game/tetris/s21_tetris_FSM.h \
    ../../../brick_game/tetris/s21_tetris_field.h \
    ../../../brick_game/tetris/s21_tetris_figures.h \
    ../../../brick_game/s21_brick_games_highscores.h \
    ../../../brick_game/s21_brick_games_directions.h \
    ../../../controllers/tetris/s21_tetris_controller_c.h \
    ../../../controllers/tetris/s21_tetris_controller.h \
    ../../../controllers/s21_controller.h \
    s21_bg_keys.h \
    s21_bg_window.h \
    s21_resized_view.h \
    s21_desktop_view.h \
    s21_desktop_view.tpp

FORMS += \
    s21_bg_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LOGS_DIR = $$(HOME)/brick_games/

!exists($$LOGS_DIR) {
    mkpath($$LOGS_DIR)
}

!exists($$LOGS_DIR/snake_highscore) {
    write_file($$LOGS_DIR/snake_highscore, "")

}

!exists($$LOGS_DIR/tetris_highscore) {
    write_file($$LOGS_DIR/tetris_highscore, "")
}

RESOURCES += \
    ../images/button.png \
    ../images/button_hovered.png \
    ../images/button_pressed.png \
    ../images/arrows.png \
    ../images/brick_game.png \
    ../images/snake_game.png \
    ../images/tetris_game.png \
    ../images/race_game.png \
    ../images/tetris.ico \
    ../fonts/lab-grotesk.ttf \
    ../../../brick_game/race/s21_race.py \
    ../../../controllers/race/s21_race_controller.py \
    ../../../obj/brick_game/libhighscore.so

DISTFILES += \
    ../../../brick_game/race/s21_race.py \
    ../../../controllers/race/s21_race_controller.py \
    ../../../obj/brick_game/libhighscore.so \
    ../images/brick_game.png \
    ../images/button.png \
    ../images/button_hovered.png \
    ../images/button_pressed.png \
    ../images/arrows.png \
    ../images/race_game.png \
    ../images/snake_game.png \
    ../images/tetris.ico \
    ../images/tetris_game.png \
    ../fonts/lab-grotesk.ttf \
