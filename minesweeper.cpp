#include "minesweeper.h"

Minesweeper::Minesweeper(short lvl) {
    level = lvl;

    switch(lvl) {
        case 1:
            maxX = 9;
            maxY = 9;
            break;
        case 2:
            maxX = 16;
            maxY = 16;
            break;
        case 3:
            maxX = 30;
            maxY = 16;
            break;
        default:
            maxX = 9;
            maxY = 9;
    }
    
    board.resize(extents[maxY][maxX]);
    generateLevel();
}

void Minesweeper::generateLevel() {
    typedef g_array::index index;
    for(index i = 0; i != board.size(); i++) {
        for(index j = 0; j != board[i].size(); j++) {
            board[i][j] = tuple<bool, short, bool>(false, -1, false);
        }
    }

    switch(level) {
        case 1:
            numBombs = 10;
            break;
        case 2:
            numBombs = 40;
            break;
        case 3:
            numBombs = 99;
            break;
        default:
            numBombs = 10;
    }

    srand(time(NULL));
    auto i = numBombs;
    while(i > 0) {
        auto x = rand() % maxX;
        auto y = rand() % maxY;

        if(get<0>(board[y][x]) == false) {
            get<0>(board[y][x]) = true;

            i--;
        }
    }
}

void Minesweeper::calculateAdjBombs(int x, int y, 
  vector<tuple<int, int>> *ignore) {
    if(!validX(x) || !validY(y)) { return; }
    
    typedef tuple<int, int> tp;
    array<tp, 8> adjacents = { tp(x-1, y-1), tp(x, y-1), tp(x+1, y-1),
        tp(x-1, y), tp(x+1, y), tp(x-1, y+1), tp(x, y+1), tp(x+1, y+1) };

    for(auto i = begin(adjacents); i != end(adjacents); ++i) {
        // Ignore Flagged regions.
        auto fx = get<0>(*i);
        auto fy = get<1>(*i);

        if(validX(fx) && validY(fy)) {
            if(get<2>(board[fy][fx])) { 
                ignore->push_back(tuple<int,int>(fx,fy));
            }
        }

        // Check ignore vector
        for(auto j = ignore->begin(); j != ignore->end(); ++j) {
            if(get<0>(*i) == get<0>(*j) && get<1>(*i) == get<1>(*j)) {
                get<0>(*i) = -1;
                get<1>(*i) = -1;
            }
        }
    }
    
    auto num = 0;
    for(auto i = begin(adjacents); i != end(adjacents); ++i) {
        auto xi = get<0>(*i);
        auto yi = get<1>(*i);
        if(validX(xi) && validY(yi)) {
            if(get<0>(board[yi][xi])) { num++; }
        }
    }
    
    get<1>(board[y][x]) = num;
    if(num == 0) {
        ignore->push_back(tp(x,y));
        
        for(auto i = begin(adjacents); i != end(adjacents); ++i) {
            calculateAdjBombs(get<0>(*i), get<1>(*i),ignore);
        }
    }
}

void Minesweeper::flag(int x, int y) {
    if(!validX(x) || !validY(y)) { return; }
    get<2>(board[y][x]) = !get<2>(board[y][x]);
}

bool Minesweeper::check(int x, int y) {
    if(!validX(x) || !validY(y))  { return false; }
    if(get<2>(board[y][x])) { return false; }
    
    auto bomb = get<0>(board[y][x]);
    if(bomb == 1) {
        return true;
    } else {
        vector<tuple<int,int>> *ignore = new vector<tuple<int,int>>();
        calculateAdjBombs(x,y,ignore);
        delete ignore;

        return false;
    }
}

inline bool Minesweeper::validX(int x) {
    if(x >= 0 && x < maxX) {
        return true;
    }

    return false;
}

inline bool Minesweeper::validY(int y) {
    if(y >= 0 && y < maxY) {
        return true;
    }

    return false;
}

void Minesweeper::print() {
    auto k = 1;
    cout << "    ";
    for(k; k != maxX; ++k) {
        cout << " " << k << " ";
    }
    cout << endl;

    k = 1;
    auto i = board.begin();
    for(; i != board.end(); ++i) {
        if(k < 10)
            cout << "  " << k << " ";
        else
            cout << " " << k << " ";

        auto j = (*i).begin();
        for(; j != (*i).end(); ++j) {
            if(get<2>(*j)) {
                cout << " f ";
            } else {
                if(get<1>(*j) == -1) {
                    cout << " . ";
                } else {
                    cout << " " << get<1>(*j) << " ";
                }
            }
        }
        k++;
        cout << endl;
    }
}

void Minesweeper::revealBoard() {
    auto k = 1;
    cout << "    ";
    for(k; k != maxX; ++k) {
        cout << " " << k << " ";
    }
    cout << endl;

    k = 1;
    auto i = board.begin();
    for(; i != board.end(); ++i) {
        if(k < 10)
            cout << "  " << k << " ";
        else
            cout << " " << k << " ";

        auto j = (*i).begin();
        for(; j != (*i).end(); ++j) {
            if(get<0>(*j)) {
                cout << " x ";
            } else {
                if(get<2>(*j)) {
                    cout << " f ";
                } else {
                    if(get<1>(*j) == -1) {
                        cout << " . ";
                    } else {
                        cout << " " << get<1>(*j) << " ";
                     }
                }
            }
        }
        k++;
        cout << endl;
    }
}
