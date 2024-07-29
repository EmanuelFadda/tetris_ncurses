#include <ncurses/ncurses.h>
#include "headers/game.hpp"
#include "headers/menu.hpp"
#include "headers/leaderboard.hpp"

using namespace std;

//costanti di gioco
const int HEIGHT_GAME=22;
const int WIDTH_GAME=22;
const int STARTY_GAME=1;
const int STARTX_GAME=-1;

int main() {

    Menu menu;
    Game game(HEIGHT_GAME, WIDTH_GAME, STARTY_GAME, STARTX_GAME);
    Leaderboard leaderboard;

    menu.logo();


    int choice;
    while ((choice = menu.show()) != 2) {
        if (choice == 0) {
            game.running = true;
            game.getName();
            game.show();
        } else if (choice == 1) {
            leaderboard.show();
        }
    }

    
    menu.hide();
    game.hide();
    leaderboard.hide();

    return 0;
}

// TODO
// fix Block::rotate(), pacman effect and add clockwise/counter-clockwise rotation
// implement Game::gameOver() -> reset game
// implement Game::pause() -> optional feature
// implement Game::resume() -> optional feature
// modify design of Game grid
// try solve delay issue
// add time and lines cleared to Game
// implement tutorial