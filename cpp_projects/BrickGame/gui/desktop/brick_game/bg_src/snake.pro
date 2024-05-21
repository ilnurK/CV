QT += core gui
greaterThan(QT_MAJOR_VERSION, 4) QT += widgets

CONFIG += c++17 qmake

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../../../brick_game/snake/s21_apple.cc \
    ../../../../brick_game/snake/s21_field.cc \
    ../../../../brick_game/snake/s21_snake.cc \
    ../../../../brick_game/snake/s21_snake_FSM.cc \
    ../../../../brick_game/snake/s21_support.cc \
    ../../../../brick_game/tetris_c/s21_tetris_FSM.c \
    ../../../../brick_game/tetris_c/s21_tetris_controller.c \
    ../../../../brick_game/tetris_c/s21_tetris_field.c \
    ../../../../brick_game/tetris_c/s21_tetris_figures.c \
    ../../../../brick_game/tetris_c/s21_tetris_support.c \
    ../bg_games/tetris/s21_tetris_view.cc \
    ../bg_games/snake/s21_snake_view.cc \
    s21_bg_buttons.cc \
    s21_bg_main.cc \
    s21_bg_window.cc \
    s21_resized_view.cpp

HEADERS += \
    ../../../../brick_game/snake/s21_apple.h \
    ../../../../brick_game/snake/s21_field.h \
    ../../../../brick_game/snake/s21_snake.h \
    ../../../../brick_game/snake/s21_snake_controller.h \
    ../../../../brick_game/snake/s21_snake_FSM.h \
    ../../../../brick_game/snake/s21_support.h \
    ../../../../brick_game/tetris_c/s21_tetris_FSM.h \
    ../../../../brick_game/tetris_c/s21_tetris_controller.h \
    ../../../../brick_game/tetris_c/s21_tetris_field.h \
    ../../../../brick_game/tetris_c/s21_tetris_figures.h \
    ../../../../brick_game/tetris_c/s21_tetris_support.h \
    ../bg_games/tetris/s21_tetris_view.h \
    s21_bg_keys.h \
    s21_bg_window.h \
    ../bg_games/snake/s21_snake_view.h \
    s21_resized_view.h

FORMS += \
    s21_bg_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LOGS_DIR = ../../../../logs

!exists($$LOGS_DIR) {
    mkpath($$LOGS_DIR)
}

!exists($$LOGS_DIR/snake_score.log) {
    write_file($$LOGS_DIR/snake_score.log, "")

}

!exists($$LOGS_DIR/tetris_score.log) {
    write_file($$LOGS_DIR/tetris_score.log, "")
}

RESOURCES += \
    ../bg_images/button.png \
    ../bg_images/button_hovered.png \
    ../bg_images/button_pressed.png \
    ../bg_images/arrows.png \
    ../bg_images/brick_game.png \
    ../bg_images/snake_game.png \
    ../bg_images/tetris_game.png \
    ../bg_games/snake/snake_images/apple.png \
    ../bg_games/snake/snake_images/snake_body.png \
    ../bg_games/snake/snake_images/snake_head.png \
    ../bg_games/snake/snake_images/snake_tail.png \
    ../bg_games/snake/snake_images/win.png \
    ../bg_games/snake/snake_images/win_tongue.png \
    ../bg_games/snake/snake_images/game_over.png \
    ../bg_games/snake/snake_images/game_over_eyes.png \
    ../../../../logs/snake_score.log \
    ../../../../logs/tetris_score.log \
    ../bg_images/tetris.ico \
    ../fonts/lab-grotesk.ttf \

DISTFILES += \
    ../bg_images/brick_game.png \
    ../bg_images/button.png \
    ../bg_images/button_hovered.png \
    ../bg_images/button_pressed.png \
    ../bg_images/arrows.png \
    ../bg_games/snake/snake_images/apple.png \
    ../bg_games/snake/snake_images/snake_body.png \
    ../bg_games/snake/snake_images/snake_head.png \
    ../bg_games/snake/snake_images/snake_tail.png \
    ../bg_games/snake/snake_images/win.png \
    ../bg_games/snake/snake_images/win_tongue.png \
    ../bg_games/snake/snake_images/game_over.png \
    ../bg_games/snake/snake_images/game_over_eyes.png \
    ../../../../logs/snake_score.log \
    ../../../../logs/tetris_score.log \
    ../bg_images/snake_game.png \
    ../bg_images/tetris.ico \
    ../bg_images/tetris_game.png \
    ../fonts/lab-grotesk.ttf \
