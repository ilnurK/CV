export const SITE = "http://localhost:8080/api/"
export const GAMES = {
    'race': 1,
    'snake': 2,
    'tetris': 3,
}

export const DIRECTIONS = { 
    'up': 1,
    'down': 2,
    'left': 3,
    'right': 4,
    'action': 5,
    'pause': 6,
}
export const END_STATES = {
    'WIN': -1,
    'GAME_OVER': 6,
}

export const FREE_CELLS = ' '

export const GAME_BOARD_WIDTH = 10;
export const GAME_BOARD_HEIGHT = 20;

export const SIDE_BOARD_WIDTH = 29;
export const SIDE_BOARD_HEIGHT = 44;

export const rootStyles = {
    '--tile-size': '20px',
    '--tile-color': 'rgba(158, 172, 136, 1)',
    '--tile-active-color': '#222',
    '--game-board-width': GAME_BOARD_WIDTH,
    '--game-board-height': GAME_BOARD_HEIGHT,
    '--game-board-gap': '1px',
    '--game-board-background': '#333',
    '--side-tile-size': '4px',
    '--side-board-width': SIDE_BOARD_WIDTH,
    '--side-board-height': SIDE_BOARD_HEIGHT,
    '--side-board-gap': '0.5px',
};

export const keyCodes = {
    up: ['ArrowUp', 'KeyW', 'KeyI'],
    right: ['ArrowRight', 'KeyD', 'KeyL'],
    down: ['ArrowDown', 'KeyS', 'KeyK'],
    left: ['ArrowLeft', 'KeyA', 'KeyJ'],
    action: ['Space'],
    pause: ['KeyP'],
};
