#include <ncurses/ncurses.h>
#include <cstring>
#include "headers/game.hpp"
#include "headers/block.hpp"
#include "headers/utilities.hpp"
#include "headers/tutorial.hpp"
using namespace std;

//char used to write a board
const char ASCII_TOP_BORDER = ' ';
const char ASCII_BOTTOM_BORDER = '=';
const char ASCII_LEFT_BORDER = '<';
const char ASCII_RIGHT_BORDER = '>';
const char ASCII_CORNER_BORDER = '+';

//int code left,right border
const int RIGHT_BORDER=1,LEFT_BORDER=0;

const int n_choices=3;
const char* choices[n_choices]={"[[ Continue ]]","[[ Commands ]]", "[[ Exit ]]"};
int choice;


/*
function: Game
description: constructor for Game class

@param int height: height of the game window
@param int width: width of the game window
@param int starty: starting y position of the game window
@param int startx: starting x position of the game window

@return Game: Game object
*/
Game::Game(int height, int width, int starty, int startx) {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    this->score = 0;
    this->height = height;
    this->width = width;
    this->starty = starty;
    this->startx = startx == - 1 ? getmaxx(stdscr) / 2 - width / 2 : startx;
}

/*
function: drawBoard
description: draws the game board, blocks are represented by []

@param WINDOW* win: window to draw the board in

@return void
*/
void Game::drawBoard(WINDOW* win) {
    for (int i = 1; i < 21; i++) {
        for (int j = 1; j < 21; j += 2) {
            if (this->board[i-1][(j-1)/2] == 2 || this->board[i-1][(j-1)/2] == 1){
                mvwprintw(win, i, j, "[]");
            } else {
                mvwprintw(win, i, j, "  ");
            }
        }
    }
}   

/*
function: getName
description: creates a prompt for the user to enter their name

@return void
*/
void Game::getName() {
    clear();
    echo();
    curs_set(1);

    mvprintw(getmaxy(stdscr) / 2 - 2, getmaxx(stdscr) / 2 - 9, "Enter your name: ");

    getstr(this->name);

    noecho();
    curs_set(0);
}

/*
function: eraseLines
description: erases lines that are full and updates the score

@param int board[][10]: game board

@return void
*/
void Game::eraseLines(int board[][10]) {
    for (int i = 0; i < 20; i++) {
        bool full = true;

        // check if the line is full
        for (int j = 0; j < 10; j++) {
            if (board[i][j] == 0) {
                full = false;
                break;
            }
        }

        // if the line is full, erase it and move all the lines above it down
        if (full) {
            for (int j = i; j > 0; j--) {
                for (int k = 0; k < 10; k++) {
                    board[j][k] = board[j-1][k];
                }
            }

            this->score += 100;
        }
    }
}

/*
function: gameOver
description: displays the game over screen and saves the user's score

@return void
*/
void Game::gameOver(bool wasPaused) {
    clear();

    this->score = 0;
    this->running = true;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            this->board[i][j] = 0;
        }
    }
    printCentered(stdscr, getmaxy(stdscr) / 2, "Game Over!");

    if(!wasPaused){
        saveScore(this->name, this->score);
        mvprintw(getmaxy(stdscr) / 2 + 1, getmaxx(stdscr) / 2 - 9, "Your score: %d", this->score);
    }
    printCentered(stdscr, getmaxy(stdscr) / 2 + 3, "Press any key to continue...");
    getch();
}


/*
function: show
description: displays the game screen and handles user input

@return void
*/
void Game::show() {
    clear();
    
    Block block = Block(0, 4, random(0, 6));
    block.add(this->board);
    int rand = random(0, 6);
    Block next = Block(0, 4, rand);

    WINDOW* stats = newwin(12, getmaxx(stdscr) / 2 - width / 2 - 1, starty, getmaxx(stdscr) / 5);
    refresh();
    
    mvwprintw(stats, 0, 0, "Name: %s", this->name);
    mvwprintw(stats, 1, 0, "Score: %d", this->score);
    mvwprintw(stats, 4, 0, "Next:");


    for (int i = 0; i < 4; i++){
        mvwprintw(stats, 6 + next.coords[i][0], 2 + next.coords[i][1] * 2, "[]");
    }
    
    wrefresh(stats);

    WINDOW* game = newwin(height, width, starty, startx);
    refresh();
    

    wborder(game, ASCII_LEFT_BORDER, ASCII_RIGHT_BORDER, ASCII_TOP_BORDER, ASCII_BOTTOM_BORDER, ASCII_CORNER_BORDER, ASCII_CORNER_BORDER, ASCII_CORNER_BORDER, ASCII_CORNER_BORDER);

    wrefresh(game);

    char c;
    timeout(100);
    while (running){
        if (block.checkCollision(this->board)) {
            // if the block has collided with another block and is at the top of the board, the game is over
            if (block.getY() == 0) {
                this->gameOver(false);
            }

            // change blocks' values from 2 to 1 (from active to inactive)
            block.collided(this->board);

            timeout(40);
            this->eraseLines(this->board);

            // erase the previous block from stats window
            for (int i = 0; i < 4; i++) {
                mvwprintw(stats, 6 + next.coords[i][0], 2 + next.coords[i][1] * 2, "  ");
            }

            block = next;
            block.add(this->board);
            rand = random(0, 6);
            next = Block(0, 4, rand);

            mvwprintw(stats, 1, 0, "Score: %d", this->score);
            
            // display the next block
            for (int i = 0; i < 4; i++){
                mvwprintw(stats, 6 + next.coords[i][0], 2 + next.coords[i][1] * 2, "[]");
            }

            wrefresh(stats);
        }

        this->drawBoard(game);

        timeout(800);

        int oldCords[4][2]; // store the old coordinates of the block before rotation for collision detection
        // input handling
        // a: move left
        // d: move right
        // s: move down
        // m: quit
        // r: rotate left
        // q: rotate right
        c = getch();
        switch (c) {
            case 'a':
                if (!block.checkWall(this->board, LEFT_BORDER)) block.move(1, -1, this->board);
                break;
            case 'd':
                if (!block.checkWall(this->board, RIGHT_BORDER)) block.move(1, 1, this->board);
                break;
            case 's':
                block.move(1, 0, this->board);
                break;
            case 'm':
                timeout(-1);
                do{
                    choice=createMenu(choices,n_choices,5,"  PAUSE  ");
                    if(choice==1){
                        clear();
                        int y=11;
                        
                        attron(A_REVERSE);
                        printCentered(stdscr,y,"Commands");
                        attroff(A_REVERSE);
                        
                        mvwprintw(stdscr,y,28,"[a]: move left");
                        mvwprintw(stdscr,y,28+28,"[d]: move right");
                        mvwprintw(stdscr,y,28+50,"[s]: move down");
                        mvwprintw(stdscr,y+2,28,"[q]: rotate right");
                        mvwprintw(stdscr,y+2,28+28,"[r]: rotate left");
                        mvwprintw(stdscr,y+2,28+50,"[m]: quit");

                        printCentered(stdscr,y+15,"Press any key to turn back");
                        
                        
                        char h=getch();

                        // parte automaticamente ???
                    }else if(choice==2){
                        gameOver(true);
                        this->running=false;
                    }
                }while(choice!=0 && running);

                if(running){
                    //continue the game
                    wborder(game, ASCII_LEFT_BORDER, ASCII_RIGHT_BORDER, ASCII_TOP_BORDER, ASCII_BOTTOM_BORDER, ASCII_CORNER_BORDER, ASCII_CORNER_BORDER, ASCII_CORNER_BORDER, ASCII_CORNER_BORDER);
                    wrefresh(game);
                }
                
                break;
            case 'r':
                for (int i = 0; i < 4; i++) {
                    oldCords[i][0] = block.coords[i][0];
                    oldCords[i][1] = block.coords[i][1];
                }

                block.rotate(this->board, 1);

                if (block.checkCollision(this->board)) {
                    for (int i = 0; i < 4; i++) {
                        block.coords[i][0] = oldCords[i][0];
                        block.coords[i][1] = oldCords[i][1];
                    }
                }
                break;
            case 'q':
                for (int i = 0; i < 4; i++) {
                    oldCords[i][0] = block.coords[i][0];
                    oldCords[i][1] = block.coords[i][1];
                }

                block.rotate(this->board, 0);

                if (block.checkCollision(this->board)) {
                    for (int i = 0; i < 4; i++) {
                        block.coords[i][0] = oldCords[i][0];
                        block.coords[i][1] = oldCords[i][1];
                    }
                }
                break;
            default:
                block.move(1, 0, this->board);
                break;
        }
        wrefresh(game);
    }
}

/*
function: hide
description: ends game window

@return void
*/
void Game::hide() {
    endwin();
}