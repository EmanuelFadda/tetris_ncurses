#include <ncurses/ncurses.h>
#include <cstring>

void printCentered(WINDOW* win, int y, const char* text);
void printTable(WINDOW* win, int y, int x, char names[][14], int scores[], int size);
void saveScore(char name[], int score);
bool loadScores(char names[][14], int scores[], int& size);
int random(int min, int max);
int createMenu(const char* choices[], int n_choices, int y,const char* titleText);
void deleteScore();
void orderScore(char names[][14],int scores[],int size);
bool checkOrderArray(int array[],int size, bool ascending);


const int X_SUB_BLOCK=1,Y_SUB_BLOCK=0;
const int SUB_BLOCK1=0,SUB_BLOCK2=1,SUB_BLOCK3=2,SUB_BLOCK4=3;
const int N_SUB_BLOCKS=4;

const int MAX_TOP_PLAYER=5;

const int HEIGHT_GAME=22;
const int WIDTH_GAME=22;
const int STARTY_GAME=1;
const int STARTX_GAME=-1;

const char ASCII_TOP_BORDER = ' ';
const char ASCII_BOTTOM_BORDER = '=';
const char ASCII_LEFT_BORDER = '<';
const char ASCII_RIGHT_BORDER = '>';
const char ASCII_CORNER_BORDER = '+';
const int RIGHT_BORDER=1,LEFT_BORDER=0;

const char URL_FILE_SCORES[] = "leaderboard.txt";