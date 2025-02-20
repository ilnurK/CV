# BrickGame
The game is based on the Brick Game console and contains 3 games  
from the console - Snake, Tetris and Race.  

It is developed according to the MVC (Model-View-Controller) pattern.  
With three types of Views:
- CLI (ncurses)
- desktop (QT)
- WEB GUI  

Business logic of games is based on finite state machine,  
Tetris is written in C, Snake in C++ and Race on Python.  

## About games

The game field is a rectangle measuring 10 by 20 game pixels.  
Games consist of changes in FSM states due to the expiration  
of the game timer. And the View displays the state of the game's  
state machine at a specific timer stop.  

### Game controls

The console has 4 motion control buttons, one action button,  
and control buttons: start (aka pause), sound, reset and exit.  

### Tetris

The goal of the game is to fill a horizontal line with figures  
of different shapes, while the figures can be moved using the control  
keys (including instantly lowering the figure - with the down key)  
and rotated clockwise - with the action button, wherein
- When you delete several lines at the same time, combo points are awarded
- If it is impossible to generate a new piece, the game ends with the defeat of the player.

### Snake

The goal of the game is to control the direction keys and speed up  
the snake using the action button to collect all the apples on the field
Wherein
- The initial length of the snake is equal to four game “pixels”,
the snake has a head and a tail
- if the snake collides with the “apple”, its length increases by one.
- If the snake collides with the boundary of the field or with itself,
the game ends in defeat.

### Race

The main goal of the game is to drive as far as possible, dodging  
the opponent's cars using the direction keys, you can also speed up  
by pressing the up key

#### Developed by suzannpi, play and have fun!
___

### CLI version build

```
make cli
```

### DESKTOP version build

```
make install
brick_games
```

### WEB GUI version build
```
python3 -m venv race
source race/bin/activate
pip install -r requirements.txt
make server_start
```
