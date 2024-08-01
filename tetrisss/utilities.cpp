#include <ncurses/ncurses.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include "headers/utilities.hpp"

using namespace std;

/*
function: printCentered
description: prints text centered in a specific window

@param WINDOW* win: window to print text in
@param int y: y position of the text
@param const char* text: text to print

@return void
*/
void printCentered(WINDOW* win, int y, const char* text) {
    int x = getmaxx(win) / 2 - strlen(text) / 2; //trova il centro dello schermo
    mvwprintw(win, y, x, text); //stampa al centro dello schermo il nome
}

/*
function: printTable
description: prints the names anc scores in a table format

@param WINDOW* win: window to print the table in
@param int y: y position of the table
@param int x: x position of the table
@param char names[][14]: array of names
@param int scores[]: array of scores
@param int size: size of the arrays

@return void
*/
void printTable(WINDOW* win, int y, int x, char names[][14], int scores[], int size) {
    //stampa al centro dello schermo
    if (x == -1) {
        x = getmaxx(win) / 2 - 16;
    }

    mvwprintw(win, y , x,  "         Name           Score   ");
    //scrive nomi e punteggi
    mvwprintw(win, y+1 , x, "--------------------------------");
    for (int i = 0; i < size; i++) { 
        char scorestring[6];
        snprintf(scorestring, 6, "%d", scores[i]);
        mvwprintw(win, (y+2)+(2*i), x, "|");
        mvwprintw(win, (y+2)+(2*i), x+2, names[i]);

        mvwprintw(win, (y+2)+(2*i), x+21, "|");
        mvwprintw(win, (y+2)+(2*i), x+23,scorestring);
        mvwprintw(win, (y+2)+(2*i), x+31,"|");
        mvwprintw(win, (y+2)+(2*i)+1 , x,  "--------------------------------");
    }
}

/*
function: loadScores
description: loads the scores from the leaderboard file into arrays

@param char names[][14]: array of names
@param int scores[]: array of scores
@param int& size: size of the arrays

@return void
*/
bool loadScores(char names[][14], int scores[], int& size) {
    ifstream file;
    bool fileExist=file.good();
    if(fileExist){
        file.open("leaderboard.txt");
        while (file >> names[size] >> scores[size]) {
            size++;
        }
        file.close();
    }
    return fileExist;
}

bool checkOrderArray(int array[],int size, bool ascending){
    int i=0;
    bool ordered=true;
    while(i<size-1 && ordered){
        if(ascending){
            if(array[i]>array[i+1]){
                ordered=false;
            }
        }else{
            if(array[i]<array[i+1]){
                ordered=false;
            }
        }
        i++;
    }
    return ordered;
}
/*
function: saveScore
description: sorts and saves the score to the leaderboard file 

@param char name[14]: name of the current player
@param int score: score of the current player

@return void
*/
void saveScore(char name[14], int score) {
    char new_names[6][14];
    int new_scores[6];
    int size = 0;

    bool fileExist=loadScores(new_names,new_scores, size);

    if(fileExist){
        //inserisce all'interno della lista il nuovo nome e punteggio
        strcpy(new_names[size], name);
        new_scores[size] = score;
        size++;


        //riordina gli elementi all'interno
        orderScore(new_names,new_scores,size);
        ofstream file;
        file.open("leaderboard.txt");
        //inserisce nome e punteggio all'interno del file
        for (int i = 0; i < size; i++) {
            file << new_names[i] << " " << new_scores[i] << endl;
        }

        file.close();
    }else{
        //crea un file e ci aggiunge le info della nuova partita
    }

}

/*
function: random
description: generates a random number between min and max

@param int min: minimum value
@param int max: maximum value

@return int: random number
*/
int random(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void orderScore(char names[][14],int scores[],int size){
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (scores[i] < scores[j]) {
                //punteggi
                int temp = scores[i];                    
                scores[i] = scores[j];
                scores[j] = temp;
                //nomi
                char tempname[14];
                strcpy(tempname, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], tempname);
            }
        }
    }
}
void deleteScore(){
    ofstream file("leaderboard.txt", ofstream::out | ofstream::trunc);
}
int createMenu(const char* choices[], int n_choices, int y,const char* titleText){
    int highlight = 0;
    
    while (1) {
        //creazione
        clear();
        int choice_y=y;
        if(strlen(titleText)!=0){
            attron(A_REVERSE);
            printCentered(stdscr,y,titleText);
            attroff(A_REVERSE);
            choice_y+=3;
        }

        for (int i = 0; i < n_choices; i++) {
            if (i == highlight) {
                attron(A_REVERSE);
            }
            printCentered(stdscr, i + choice_y , choices[i]);
            attroff(A_REVERSE);
        }

        //scelta 
        int choice=getch();
        
        switch (choice){
        case KEY_UP:
            highlight = (highlight - 1 + n_choices) % n_choices;
            break;
        case KEY_DOWN:
            highlight = (highlight + 1) % n_choices;
            break;
        default:
            break;
        }


        //output "enter"
        if (choice == 10) {
            return highlight;
        }
    }
}