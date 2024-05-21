# BrickGame
The game is based on the Brick Game console and contains two games from the console - Snake and Tetris.

It is developed according to the MVC (Model-View-Controller) pattern.
With two types of Views:
- CLI (ncurses)
- desktop (QT)  

Business logic of games is based on finite state machine, Tetris is written in C, and Snake in C++. 

## About games

The game field is a rectangle measuring 10 by 20 game pixels.
Games consist of changes in FSM states due to the expiration of the game timer. And the View displays the state of the game's state machine at a specific timer stop. 

### Game controls

The console has 4 motion control buttons, one action button, and control buttons: start (aka pause), sound, reset and exit.

### Snake

The goal of the game is to control the direction keys and speed up the snake using the action button to collect all the apples on the field
Wherein
- The initial length of the snake is equal to four game “pixels”, the snake has a head and a tail
- if the snake collides with the “apple”, its length increases by one.
- If the snake collides with the boundary of the field or with itself, the game ends in defeat.

### Tetris

The goal of the game is to control the direction keys (including instantly dropping using the down key), and turning the pieces using the action button to score the most points for removing a fully assembled “field line”
Wherein
- When you delete several lines at the same time, combo points are awarded
- If it is impossible to generate a new piece, the game ends with the defeat of the player.

#### Developed by suzannpi, play and have fun!