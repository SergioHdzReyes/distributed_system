//
// Created by sergio on 04/11/21.
//

#include "gui_tools.h"

void draw_windows()
{
    //initscr();

    printw("COLS: %d, LINES: %d", COLS, LINES);
    printw("average: %d", (int)(LINES * 0.9));

    refresh();
    getch();
    //wgetch(history);

    // draw history
    history_box();

    // draw input text
    send_box();

    //endwin();
}

void history_box(void)
{
    limit_history = (int)(LINES * 0.90);

    history = newwin(limit_history, 0, 0, 0);
    if (history == NULL) {
        addstr("Unable to allocate memory for new window.");
        endwin();
        exit(1);
    }

    for (int y = 0; y < LINES; y++) {
        for (int x = 0; x < COLS; x++) {
            if ((y == 0 || y == limit_history-1) || (x == 0 || x == COLS-1)) {
                //printw("*");
                wmove(history, y, x);
                waddstr(history, "*");
            }
        }
    }
    wrefresh(history);
    getch();
}

void send_box(void)
{
    sending = newwin(LINES - limit_history, 0, limit_history, 0);
    if (sending == NULL) {
        addstr("Unable to allocate memory for new window.");
        endwin();
        exit(1);
    }

    for (int y = 0; y < LINES-limit_history; y++) {
        for (int x = 0; x < COLS; x++) {
            if ((y == 0 || y == LINES-limit_history-1) || (x == 0 || x == COLS-1)) {
                wmove(sending, y, x);
                waddstr(sending, "*");
            }
        }
    }

    // START FORM

    // END FORM

    wrefresh(sending);
    getch();
}

void rec_msg(char *str)
{
    strcpy(msgs.buff[msgs.counter], str);
    msgs.counter++;

    refresh_msgs();
}

void snd_msg(char *str)
{

}

void refresh_msgs()
{
    int aux = 0;

    for (int y = limit_history-2; y > 2; y--) {
        if (aux < msgs.counter) {
            wmove(history, y, 3);
            waddstr(history, msgs.buff[aux]);
        }
    }

    wrefresh(history);
}