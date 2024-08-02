#include <ncurses/ncurses.h>
#include "../headers/menu.hpp"
#include "../headers/game.hpp"
#include "../headers/utilities.hpp"
#include <string>


/*
function: Menu
description: constructor for Menu class

@return Menu: Menu object
*/
Menu::Menu() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
}

/*
function: logo
description: displays the game logo

@return void
*/
void Menu::logo() {
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(5, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    printCentered(stdscr, 8 , " _____ _____ _____ ____  ___ ____  ");
    attron(COLOR_PAIR(2));
    printCentered(stdscr, 9 , "|_   _| ____|_   _|  _ \\|_ _/ ___| ");
    attron(COLOR_PAIR(3));
    printCentered(stdscr, 10, "  | | |  _|   | | | |_) || |\\___ \\ ");
    attron(COLOR_PAIR(4));
    printCentered(stdscr, 11, "  | | | |___  | | |  _ < | | ___) |");
    attron(COLOR_PAIR(5));
    printCentered(stdscr, 12, "  |_| |_____| |_| |_| \\_\\___|____/ ");
    attroff(COLOR_PAIR(1));
    timeout(5000);

    printCentered(stdscr, 20, "Press any key to show the menu' ...");
    timeout(-1);
    getch();
}

/*
function: show
description: displays the menu and handles user input

@return int: choice
*/
int Menu::show() {
    WINDOW* win = newwin(0, 0, 0, 0);

    refresh();
    int n_choices=4;
    const char* choices[n_choices] = {"[[ Play ]]", "[[Leaderboard]]","[[ Tutorial ]]", "[[ Exit ]]"};
    int choice=createMenu(choices,n_choices,10,"  MENU'  ");
    return choice;

}

/*
function: hide
description: ends menu window

@return void
*/
void Menu::hide() {
    endwin();
};