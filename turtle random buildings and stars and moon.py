import turtle as t
from random import randint, choice

x, y, coords, m_coords = 400, 400, [], []  # размеры экрана, список координат
w_diff, w_size = 5, 10  # отступ до краев и между окон, их размер
s_diff, s_max_size = 5, 6  # отступ между звездами, их размер

t.Screen().setup(x, y)
t.Screen().colormode(255)
bgcolor = randint(0, 55), randint(0, 55), randint(0, 55)  # оттенки от черного до синего
t.Screen().bgcolor(bgcolor)
t.hideturtle()
t.penup()
t.speed(0)


def left(move_x):  # движение влево
    coords.append((t.xcor(), t.ycor()))  # запись координат в начале
    t.setheading(180)
    t.forward(move_x)
    coords.append((t.xcor(), t.ycor()))  # и в конце; в один список


def up(move_y):  # движение вверх
    t.setheading(90)
    t.forward(move_y)


def down(move_y):  # движение вниз
    t.setheading(270)
    t.forward(move_y)


def buildings():
    t.goto(-x // 2, -y // 2)  # движение к левому нижнему углу экрана
    t.fillcolor(randint(0, 25), randint(0, 25), randint(100, 255))  # оттенки синего
    t.begin_fill()
    t.goto(x // 2, -y // 2)  # движение к правому нижнему углу
    min_building_width = w_size * 2 + 3 * w_diff  # минимальная ширина здания
    min_building_heigth = w_size * 2 + 3 * w_diff  # минимальная высота здания
    t.goto(x // 2, randint(-min_building_heigth, min_building_heigth))
    while True:
        move_x = randint(min_building_width, min_building_width + w_diff)  # возможное передвижение налево
        if - move_x + t.xcor() >= -x // 2 + min_building_width:  # проверка на последний короткий отрезок
            left(move_x)
        else:
            coords.append((t.xcor(), t.ycor()))
            t.goto(-x // 2, t.ycor())
            coords.append((-x // 2, t.ycor()))
            break
        move_y = randint(min_building_heigth,
                         int(min_building_heigth + w_diff * 4))  # возможное передвижение вверх или вниз
        if randint(0, 1) == 1:  # вверх (1) или вниз
            if move_y + t.ycor() <= y // 2 - w_diff:  # проверка на верхнее касание
                up(move_y)
            else:
                down(move_y)
        else:
            if -move_y + t.ycor() >= - y // 2 + w_diff * 2:
                down(move_y)
            else:
                up(move_y)
    t.goto(-x // 2, -y // 2)
    t.end_fill()


def windows():  # окна
    t.fillcolor(randint(200, 255), randint(200, 255), randint(0, 200))  # оттенки желтого
    for i in range(0, len(coords) - 1, 2):  # проход по координатам
        y1_part1 = int(coords[i][1]) - w_diff  # координата низа окна по высоте с учётом уменьшения в цикле
        y1_part2 = int(coords[i][1]) + w_size  # координата верха окна по высоте с учётом уменьшения
        y1 = y // 2
        while y1 >= - y // 2 + w_size * 3 + w_diff * 3:  # проверка на касание низа экрана с отступом
            y1_part1 -= w_size * 2 + w_diff  # позиционируем окно
            y1_part2 -= w_size * 2 + w_diff
            y1 = randint(y1_part1, y1_part2)  # расположение по у от -у до верха линии с запасом
            for j in range(2):
                if j == 0:
                    x1 = coords[i][0] - w_size - w_diff
                else:
                    x1 = coords[i + 1][0] + w_diff
                t.goto(x1, y1)
                t.setheading(0)
                is_window = randint(0, 2)  # 1 из 3 окон включено
                if is_window == 1:
                    t.begin_fill()
                    for _ in range(4):
                        t.forward(w_size)
                        t.right(90)
                    t.end_fill()


def stars():  # звезды
    t.pencolor(randint(200, 255), randint(200, 255), randint(0, 150))  # оттенки желтого
    for i in range(0, len(coords) - 1, 2):  # проход по координатам
        y1_part1 = int(coords[i][1]) - s_max_size  # координата низа звезды по высоте с учётом уменьшения в цикле
        y1_part2 = int(coords[i][1]) + s_max_size  # координата верха звезды по высоте с учётом уменьшения
        y1 = - y // 2
        while y1 <= y // 2 - s_max_size * 2 - s_diff * 2:  # проверка касания верха экрана
            y1_part1 += s_max_size + s_diff  # позиционируем звезду
            y1_part2 += s_max_size + s_diff
            y1 = randint(y1_part1, y1_part2)  # расположение по у от -у до верха линии с запасом
            x1 = randint(int(coords[i + 1][0]) + s_max_size,
                         int(coords[i][0]) - s_max_size)
            is_star = randint(0, 2)  # 1 из 3 звезд
            if is_star == 1:
                t.goto(x1, y1)
                t.dot(randint(1, s_max_size))
            else:
                m_coords.append((t.xcor(), t.ycor()))


def moon(bgcolor):
    m_coord = choice(m_coords)
    t.goto(m_coord[0], m_coord[1])
    t.pencolor(randint(240, 255), randint(240, 255), randint(240, 255))
    t.dot(s_max_size * 5)
    t.goto(m_coord[0] - randint(0, s_max_size * 3), m_coord[1])
    t.pencolor(bgcolor)
    t.dot(s_max_size * 5)


buildings()
windows()
stars()
moon(bgcolor)