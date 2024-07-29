#include <ncurses/ncurses.h>

void printCentered(WINDOW* win, int y, const char* text);
void printTable(WINDOW* win, int y, int x, char names[][14], int scores[], int size);
void saveScore(char name[], int score);
bool loadScores(char names[][14], int scores[], int& size);
int random(int min, int max);
int createMenu(const char* choices[], int n_choices);
void deleteScore();
void orderScore(char names[][14],int scores[],int size);
bool checkOrderArray(int array[],int size, bool ascending);