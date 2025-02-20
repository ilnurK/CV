
import { WebView } from './src/web_view.js'
import { applyRootStyles } from './src/utils.js';
import { rootStyles, keyCodes } from './src/config.js';

applyRootStyles(rootStyles);

let view = new WebView();

document.addEventListener('DOMContentLoaded', () => {
    const start_button = document.querySelector('.start-button');
    start_button.addEventListener('click', async () => {
        await view.gameInit();
    });

    const reset_button = document.querySelector('.reset-button');
    reset_button.addEventListener('click', async () => {
        await view.resetGame();
    });

    const a_buttons = document.querySelectorAll('.action-button');
    a_buttons.forEach(button => {
        button.addEventListener('mousedown', async () => {
            const action_id = button.getAttribute('data-actions');
            await view.setAction(action_id, true);
        });
        button.addEventListener('mouseup', async () => {
            const action_id = button.getAttribute('data-actions'); 
            await view.setAction(action_id, false);
        });
    });
});


document.addEventListener('keydown', async function (event) {
    event.preventDefault();
    await ControlButtonsHandler(true, event);
});


document.addEventListener('keyup', async function (event) {
    event.preventDefault();
    await ControlButtonsHandler(false, event);
});

async function ControlButtonsHandler(hold, event) {
    if (keyCodes.up.includes(event.code)) {
        console.log('up');
        await view.setAction('up', hold);
    } else if (keyCodes.right.includes(event.code)) {
        console.log('right');
        await view.setAction('right', hold);
    } else if (keyCodes.down.includes(event.code)) {
        console.log('down');
        await view.setAction('down', hold);
    } else if (keyCodes.left.includes(event.code)) {
        console.log('left');
        await view.setAction('left', hold);
    } else if (keyCodes.action.includes(event.code)) {
        console.log('action');
        await view.setAction('action', hold);
    } else if (keyCodes.pause.includes(event.code)) {
        console.log('pause');
        await view.setAction('pause', hold);
    } else if (event.code == 'KeyQ')  {
        console.log('quit');
        await view.resetGame();
    }
}
