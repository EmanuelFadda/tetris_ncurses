#include <ncurses/ncurses.h>
#include <cstring>
#include "headers/block.hpp"
#include "headers/utilities.hpp"

using namespace std;

const int X_SUB_BLOCK=1,Y_SUB_BLOCK=0;
const int SUB_BLOCK1=0,SUB_BLOCK2=1,SUB_BLOCK3=2,SUB_BLOCK4=3;
/*
function: Block
description: constructor for Block class (block values: 0 for empty, 1 for inactive, 2 for active)

@param int y: y position of the block
@param int x: x position of the block
@param int type: type of the block

@return Block: Block object
*/
Block::Block(int y, int x, int type) {
    this->x = x;
    this->y = y;

    switch (type){
    case 0:
            // [][]
            // [][]
            this->coords[SUB_BLOCK1][Y_SUB_BLOCK] = 0;
            this->coords[SUB_BLOCK1][X_SUB_BLOCK] = 0;

            this->coords[SUB_BLOCK2][Y_SUB_BLOCK] = 0;
            this->coords[SUB_BLOCK2][X_SUB_BLOCK] = 1;

            this->coords[SUB_BLOCK3][Y_SUB_BLOCK] = 1;
            this->coords[SUB_BLOCK3][X_SUB_BLOCK] = 0;

            this->coords[SUB_BLOCK4][Y_SUB_BLOCK] = 1;
            this->coords[SUB_BLOCK4][X_SUB_BLOCK] = 1;
            break;
        case 1:
            // [][][][]
            this->coords[SUB_BLOCK1][Y_SUB_BLOCK] = 0;
            this->coords[SUB_BLOCK1][X_SUB_BLOCK] = 0;

            this->coords[SUB_BLOCK2][Y_SUB_BLOCK] = 0;
            this->coords[SUB_BLOCK2][X_SUB_BLOCK] = 1;

            this->coords[SUB_BLOCK3][Y_SUB_BLOCK] = 0;
            this->coords[SUB_BLOCK3][X_SUB_BLOCK] = 2;

            this->coords[SUB_BLOCK4][Y_SUB_BLOCK] = 0;
            this->coords[SUB_BLOCK4][X_SUB_BLOCK] = 3;
            break;
        case 2:
            // [][]         ???
            //   [][]
            this->coords[SUB_BLOCK1][Y_SUB_BLOCK] = 0;
            this->coords[SUB_BLOCK1][X_SUB_BLOCK] = 0;

            this->coords[SUB_BLOCK2][Y_SUB_BLOCK] = 0;
            this->coords[SUB_BLOCK2][X_SUB_BLOCK] = 1;

            this->coords[SUB_BLOCK3][Y_SUB_BLOCK] = 1;
            this->coords[SUB_BLOCK3][X_SUB_BLOCK] = 1;

            this->coords[SUB_BLOCK4][Y_SUB_BLOCK] = 1;
            this->coords[SUB_BLOCK4][X_SUB_BLOCK] = 2;
            break;
        case 3:
            //   [][]
            // [][] 
            this->coords[SUB_BLOCK1][Y_SUB_BLOCK] = 0;
            this->coords[SUB_BLOCK1][X_SUB_BLOCK] = 1;

            this->coords[SUB_BLOCK2][X_SUB_BLOCK] = 0;
            this->coords[SUB_BLOCK2][Y_SUB_BLOCK] = 2;

            this->coords[SUB_BLOCK3][Y_SUB_BLOCK] = 1;
            this->coords[SUB_BLOCK3][X_SUB_BLOCK] = 0;
            
            this->coords[SUB_BLOCK4][Y_SUB_BLOCK] = 1;
            this->coords[SUB_BLOCK4][X_SUB_BLOCK] = 1;
            break;
        case 4:
            //   [] 
            // [][][]
            this->coords[SUB_BLOCK1][Y_SUB_BLOCK] = 0;
            this->coords[SUB_BLOCK1][X_SUB_BLOCK] = 1;

            this->coords[SUB_BLOCK2][Y_SUB_BLOCK] = 1;
            this->coords[SUB_BLOCK2][X_SUB_BLOCK] = 0;

            this->coords[SUB_BLOCK3][Y_SUB_BLOCK] = 1;
            this->coords[SUB_BLOCK3][X_SUB_BLOCK] = 1;

            this->coords[SUB_BLOCK4][Y_SUB_BLOCK] = 1;
            this->coords[SUB_BLOCK4][X_SUB_BLOCK] = 2;
            break;
        case 5:
            // []   
            // [][][] 
            this->coords[SUB_BLOCK1][Y_SUB_BLOCK] = 0;
            this->coords[SUB_BLOCK1][X_SUB_BLOCK] = 0;

            this->coords[SUB_BLOCK2][Y_SUB_BLOCK] = 1;
            this->coords[SUB_BLOCK2][X_SUB_BLOCK] = 0;

            this->coords[SUB_BLOCK3][Y_SUB_BLOCK] = 1;
            this->coords[SUB_BLOCK3][X_SUB_BLOCK] = 1;

            this->coords[SUB_BLOCK4][Y_SUB_BLOCK] = 1;
            this->coords[SUB_BLOCK4][X_SUB_BLOCK] = 2;
            break;
        case 6:
            //     []  ???
            // [][][]
            this->coords[SUB_BLOCK1][Y_SUB_BLOCK] = 0;
            this->coords[SUB_BLOCK1][X_SUB_BLOCK] = 2;

            this->coords[SUB_BLOCK2][Y_SUB_BLOCK] = 1;
            this->coords[SUB_BLOCK2][X_SUB_BLOCK] = 0;

            this->coords[SUB_BLOCK3][Y_SUB_BLOCK] = 1;
            this->coords[SUB_BLOCK3][X_SUB_BLOCK] = 1;

            this->coords[SUB_BLOCK4][Y_SUB_BLOCK] = 1;
            this->coords[SUB_BLOCK4][X_SUB_BLOCK] = 2;
            break;
    }

}

/*
function: getX
description: returns the x position of the block

@return int: x position of the block
*/
int Block::getX() {
    return this->x;
}

/*
function: getY
description: returns the y position of the block

@return int: y position of the block
*/
int Block::getY() {
    return this->y;
}

/*
function: add
description: adds the block to the board matrix with value 2

@param int board[][10]: the board matrix

@return void
*/
void Block::add(int board[][10]) {
    for (int i = 0; i < 4; i++) {
        board[this->y + this->coords[i][Y_SUB_BLOCK]][this->x + this->coords[i][X_SUB_BLOCK]] = 2;
    }
}

/*
function: rotate
description: rotates the block clockwise or counter-clockwise

@param int board[][10]: the board matrix
@param int direction: the direction to rotate the block (0 for left, 1 for right)

@return void
*/
void Block::rotate(int board[][10], int direction) {
    int temp[4][2];

    for (int i = 0; i < 4; i++) {
        board[this->y + this->coords[i][Y_SUB_BLOCK]][this->x + this->coords[i][X_SUB_BLOCK]] = 0;
    }

    for (int i = 0; i < 4; i++) {
        temp[i][Y_SUB_BLOCK] = this->coords[i][Y_SUB_BLOCK];
        temp[i][X_SUB_BLOCK] = this->coords[i][X_SUB_BLOCK];
    }

    if (this->checkCollision(board)) {
        for (int i = 0; i < 4; i++) {
            this->coords[i][Y_SUB_BLOCK] = temp[i][Y_SUB_BLOCK];
            this->coords[i][X_SUB_BLOCK] = temp[i][X_SUB_BLOCK];
        }
    } else {
        if (direction == 0) {
            // rotate left
            for (int i = 0; i < 4; i++) {
                this->coords[i][Y_SUB_BLOCK] = -temp[i][X_SUB_BLOCK];
                this->coords[i][X_SUB_BLOCK] = temp[i][Y_SUB_BLOCK];
            }
        } else if (direction == 1) {
            // rotate right
            for (int i = 0; i < 4; i++) {
                this->coords[i][Y_SUB_BLOCK] = temp[i][X_SUB_BLOCK];
                this->coords[i][X_SUB_BLOCK] = -temp[i][Y_SUB_BLOCK];
            }
        }
    }
}

/*
function: move
description: moves the block

@param int dy: change in y position
@param int dx: change in x position
@param int board[][10]: the board matrix

@return void
*/
void Block::move(int dy, int dx, int board[][10]) {
    for (int i = 0; i < 4; i++) {
        board[this->y + this->coords[i][Y_SUB_BLOCK]][this->x + this->coords[i][X_SUB_BLOCK]] = 0;
    }

    this->x += dx;
    this->y += dy;

    for (int i = 0; i < 4; i++) {
        board[this->y + this->coords[i][Y_SUB_BLOCK]][this->x + this->coords[i][X_SUB_BLOCK]] = 2;
    }
}

/*
function: checkCollision
description: checks if the block has collided with another (static) block in the board

@param int board[][10]: the board matrix

@return bool: true if the block has collided, false otherwise
*/
bool Block::checkCollision(int board[][10]) {
    for (int i = 0; i < 4; i++) {
        if (this->y + this->coords[i][Y_SUB_BLOCK] < 0 || this->y + this->coords[i][Y_SUB_BLOCK] >= 19) {
            return true;
        }
    }

    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 10; j++) {
            if (board[i][j] == 1) {
                if (board[i - 1][j] == 2 || board[i + 1][j] == 2) {
                    return true;
                }
            }
        }
    }

    return false;
}

/*
function: checkWall
description: checks if the block has collided with the walls of the board in order to prevent pacman effect

@param int board[][10]: the board matrix
@param int side: the side of the board to check (0 for left, 1 for right)

@return bool: true if the block has collided, false otherwise
*/
bool Block::checkWall(int board[][10], int side) {
    for (int i = 0; i < 4; i++) {
        if (side == 0) {
            // left wall
            if (this->x + this->coords[i][X_SUB_BLOCK] == 0) {
                return true;
            }
        } else if (side == 1) {
            // right wall
            if (this->x + this->coords[i][X_SUB_BLOCK] == 9) {
                return true;
            }
        }

    }

    return false;
}

/*
function: collided
description: adds the block to the board matrix changing the value from 2 to 1 (2 if the block is active, 1 if the block is inactive)

@param int board[][10]: the board matrix

@return void
*/
void Block::collided(int board[][10]) {
    for (int i = 0; i < 4; i++) {
        board[this->y + this->coords[i][Y_SUB_BLOCK]][this->x + this->coords[i][X_SUB_BLOCK]] = 1;
    }
}