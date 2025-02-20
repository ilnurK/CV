import { GAME_BOARD_WIDTH, GAME_BOARD_HEIGHT } from './config.js';

export class GameBoard {
    constructor($gameBoard, tile_class = 'tile',
                rows = GAME_BOARD_HEIGHT, cols = GAME_BOARD_WIDTH) {
        this.element = $gameBoard;
        this.tiles = [];
        this.rows = rows;
        this.cols = cols;
        for (let i = 0; i < rows; ++i) {
            for (let j = 0; j < cols; ++j) {
                const $tile = document.createElement('div');
                $tile.classList.add(tile_class);
                $tile.id = `position-${i}-${j}`;
                this.tiles.push($tile);
                this.element.append($tile);
            }
        }
    }

    getTile(x, y) {
        return this.tiles[y * this.cols + x];
    }

    enableTile(x, y) {
        this.getTile(x, y).classList.add('active');
    }

    enableTileMainDiagUp(x, y) {
        this.getTile(x, y).classList.add('main_diagonal_up');
    }

    enableTileMainDiagDown(x, y) {
        this.getTile(x, y).classList.add('main_diagonal_down');
    }

    enableTileSecDiagUp(x, y) {
        this.getTile(x, y).classList.add('sec_diagonal_up');
    }

    enableTileSecDiagDown(x, y) {
        this.getTile(x, y).classList.add('sec_diagonal_down');
    }

    enableTileHorizontalDown50(x, y) {
        this.getTile(x, y).classList.add('horizontal_down50');
    }

    enableTileHorizontalDown25(x, y) {
        this.getTile(x, y).classList.add('horizontal_down25');
    }

    enableTileHorizontalUp75(x, y) {
        this.getTile(x, y).classList.add('horizontal_up75');
    }

    enableTileHorizontalUp50(x, y) {
        this.getTile(x, y).classList.add('horizontal_up50');
    }

    enableTileHorizontalUp25(x, y) {
        this.getTile(x, y).classList.add('horizontal_up25');
    }

    enableTileVerticalRight50(x, y) {
        this.getTile(x, y).classList.add('vertical_right50');
    }

    enableTileVerticalLeft50(x, y) {
        this.getTile(x, y).classList.add('vertical_left50');
    }
   
    disableTile(x, y) {
        const tile = this.getTile(x, y);
        let name = tile.className;
        const idx = name.indexOf(" ");
        name = (idx !== -1) ? name.substring(0, idx) : name; 
        tile.className = name;
    }

    TILE_TYPE = {
        "disable": 0,
        "active": 1,
        "main_diagonal_up": 2,
        "main_diagonal_down": 3,
        "sec_diagonal_up": 4,
        "sec_diagonal_down": 5,
        "horizontal_down50": 6,
        "horizontal_down25": 7,
        "horizontal_up50": 8,
        "horizontal_up25": 9,
        "horizontal_up75": 10,
        "vertical_right50": 11,
        "vertical_left50": 12,
    }
    
    TILE_ENUM = {
        0: 'disableTile',
        1: 'enableTile',
        2: 'enableTileMainDiagUp',
        3: 'enableTileMainDiagDown',
        4: 'enableTileSecDiagUp',
        5: 'enableTileSecDiagDown',
        6: 'enableTileHorizontalDown50',
        7: 'enableTileHorizontalDown25',
        8: 'enableTileHorizontalUp50',
        9: 'enableTileHorizontalUp25',
        10: 'enableTileHorizontalUp75',
        11: 'enableTileVerticalRight50',
        12: 'enableTileVerticalLeft50'
    }

    tileAction(id, x, y) {
        const method_name = this.TILE_ENUM[id];
        const method = this[method_name];
        if (typeof method === 'function') {
            return method.call(this, x, y);
        } else {
            console.error('Invalid action id');
        }
    }
}