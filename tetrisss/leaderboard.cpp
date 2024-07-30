#include <ncurses/ncurses.h>
#include <cstring>
#include <fstream>
#include "headers/leaderboard.hpp"
#include "headers/utilities.hpp"


const int MAX_TOP_PLAYER=5;

/*
function: Leaderboard
description: constructor for Leaderboard class

@return Leaderboard: Leaderboard object
*/
Leaderboard::Leaderboard() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
};

/*
function: show
description: displays the leaderboard

@return void
*/
void Leaderboard::show() {
    clear();

    WINDOW *win = newwin(0, 0, 0, 0);
    refresh();

    char* table;

    
   
    char names[MAX_TOP_PLAYER][14];  
    int scores[MAX_TOP_PLAYER];
    int size = 0;

    //carica negli array i dati del file,
    //e restituisce il numero di player nel file

    // 
    bool fileExist=loadScores(names, scores, size); 

    if(!fileExist || size==0){
        
        printCentered(stdscr,1,"There is no scores about your play saved in this device");
        printCentered(stdscr,2,"Play at least one game and turn back :)");
        
        timeout(-1);
        getch();

    }else{
        if (!checkOrderArray(scores,size,false)){
            orderScore(names,scores,size);
            deleteScore();
            int i=0;
            //corregge l'ordine nel file dei punteggi
            while(i<size){
                saveScore(names[i],scores[i]);
                i++;
            }
        }
        printCentered(stdscr, 1, "Leaderboard");
        printTable(stdscr, 3, -1, names, scores, size);
        attron(A_REVERSE);
        attroff(A_REVERSE);
        //attende fino a un output
        timeout(-1);
        char c=getch();

        // da creare menù
        if(c=='d'|| c=='D'){
            resetLeaderboard();
        }
    }
   
}


/*
function: hide
description: ends leaderboard window

@return void
*/
void Leaderboard::hide() {
    endwin();
}

void Leaderboard::resetLeaderboard(){
    clear();


    int n_choices=2;
    const char* choices[n_choices]={"CONFIRM", "Exit"};
    int choice=createMenu(choices,n_choices);
    
    if(choice==0){
        deleteScore();
    }
    show();
    
}