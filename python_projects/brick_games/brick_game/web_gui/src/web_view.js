import { SITE, DIRECTIONS, END_STATES, GAMES, FREE_CELLS,
         GAME_BOARD_HEIGHT, GAME_BOARD_WIDTH,
         SIDE_BOARD_HEIGHT, SIDE_BOARD_WIDTH} from './config.js';
import { GameBoard} from './game-board.js';

export class WebView {
    constructor() {
        this.game = GAMES.tetris;
        this.START = 1;
        this.state = this.START;
        this.delay = 600;
        this.dir = 0;
        this.hold_status = false;
        this.score = 0;
        this.high_score = 0;
        this.level = 0;
        this.pause = false;
        this.game_board = new GameBoard(document.querySelector('#game-board'));
        this.side_board = new GameBoard(document.querySelector('#side-board'),
                                        'side-tile',
                                        SIDE_BOARD_HEIGHT,
                                        SIDE_BOARD_WIDTH);
        this.is_reset = false;
        this.are_playing = false;

        this.letter_width = 5;
        this.letter_height = 4;
        this.digit_width = 3;
        this.digit_height = 4;

        this.score_label_y_start = 0;
        this.hscore_label_y_start = 10;
        this.level_label_y_start = 20;
        this.extra_label_y_start = 30;
        this.pause_label_y_start_with_extra = 40;
        this.pause_label_y_start = this.extra_label_y_start;
        this.initGameScreen();
    }

    initGameScreen() {
        function drawRace() {
            function drawRacePreview(poses) {
                for (let i = 0, cr = 0; i < GAME_BOARD_HEIGHT - 1; ++i, ++cr) {
                    if (cr % 3 != 0 || cr == 0) {
                        poses[i][GAME_BOARD_WIDTH - 1] = this.game_board.TILE_TYPE.active;
                    } else {
                        cr = -1;
                    }
                }
        
                function drawCar(gb, y_start, x_start) {
                    poses[y_start][x_start] = gb.TILE_TYPE.active;
                    poses[y_start + 1][x_start] = gb.TILE_TYPE.active;
                    poses[y_start + 2][x_start] = gb.TILE_TYPE.active;
                    
                    poses[y_start + 1][x_start - 1] = gb.TILE_TYPE.active;
                    poses[y_start + 1][x_start + 1] = gb.TILE_TYPE.active;
        
                    poses[y_start + 3][x_start - 1] = gb.TILE_TYPE.active;
                    poses[y_start + 3][x_start + 1] = gb.TILE_TYPE.active;
        
                }
        
                drawCar(this.game_board, 2, GAME_BOARD_WIDTH - 4);
                drawCar(this.game_board, GAME_BOARD_HEIGHT - 4, GAME_BOARD_WIDTH - 4);
                
            }
    
            const poses = Array.from({ length: GAME_BOARD_HEIGHT },
                () => Array(GAME_BOARD_WIDTH).fill(0));
            const start_x = 0;
            const start_y_r = 0;
            this.letterR(poses, start_y_r, start_x);
            const start_y_a = 5;
            this.letterA(poses, start_y_a, start_x);
            const start_y_c = 10;
            this.letterC(poses, start_y_c, start_x);
            const start_y_e = 15;
            this.letterE(poses, start_y_e, start_x);
            drawRacePreview.call(this, poses);
            
            this.boardTraversing((y, x) => poses[y][x]);
        }
        
        function drawSnake() {
            function drawSnakeAndApple(poses) {
                let y_start = 15;
                let x_left = 0;
                let x_right = GAME_BOARD_WIDTH - 1;
                let y_low = GAME_BOARD_HEIGHT - 1;
                let y_end = GAME_BOARD_HEIGHT - 7;
                for (let x = 4; x > x_left; --x) {
                    poses[y_start][x] = this.game_board.TILE_TYPE.active;
                }
                for (let y = y_start; y < y_low; ++y) {
                    poses[y][x_left + 1] = this.game_board.TILE_TYPE.active;
                }
                for (let x = x_left + 2; x < x_right; ++x) {
                    poses[y_low - 1][x] = this.game_board.TILE_TYPE.active;
                }
                for (let y = y_low - 1; y > y_end; --y) {
                    poses[y][x_right - 1] = this.game_board.TILE_TYPE.active;
                }
                poses[y_end - 2][x_right - 1] = this.game_board.TILE_TYPE.active;
            }
    
            const poses = Array.from({ length: GAME_BOARD_HEIGHT },
                () => Array(GAME_BOARD_WIDTH).fill(0));
            const start_x = 0;
            const start_y_s = 0;
            this.letterS(poses, start_y_s, start_x);
            const start_y_n = 5;
            this.letterN(poses, start_y_n, start_x);
            const start_y_a = 10;
            this.letterA(poses, start_y_a, start_x);
    
    
            const start_x_shift = 6;
            const start_y_k = 0;
            this.letterK(poses, start_y_k, start_x_shift);
            const start_y_e = 5;
            this.letterE(poses, start_y_e, start_x_shift);
    
            drawSnakeAndApple.call(this, poses);
    
            this.boardTraversing((y, x) => poses[y][x]);
        }
    
        function drawTetris() {
            const poses = Array.from({ length: GAME_BOARD_HEIGHT },
                () => Array(GAME_BOARD_WIDTH).fill(0));
            const start_x = 0;
            let start_y_t = 0;
            this.letterT(poses, start_y_t, start_x);
            const start_y_e = 5;
            this.letterE(poses, start_y_e, start_x);
            start_y_t = 10;
            this.letterT(poses, start_y_t, start_x);
            const start_y_r = 15;
            this.letterR(poses, start_y_r, start_x);
            const start_x_shift = 6;
            const start_y_i = 0;
            this.letterI(poses, start_y_i, start_x_shift);
            const start_y_s = 5;
            this.letterS(poses, start_y_s, start_x_shift);
            
            poses[10][GAME_BOARD_WIDTH - 4] = this.game_board.TILE_TYPE.active;
            poses[11][GAME_BOARD_WIDTH - 4] = this.game_board.TILE_TYPE.active;
            poses[11][GAME_BOARD_WIDTH - 3] = this.game_board.TILE_TYPE.active;
            poses[12][GAME_BOARD_WIDTH - 3] = this.game_board.TILE_TYPE.active;
    
            poses[14][GAME_BOARD_WIDTH - 2] = this.game_board.TILE_TYPE.active;
            poses[15][GAME_BOARD_WIDTH - 1] = this.game_board.TILE_TYPE.active;
            poses[15][GAME_BOARD_WIDTH - 2] = this.game_board.TILE_TYPE.active;
            poses[15][GAME_BOARD_WIDTH - 3] = this.game_board.TILE_TYPE.active;
    
            poses[17][GAME_BOARD_WIDTH - 2] = this.game_board.TILE_TYPE.active;
            poses[18][GAME_BOARD_WIDTH - 2] = this.game_board.TILE_TYPE.active;
            poses[17][GAME_BOARD_WIDTH - 3] = this.game_board.TILE_TYPE.active;
            poses[18][GAME_BOARD_WIDTH - 3] = this.game_board.TILE_TYPE.active;
    
            poses[14][GAME_BOARD_WIDTH - 5] = this.game_board.TILE_TYPE.active;
            poses[15][GAME_BOARD_WIDTH - 5] = this.game_board.TILE_TYPE.active;
            poses[16][GAME_BOARD_WIDTH - 5] = this.game_board.TILE_TYPE.active;
            poses[17][GAME_BOARD_WIDTH - 5] = this.game_board.TILE_TYPE.active;
            this.boardTraversing((y, x) => poses[y][x]);
        }
    

        if (this.game == GAMES.race) {
            drawRace.call(this);
        } else if (this.game == GAMES.snake) {
            drawSnake.call(this);
        } else if (this.game == GAMES.tetris) {
            drawTetris.call(this);
        }
        this.initSideScreen();
    }

    initSideScreen() {
        function drawScoreLabel(poses) {
            const start_x_s = 2;
            this.letterS(poses, this.score_label_y_start, start_x_s);
            const start_x_c = start_x_s +  this.letter_width;
            this.letterC(poses, this.score_label_y_start, start_x_c);
            const start_x_o = start_x_c +  this.letter_width;
            this.letterO(poses, this.score_label_y_start, start_x_o);
            const start_x_r = start_x_o +  this.letter_width;
            this.letterR(poses, this.score_label_y_start, start_x_r);
            const start_x_e = start_x_r +  this.letter_width;
            this.letterE(poses, this.score_label_y_start, start_x_e);
        }

        function drawHighScoreLabel(poses) {
            const start_x_h = 0;
            this.letterH(poses, this.hscore_label_y_start, start_x_h);
            const start_x_s = start_x_h +  this.letter_width;
            this.letterS(poses, this.hscore_label_y_start, start_x_s);
            const start_x_c = start_x_s +  this.letter_width;
            this.letterC(poses, this.hscore_label_y_start, start_x_c);
            const start_x_o = start_x_c +  this.letter_width;
            this.letterO(poses, this.hscore_label_y_start, start_x_o);
            const start_x_r = start_x_o +  this.letter_width;
            this.letterR(poses, this.hscore_label_y_start, start_x_r);
            const start_x_e = start_x_r +  this.letter_width;
            this.letterE(poses, this.hscore_label_y_start, start_x_e);
        }

        function drawLevelLabel(poses) {
            let start_x_l = 2;
            this.letterL(poses, this.level_label_y_start, start_x_l);
            let start_x_e = start_x_l +  this.letter_width;
            this.letterE(poses, this.level_label_y_start, start_x_e);
            const start_x_v = start_x_e +  this.letter_width;
            this.letterV(poses, this.level_label_y_start, start_x_v);
            start_x_e = start_x_v +  this.letter_width;
            this.letterE(poses, this.level_label_y_start, start_x_e);
            start_x_e = start_x_e +  this.letter_width;
            this.letterL(poses, this.level_label_y_start, start_x_e);
        }

        function drawSpeedLabel(poses) {
            const start_x_s = 2;
            this.letterS(poses, this.extra_label_y_start, start_x_s);
            const start_x_p = start_x_s +  this.letter_width;
            this.letterP(poses, this.extra_label_y_start, start_x_p);
            let start_x_e = start_x_p +  this.letter_width;
            this.letterE(poses, this.extra_label_y_start, start_x_e);
            start_x_e = start_x_e +  this.letter_width;
            this.letterE(poses, this.extra_label_y_start, start_x_e);
            const start_x_d = start_x_e +  this.letter_width;
            this.letterD(poses, this.extra_label_y_start, start_x_d);
        }
    
        function drawNextLabel(poses) {
            const start_x_n = 5;
            this.letterN(poses, this.extra_label_y_start, start_x_n);
            let start_x_e = start_x_n +  this.letter_width;
            this.letterE(poses, this.extra_label_y_start, start_x_e);
            const start_x_x = start_x_e +  this.letter_width;
            this.letterX(poses, this.extra_label_y_start, start_x_x);
            const start_x_t = start_x_x +  this.letter_width;
            this.letterT(poses, this.extra_label_y_start, start_x_t);
        }
    
        function clearExtraField() {
            const rows = SIDE_BOARD_HEIGHT - this.extra_label_y_start;
            const cols = SIDE_BOARD_WIDTH;
            this.extra_label_y_start;
            this.boardTraversing(() => 0, this.side_board, rows, cols,
                                 this.extra_label_y_start);
        }

        const poses = Array.from({ length: SIDE_BOARD_HEIGHT },
            () => Array(SIDE_BOARD_WIDTH).fill(0));
        drawScoreLabel.call(this, poses);
        drawHighScoreLabel.call(this, poses);
        drawLevelLabel.call(this, poses);
        if (this.game == GAMES.race || this.game == GAMES.tetris) {
            clearExtraField.call(this);
            (this.game == GAMES.race) ? drawSpeedLabel.call(this,poses) :
                                        drawNextLabel.call(this,poses);
        }
        this.boardTraversing((y, x) => poses[y][x], this.side_board,
                             SIDE_BOARD_HEIGHT, SIDE_BOARD_WIDTH);
    }

    async gameInit() {
        await this.resetGame();
        const path = `${SITE}games/${this.game}`
        try {
            const response = await fetch(path, {method: 'POST'})

            if (!response.ok) {
                throw new Error(`HTTP error: ${response.status} - ${response.statusText}`);
            }
            const text = await response.text();
            try {
                const data = JSON.parse(text);
                console.log('Data:', data);
                this.are_playing = true;
                await this.play()
            } catch (error) {
                console.error('JSON deserialization error:', error);
            }
        } catch (error){
            console.error('fetch to games/game_id error: ', error);
        }
    }

    async resetGame() {
        this.are_playing = false;
        this.pause = false;
        this.state = this.START;
        this.is_reset = true;
        this.boardTraversing();
        this.initGameScreen();
        const response = await fetch(`${SITE}games/reset`);
        if (!response.ok) {
            console.error('Error:', data);
        }
    }

    boardTraversing(func = (y, x) => 0, board = this.game_board,
                    rows = GAME_BOARD_HEIGHT, cols = GAME_BOARD_WIDTH,
                    y_shift = 0) {
        for (let y = 0; y < rows; ++y) {
            for (let x = 0; x < cols; ++x) {
                let val = func(y, x);
                board.tileAction(val, x, y + y_shift);
            }
        }
    }
    
    async play() {
        this.is_reset = false;
        let error = false;
        this.InitEndStates();
        while (!(Object.values(END_STATES).includes(this.state)) && !error && !this.is_reset) {
            if (this.pause === false) {
                const response = await fetch(`${SITE}state/${this.state}`, {method: 'POST',});
                const data = await response.json();
                if (response.ok) {
                    this.state = data.state;
                    this.delay = data.delay;
                    this.boardTraversing();
                    this.showField(data.field);
                    this.SideScreenHandle(data);
                } else {
                    error = true;
                    console.error('Error:', data);
                }
            }
            await this.sleep(this.delay);
        }
        if (Object.values(END_STATES).includes(this.state)) {
            this.showEndGame();
        }
        this.are_playing = false;
    }

    InitEndStates() {
        if (this.game == GAMES.race) {
            END_STATES.GAME_OVER = 6;
        } else if (this.game == GAMES.snake) {
            END_STATES.GAME_OVER = 7;
        } else if (this.game == GAMES.tetris) {
            END_STATES.GAME_OVER = 6;
        }
    }
    
    showField(field) {
        function isFilledCell(char) {
            return (FREE_CELLS.includes(char)) ? 0 : 1;
        }

        this.boardTraversing((y, x) => isFilledCell(field[y][x]));
    }


    SideScreenHandle(data) {
        this.score = data.score;
        this.high_score = data.high_score;
        this.level = data.level;
        this.drawSideValue(this.score, this.score_label_y_start);
        this.drawSideValue(this.high_score, this.hscore_label_y_start);
        this.drawSideValue(this.level, this.level_label_y_start);
        this.drawExtraInfo(data);
        this.cleanPauseLabel(data);
    }

    drawSideValue(number, y_shift) {
        function drawNumber(poses, number, y_start) {
            let exponent = 0;
            let temp = number;
            while (temp >= 10) {
                temp /= 10;
                exponent += 1;
            }
            let shift = 1 + Math.floor((SIDE_BOARD_WIDTH - (exponent + 1) * (1 + this.digit_width)) / 2);
            temp = number;
            do {
                const ten_exp = 10 ** exponent--;
                const divr = temp / ten_exp;
                let digit = Math.floor(divr);
                temp %= ten_exp;
                const func_name = 'digit' + digit.toString();
                if (typeof this[func_name] === 'function') {
                    this[func_name](poses, y_start, shift);
                }
                shift += this.digit_width + 1
            } while (exponent > -1);
        }

        const rows = this.digit_height;
        const cols = SIDE_BOARD_WIDTH;
        const poses = Array.from({ length: rows}, () => Array(cols).fill(0));
        const total_shift = y_shift +  this.letter_height + 1;
        this.boardTraversing(() => 0, this.side_board, rows, cols, total_shift);
        if (number < 1e8) {
            drawNumber.call(this, poses, number, 0);
        }
        this.boardTraversing((y, x) => poses[y][x], this.side_board, rows,
                             cols, total_shift);
    }

    drawExtraInfo(data) {
        function drawNextFigure(data) {
            const nf = data.next;
            const nf_len = 4;
            const scale_coef = 2;
            const rows = this.digit_height + 1;
    
            function GetNextCenter(old_pos, new_center) {
                let new_pos = [(old_pos[0] - new_center[0]) * scale_coef, 
                               (old_pos[1] - new_center[1]) * scale_coef, 
                ];
                return new_pos;
            }
    
            function Centralization(nf) {
                let y_min = SIDE_BOARD_HEIGHT;
                let x_min = SIDE_BOARD_WIDTH;
                for (let i = 0; i < nf_len; ++i) {
                    if (nf[i][0] < x_min) {
                        x_min = nf[i][0]
                    }
                    if (nf[i][1] < y_min) {
                        y_min = nf[i][1]
                    }
                }
                x_min = 0 - x_min;
                y_min = 0 - y_min;
    
                for (let i = 0; i < nf_len; ++i) {
                    nf[i][0] += x_min;
                    nf[i][1] += y_min;
                }
            }

            function CalcShifts() {
                let x_sum = 0;
                for (let i = 0; i < nf_len; ++i) {
                    x_sum += new_centers[i][0];
                }
                let x_center = Math.floor(x_sum / nf_len);
                return Math.floor(SIDE_BOARD_WIDTH / 2) - x_center
            }

            function drawScale2Pixel(poses, center) {
                poses[center[1]][center[0]] = this.side_board.TILE_TYPE.active;
                poses[center[1]][center[0] - 1] = this.side_board.TILE_TYPE.active;
                poses[center[1] - 1][center[0] - 1] = this.side_board.TILE_TYPE.active;
                poses[center[1] - 1][center[0]] = this.side_board.TILE_TYPE.active;
            }

            const start_point = nf[0];
            let new_centers = [];
            for (let i = 0; i < nf_len; ++i) {
                new_centers.push(GetNextCenter(nf[i], start_point))
            }
            Centralization(new_centers);
    
            let x_shift = CalcShifts();
            let y_shift = 1;
     
            const poses = Array.from( { length: rows},
                () => Array(SIDE_BOARD_WIDTH).fill(0));
    
            for (let i = 0; i < nf_len; ++i) {
                new_centers[i][0] += x_shift;
                new_centers[i][1] += y_shift;
                drawScale2Pixel.call(this, poses, new_centers[i]);
            }
    
            this.boardTraversing((y, x) => poses[y][x], this.side_board,
                rows, SIDE_BOARD_WIDTH,
                this.extra_label_y_start + this.digit_height + 1);
        }

        if (this.game == GAMES.race) {
            this.drawSideValue(data.speed, this.extra_label_y_start);
        } else if (this.game == GAMES.tetris) {
            drawNextFigure.call(this, data);
        }
    }

    drawPauseLabel() {
        const poses = Array.from({ length: this.digit_height },
            () => Array(SIDE_BOARD_WIDTH).fill(0));

        let y_start = this.pause_label_y_start_with_extra;
        if (this.game == GAMES.snake) {
            y_start = this.pause_label_y_start;
        }
        const start_x_p = 2;
        this.letterP(poses, 0, start_x_p);
        const start_x_a = start_x_p + this.letter_width;
        this.letterA(poses, 0, start_x_a);
        const start_x_u = start_x_a + this.letter_width;
        this.letterU(poses, 0, start_x_u);
        const start_x_s = start_x_u +  this.letter_width;
        this.letterS(poses, 0, start_x_s);
        const start_x_e = start_x_s +  this.letter_width;
        this.letterE(poses, 0, start_x_e);

        this.boardTraversing((y, x) => poses[y][x], this.side_board,
            this.digit_height, SIDE_BOARD_WIDTH, y_start);
    }

    cleanPauseLabel() {
        let y_start = this.pause_label_y_start_with_extra;
        if (this.game == GAMES.snake) {
            this.y_start = this.pause_label_y_start;
        }
        const poses = Array.from({ length: this.digit_height },
            () => Array(SIDE_BOARD_WIDTH).fill(0));
        this.boardTraversing(() => 0, this.side_board,
        this.digit_height, SIDE_BOARD_WIDTH, y_start);
    }
    
    async setAction(action, is_hold) {
        if (this.are_playing) {
            const action_id = DIRECTIONS[action];
            if (this.dir !== action_id || this.hold_status !== is_hold) {
                await this.setActionInGame(action_id, is_hold);
            } 
        } else if (is_hold){
            this.rotateCarousel(action);
        }
    }

    async setActionInGame(dir, is_hold) {
        try {
            this.dir = dir;
            this.hold_status = is_hold;
            if (dir == DIRECTIONS["pause"] && is_hold === false) {
                this.pause = (!this.pause) ? true : false;
                if (this.pause) {
                    this.drawPauseLabel();
                }
            }
            const response = await fetch(`${SITE}actions`, 
                {method: 'POST',
                 headers: { 'Content-Type': 'application/json;charset=utf-8' },
                 body: JSON.stringify({ action_id: this.dir,
                                        hold: this.hold_status,
                                        are_playing: this.are_playing })
                });
            const data = await response.json();
            if (response.ok) {
                console.log('Success:', data);
            } else {
                console.error('Error:', data);
            }
        } catch (error) {
            console.error('Ошибка:', error);
        }
    }

    rotateCarousel(action) {
        const games = Object.values(GAMES);
        const min_game = Math.min(...games);
        const max_game = Math.max(...games);
        if (action == 'left') {
            if (this.game != min_game)
                this.game -= 1;
            else {
                this.game = max_game;
            } 
        } else if (action == 'right') {
            if (this.game != max_game) {
                this.game += 1;
            } else {
                this.game = min_game;
            }
        }
        this.boardTraversing();
        this.initGameScreen();
    }

    sleep(ms) {
        return new Promise(resolve => setTimeout(resolve, ms));
    }

    showEndGame() {
        function drawGameOver(poses)  {
            const start_x = 0;
            const start_y_g = 0;
            this.letterG(poses, start_y_g, start_x);
            const start_y_a = 5;
            this.letterA(poses, start_y_a, start_x);
            const start_y_m = 10;
            this.letterM(poses, start_y_m, start_x);
            let start_y_e = 15;
            this.letterE(poses, start_y_e, start_x);
    
            const start_x_shift = 6;
            const start_y_o = 0;
            this.letterO(poses, start_y_o, start_x_shift);
            const start_y_v = 5;
            this.letterV(poses, start_y_v, start_x_shift);
            start_y_e = 10;
            this.letterE(poses, start_y_e, start_x_shift);
            const start_y_r = 15;
            this.letterR(poses, start_y_r, start_x_shift);
        }

        function drawWin(poses) {
            const start_x = Math.floor((GAME_BOARD_WIDTH - 
                this.digit_width) / 2);
            const start_y_w = 3;
            this.letterW(poses, start_y_w, start_x);
            const start_y_i = start_y_w + this.digit_height + 1;
            this.letterI(poses, start_y_i, start_x);
            const start_y_n = start_y_i + this.digit_height + 1;
            this.letterN(poses, start_y_n, start_x);
        }

        const poses = Array.from({ length: GAME_BOARD_HEIGHT },
              () => Array(GAME_BOARD_WIDTH).fill(0));
        if (this.state == END_STATES.WIN) {
            drawWin.call(this, poses);
        } else {
            drawGameOver.call(this, poses);
        }
        this.boardTraversing((y, x) => poses[y][x]);
    }
    
    // DRAWS
    // LETTERS
    letterA(poses, start_y,  start_x) {
        //     |
        //   | |
        //  |_ |
        // |   |

        poses[start_y][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 3] = this.game_board.TILE_TYPE.active;

        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.sec_diagonal_up;
        poses[start_y + 2][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x] = this.game_board.TILE_TYPE.active;
        
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.sec_diagonal_down;
        poses[start_y + 1][start_x + 1] = this.game_board.TILE_TYPE.sec_diagonal_down;
        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.sec_diagonal_down;
        poses[start_y + 3][start_x + 1] = this.game_board.TILE_TYPE.sec_diagonal_up;
       
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.active;
    }

    letterC(poses, start_y, start_x) {
        //  |— — — 
        //  |
        //  |
        //  |— — —
    
        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y][start_x + 3] = this.game_board.TILE_TYPE.active;

        poses[start_y + 3][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 3] = this.game_board.TILE_TYPE.active;
    }

    letterD(poses, start_y, start_x) {
        //  |-\
        //  |  |
        //  |  |
        //  |-/

        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 3] = this.game_board.TILE_TYPE.main_diagonal_down;
        poses[start_y + 1][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 3] = this.game_board.TILE_TYPE.sec_diagonal_up;

        poses[start_y][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.active;

        poses[start_y + 3][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 2] = this.game_board.TILE_TYPE.active;

        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.main_diagonal_up;
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.sec_diagonal_down;


    }

    letterE(poses, start_y, start_x) {
        //  |— — — 
        //  |_ _ _
        //  |
        //  |— — —
    
        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y][start_x + 3] = this.game_board.TILE_TYPE.active;

        poses[start_y + 1][start_x + 1] = this.game_board.TILE_TYPE.horizontal_down50;
        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.horizontal_down50;
        poses[start_y + 1][start_x + 3] = this.game_board.TILE_TYPE.horizontal_down50;

        poses[start_y + 2][start_x + 1] = this.game_board.TILE_TYPE.horizontal_up50;
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.horizontal_up50;
        poses[start_y + 2][start_x + 3] = this.game_board.TILE_TYPE.horizontal_up50;

        poses[start_y + 3][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 3] = this.game_board.TILE_TYPE.active;
    }

    letterG(poses, start_y, start_x) {
        // |— — — 
        // |
        // |  / —
        // |— — / 
    
        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y][start_x + 3] = this.game_board.TILE_TYPE.active;

        poses[start_y + 3][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 3] = this.game_board.TILE_TYPE.sec_diagonal_up;
        
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.horizontal_up50;
        poses[start_y + 2][start_x + 3] = this.game_board.TILE_TYPE.active;

    }

    letterH(poses, start_y, start_x) {
        //  |    |
        //  | -- |
        //  | -- |
        //  |    |

        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 3] = this.game_board.TILE_TYPE.active;

        poses[start_y + 1][start_x + 1] = this.game_board.TILE_TYPE.horizontal_down50;
        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.horizontal_down50;

        poses[start_y + 2][start_x + 1] = this.game_board.TILE_TYPE.horizontal_up50;
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.horizontal_up50;
    }

    letterI(poses, start_y, start_x) {
        //     |
        //     |
        //     |
        //     |
    
        poses[start_y][start_x + 1] = this.game_board.TILE_TYPE.vertical_left50;
        poses[start_y + 1][start_x + 1] = this.game_board.TILE_TYPE.vertical_left50;
        poses[start_y + 2][start_x + 1] = this.game_board.TILE_TYPE.vertical_left50;
        poses[start_y + 3][start_x + 1]  = this.game_board.TILE_TYPE.vertical_left50;
        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.vertical_right50;
        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.vertical_right50;
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.vertical_right50;
        poses[start_y + 3][start_x + 2]  = this.game_board.TILE_TYPE.vertical_right50;
    }

    letterK(poses, start_y, start_x) {
        //  | /
        //  |/
        //  |\
        //  | \

        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x]  = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 1] = this.game_board.TILE_TYPE.vertical_right50;
        poses[start_y + 1][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 1]  = this.game_board.TILE_TYPE.vertical_right50;
        
        poses[start_y + 2][start_x + 3] = this.game_board.TILE_TYPE.main_diagonal_down;
        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.main_diagonal_down;
        poses[start_y + 3][start_x + 2] = this.game_board.TILE_TYPE.main_diagonal_up;
        
        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.sec_diagonal_down;
        poses[start_y + 3][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x + 3] = this.game_board.TILE_TYPE.sec_diagonal_up;
    }

    letterL(poses, start_y, start_x) {
        //  |
        //  |
        //  |
        //  |--|

        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x] = this.game_board.TILE_TYPE.active;

        poses[start_y + 3][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 3] = this.game_board.TILE_TYPE.active;

    }

    letterM(poses, start_y, start_x) {
        //  |\/|
        //  |\/|
        //  |  |
        //  |  |

        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 3] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 1] = this.game_board.TILE_TYPE.main_diagonal_down;
        poses[start_y + 1][start_x + 1] = this.game_board.TILE_TYPE.main_diagonal_up;
        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.sec_diagonal_down;
        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.sec_diagonal_up;
    }

    letterN(poses, start_y, start_x) {
        //  |\  |
        //  | \ |
        //  |  \|
        //  |   |

        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 3] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 1] = this.game_board.TILE_TYPE.main_diagonal_down;
        poses[start_y + 1][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.main_diagonal_down;
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x + 1] = this.game_board.TILE_TYPE.main_diagonal_up;
        poses[start_y + 3][start_x + 2] = this.game_board.TILE_TYPE.main_diagonal_up;
    }

    letterO(poses, start_y, start_x) {
        //  |--|
        //  |  |
        //  |  |
        //  |--|

        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 3] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.active;

        poses[start_y + 3][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 2] = this.game_board.TILE_TYPE.active;
    }

    letterP(poses, start_y, start_x) {
        //  |— — — 
        //  |— — —
        //  |
        //  |
    
        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y][start_x + 3] = this.game_board.TILE_TYPE.active;

        poses[start_y + 1][start_x + 1] = this.game_board.TILE_TYPE.horizontal_down50;
        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.horizontal_down50;
        poses[start_y + 1][start_x + 3] = this.game_board.TILE_TYPE.active;

        poses[start_y + 2][start_x + 1] = this.game_board.TILE_TYPE.horizontal_up50;
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.horizontal_up50;
        poses[start_y + 2][start_x + 3] = this.game_board.TILE_TYPE.horizontal_up50;
    }

    letterR(poses, start_y, start_x) {
        // |— — — 
        // |— — — 
        // | |
        // |   \
    
        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 1] = this.game_board.TILE_TYPE.horizontal_up75;
        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.horizontal_up75;
        poses[start_y][start_x + 3] = this.game_board.TILE_TYPE.active;

        poses[start_y + 1][start_x + 1] = this.game_board.TILE_TYPE.horizontal_down50;
        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.horizontal_down50;
        poses[start_y + 1][start_x + 3] = this.game_board.TILE_TYPE.active;
        
        poses[start_y + 2][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x + 3] = this.game_board.TILE_TYPE.main_diagonal_down;
        poses[start_y + 3][start_x + 2] = this.game_board.TILE_TYPE.main_diagonal_up;
        poses[start_y + 3][start_x + 3] = this.game_board.TILE_TYPE.active;

    }
    
    letterS(poses, start_y, start_x) {
        //  |— — — 
        //  |_ _ _
        //       |
        //  |— — —
    
        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.horizontal_up50;
        poses[start_y + 3][start_x] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y][start_x + 3] = this.game_board.TILE_TYPE.active;

        poses[start_y + 1][start_x + 1] = this.game_board.TILE_TYPE.horizontal_down50;
        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.horizontal_down50;
        poses[start_y + 1][start_x + 3] = this.game_board.TILE_TYPE.horizontal_down50;

        poses[start_y + 2][start_x + 1] = this.game_board.TILE_TYPE.horizontal_up50;
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.horizontal_up50;
        poses[start_y + 2][start_x + 3] = this.game_board.TILE_TYPE.active;

        poses[start_y + 3][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 3] = this.game_board.TILE_TYPE.active;
    }

    letterT(poses, start_y, start_x) {
        //  — —|— — 
        //     |
        //     |
        //     |
    
        poses[start_y][start_x + 1] = this.game_board.TILE_TYPE.vertical_left50;
        poses[start_y + 1][start_x + 1] = this.game_board.TILE_TYPE.vertical_left50;
        poses[start_y + 2][start_x + 1] = this.game_board.TILE_TYPE.vertical_left50;
        poses[start_y + 3][start_x + 1]  = this.game_board.TILE_TYPE.vertical_left50;
        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.vertical_right50;
        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.vertical_right50;
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.vertical_right50;
        poses[start_y + 3][start_x + 2]  = this.game_board.TILE_TYPE.vertical_right50;

        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y][start_x + 3] = this.game_board.TILE_TYPE.active;
    }

    letterU(poses, start_y, start_x) {
        //  |  |
        //  |  |
        //  |  |
        //   \/

        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x] = this.game_board.TILE_TYPE.main_diagonal_up;

        poses[start_y][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 3] = this.game_board.TILE_TYPE.sec_diagonal_up;

        poses[start_y + 3][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 2] = this.game_board.TILE_TYPE.active;


    }

    letterV(poses, start_y, start_x) {
        //  |  |
        //  |  |
        //  \  /
        //   \/

        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x + 1] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.active;

        poses[start_y + 1][start_x + 1] = this.game_board.TILE_TYPE.main_diagonal_down;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.main_diagonal_up;

        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.sec_diagonal_down;
        poses[start_y + 2][start_x + 3] = this.game_board.TILE_TYPE.sec_diagonal_up;

        poses[start_y + 3][start_x + 1] = this.game_board.TILE_TYPE.main_diagonal_up;
        poses[start_y + 3][start_x + 2] = this.game_board.TILE_TYPE.sec_diagonal_up;

    }

    letterX(poses, start_y, start_x) {
        //  \  /
        //   \/
        //   /\
        //  /  \

        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.main_diagonal_up;

        poses[start_y + 2][start_x + 3] = this.game_board.TILE_TYPE.main_diagonal_down;
        poses[start_y + 3][start_x + 3] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 1] = this.game_board.TILE_TYPE.main_diagonal_down;
        poses[start_y + 1][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.main_diagonal_down;
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x + 1] = this.game_board.TILE_TYPE.main_diagonal_up;
        poses[start_y + 3][start_x + 2] = this.game_board.TILE_TYPE.main_diagonal_up;

        poses[start_y][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x + 1] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.sec_diagonal_down;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.sec_diagonal_down;
        poses[start_y + 1][start_x + 3] = this.game_board.TILE_TYPE.sec_diagonal_up;
        poses[start_y + 3][start_x + 1] = this.game_board.TILE_TYPE.sec_diagonal_up;
    }

    letterW(poses, start_y, start_x) {
        // | | |
        // | | |
        // |\|/|
        // |\|/|
        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x + 3] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 3] = this.game_board.TILE_TYPE.active;

        poses[start_y + 1][start_x + 1] = this.game_board.TILE_TYPE.sec_diagonal_down;
        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.main_diagonal_down;
        poses[start_y + 2][start_x + 1] = this.game_board.TILE_TYPE.main_diagonal_up;
        poses[start_y + 3][start_x + 2] = this.game_board.TILE_TYPE.main_diagonal_up;

        poses[start_y + 2][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.active;

        poses[start_y + 3][start_x + 1] = this.game_board.TILE_TYPE.sec_diagonal_up;
    }

    // DIGITS

    digit0(poses, start_y, start_x) {
        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 2] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 1] = this.game_board.TILE_TYPE.active;
    }

    digit1(poses, start_y, start_x) {
        //  / |
        // /  |
        //    |
        //    |

        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 2] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 1] = this.game_board.TILE_TYPE.sec_diagonal_down;
        poses[start_y + 1][start_x + 1] = this.game_board.TILE_TYPE.sec_diagonal_up;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.sec_diagonal_down;
    }

    digit2(poses, start_y, start_x) {
        //  |— — — 
        //  _ _ _|
        //  |
        //  |— — —
       
        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.horizontal_down50;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.active;

        poses[start_y + 1][start_x + 1] = this.game_board.TILE_TYPE.horizontal_down50;
        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.active;

        poses[start_y + 2][start_x + 1] = this.game_board.TILE_TYPE.horizontal_up50;
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.horizontal_up50;

        poses[start_y + 3][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 2] = this.game_board.TILE_TYPE.active;
    }

    digit3(poses, start_y, start_x) {
        //  |— — — 
        //  _ _ _|
        //       |
        //  |— — —
    
        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.horizontal_down50;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.horizontal_up50;
        poses[start_y + 3][start_x] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.active;

        poses[start_y + 1][start_x + 1] = this.game_board.TILE_TYPE.horizontal_down50;
        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.active;

        poses[start_y + 2][start_x + 1] = this.game_board.TILE_TYPE.horizontal_up50;
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.active;

        poses[start_y + 3][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 2] = this.game_board.TILE_TYPE.active;
    }

    digit4(poses, start_y, start_x) {
        //  |    |
        //  _ _ _|
        //       |
        //       |
    
        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.active;


        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 2] = this.game_board.TILE_TYPE.active;


        poses[start_y + 1][start_x + 1] = this.game_board.TILE_TYPE.horizontal_down50;
        poses[start_y + 2][start_x + 1] = this.game_board.TILE_TYPE.horizontal_up50;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.horizontal_up50;

    }

    digit5(poses, start_y, start_x) {
        //  |— — — 
        //  |_ _ _
        //       |
        //  |— — —
    
        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.horizontal_up50;
        poses[start_y + 3][start_x] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.active;

        poses[start_y + 1][start_x + 1] = this.game_board.TILE_TYPE.horizontal_down50;
        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.horizontal_down50;

        poses[start_y + 2][start_x + 1] = this.game_board.TILE_TYPE.horizontal_up50;
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.active;

        poses[start_y + 3][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 2] = this.game_board.TILE_TYPE.active;
    }

    digit6(poses, start_y, start_x) {
        //  |— — — 
        //  |_ _ _
        //  |    |
        //  |— — —
    
        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.horizontal_down50;
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 2] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x + 1] = this.game_board.TILE_TYPE.horizontal_down50;
        poses[start_y + 2][start_x + 1] = this.game_board.TILE_TYPE.horizontal_up50;
        poses[start_y + 3][start_x + 1] = this.game_board.TILE_TYPE.active;
    }

    digit7(poses, start_y, start_x) {
        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.active;

        poses[start_y + 2][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 1] = this.game_board.TILE_TYPE.sec_diagonal_up;
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.sec_diagonal_up;

        poses[start_y + 1][start_x + 1] = this.game_board.TILE_TYPE.sec_diagonal_down;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.sec_diagonal_down;
    }

    digit8(poses, start_y, start_x) {
        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x] = this.game_board.TILE_TYPE.active;


        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 2] = this.game_board.TILE_TYPE.active;


        poses[start_y][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x + 1] = this.game_board.TILE_TYPE.horizontal_down50;
        poses[start_y + 2][start_x + 1] = this.game_board.TILE_TYPE.horizontal_up50;
        poses[start_y + 3][start_x + 1] = this.game_board.TILE_TYPE.active;
    }

    digit9(poses, start_y, start_x) {
        poses[start_y][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x] = this.game_board.TILE_TYPE.horizontal_up50;
        poses[start_y + 3][start_x] = this.game_board.TILE_TYPE.active;


        poses[start_y][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 2][start_x + 2] = this.game_board.TILE_TYPE.active;
        poses[start_y + 3][start_x + 2] = this.game_board.TILE_TYPE.active;

        poses[start_y][start_x + 1] = this.game_board.TILE_TYPE.active;
        poses[start_y + 1][start_x + 1] = this.game_board.TILE_TYPE.horizontal_down50;
        poses[start_y + 2][start_x + 1] = this.game_board.TILE_TYPE.horizontal_up50;
        poses[start_y + 3][start_x + 1] = this.game_board.TILE_TYPE.active;
    }

} 
