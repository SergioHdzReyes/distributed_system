//
// Created by sergio on 04/11/21.
//

#ifndef DISTRIBUTED_SYSTEM_GUI_TOOLS_H
#define DISTRIBUTED_SYSTEM_GUI_TOOLS_H

#include <form.h>
//#include <ncurses.h>
#include <stdlib.h>
#include <string.h>


// Variables / Constantes
#define MAX_MSGS 100
WINDOW *history, *sending;
int limit_history;
//char buff[MAX_MSGS][100];

struct msgs_struct {
    char buff[MAX_MSGS][100];
    int counter;
} msgs;

// FORM
FIELD *field[2];
FORM *send_form;

// Funciones
void draw_windows(void);
void history_box(void);
void send_box(void);

void rec_msg(char *str);
void snd_msg(char *str);
void refresh_msgs(void);

#endif //DISTRIBUTED_SYSTEM_GUI_TOOLS_H
