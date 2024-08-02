#include <ncurses/ncurses.h>
#include "headers/game.hpp"
#include "headers/menu.hpp"
#include "headers/leaderboard.hpp"
#include "headers/tutorial.hpp"
#include "headers/utilities.hpp"
using namespace std;

int main() {

    Menu menu;
    Game game(HEIGHT_GAME, WIDTH_GAME, STARTY_GAME, STARTX_GAME);
    Leaderboard leaderboard;
    Tutorial tutorial;
    menu.logo();


    int choice;
    while ((choice = menu.show()) != 3) {
        if (choice == 0) {
            game.running = true;
            game.getName();
            game.show();
        } else if (choice == 1) {
            leaderboard.show();
        }else if(choice == 2){
            tutorial.show();
        }
    }

    
    menu.hide();
    game.hide();
    leaderboard.hide();
    tutorial.hide();
    return 0;
}

// TODO
// fix Block::rotate(), pacman effect and add clockwise/counter-clockwise rotation
// implement Game::resume() -> optional feature
// add time and lines cleared to Game