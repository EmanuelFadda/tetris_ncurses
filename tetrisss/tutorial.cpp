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
    int y=1;

    attron(A_REVERSE);
    printCentered(stdscr,y,"Tutorial");
    attroff(A_REVERSE);
    mvwprintw(stdscr,y+3,5,"The aim of the game is to complete horizontal rows of blocks to accumulate points and keep the screen free");
    mvwprintw(stdscr,y+4,5,"of accumulated tetrominoes.");

    int y2=y+7;
    
    attron(A_REVERSE);
    printCentered(stdscr,y2,"Commands");
    attroff(A_REVERSE);
    
    mvwprintw(stdscr,y2+3,28,"[a]: move left");
    mvwprintw(stdscr,y2+3,28+28,"[d]: move right");
    mvwprintw(stdscr,y2+3,28+50,"[s]: move down");
    mvwprintw(stdscr,y2+5,28,"[q]: rotate right");
    mvwprintw(stdscr,y2+5,28+28,"[r]: rotate left");
    mvwprintw(stdscr,y2+5,28+50,"[m]: quit");

    printCentered(stdscr,y2+5+10,"Press any key to turn back");
    getch();
    hide();
}

void Tutorial::hide(){
   endwin();
}