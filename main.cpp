#include <boost/algorithm/string.hpp>
#include <ncurses.h>
#include <string>
#include <iostream>
#include "minesweeper.h"

#define BUFFER 1024
#define OFFSETX 4
using namespace std;

bool gameOver = false;

void startScreen() {
    initscr();
    clear();
    noecho();
    keypad(stdscr, 1);
    cbreak();
    mousemask(ALL_MOUSE_EVENTS, NULL);
}

void printBoard(Minesweeper *game) {
    auto maxX = game->getX();
    auto maxY = game->getY();
    
    auto offset = OFFSETX;
    for(auto i = 1; i <= maxX; ++i) {
        mvprintw(0, offset, "%d", i);
        offset += OFFSETX;
    }

    if(gameOver)
        mvprintw(1, 1, game->revealBoard().c_str());
    else 
        mvprintw(1, 1, game->print().c_str());
    
    offset = 1;
    for(auto i = 1; i <= maxY; ++i) {
        mvprintw(offset, 0, "%d", offset);
        offset += 1;
    }

}

void restoreScreen() {
    echo();
    endwin();
}

int main(int argv, char** argc) {
    auto level = 1; // Default is beginner
    if(argv == 2)
        level = atoi(argc[1]);

    startScreen();
    MEVENT event;

    Minesweeper *game = new Minesweeper(level);
    auto maxX = game->getX();
    auto maxY = game->getY();

    int ch;
    while(ch != 'q'){
        printBoard(game);
        switch((ch = getch())) {
            case KEY_MOUSE:
                if(getmouse(&event) == OK) {
                    auto mx = event.x-OFFSETX;
                    mx     /= OFFSETX;
                    mx++;
                    auto my = event.y;

                    if(event.bstate & BUTTON1_CLICKED) {

                        if((mx > 0 && mx <= maxX) && (my > 0 && my <= maxY)) {
                            if(game->check(mx-1,my-1)) {
                                gameOver = true;
                                mvprintw(18, 18, "Game Over");
                            }
                        }
                    }

                    // TODO: Check if Button3 is always going to be
                    // Right mouse
                    if(event.bstate & BUTTON3_CLICKED) {
                        if((mx > 0 && mx <= maxX) && (my > 0 && my <= maxY)) {
                            if(game->flag(mx-1,my-1)) {
                                gameOver = true;
                                mvprintw(18, 18, "Game Win");
                            }
                        }
                    }
                }
                break;
            case 'r':
                delete game;
                game     = new Minesweeper(level);
                gameOver = false;
                break;
        }
        refresh();
    }
    restoreScreen();
    delete game;
}

