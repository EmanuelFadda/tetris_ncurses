#include <ncurses/ncurses.h>
#include "headers/tutorial.hpp"
#include "headers/utilities.hpp"

/*
function: Tutorial
description: constructor for Tutorial class

@return Turorial:  Menu object
*/
Tutorial::Tutorial() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
}

void Tutorial::show(){
    clear();
    WINDOW *win = newwin(0, 0, 0, 0);
    refresh();


    printCentered(stdscr,1,"Hello");
    getch();
    hide();
}

void Tutorial::hide(){
   endwin();
}