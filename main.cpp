#include <boost/algorithm/string.hpp>
#include <iostream>
#include "minesweeper.h"

#define BUFFER 1024

using namespace std;

bool flag(Minesweeper *game, string inpt) {
    vector<string> strs;
    boost::split(strs, inpt, boost::is_any_of(" "));

    if(strs.size() != 3) { return false; }

    auto x = atoi(strs[1].c_str()) - 1;
    auto y = atoi(strs[2].c_str()) - 1;

    return game->flag(x,y);
}

bool check(Minesweeper *game, string inpt) {
    vector<string> strs;
    boost::split(strs, inpt, boost::is_any_of(" "));

    if(strs.size() != 3) { return false; }

    auto x = atoi(strs[1].c_str()) - 1;
    auto y = atoi(strs[2].c_str()) - 1;

    return game->check(x,y);
}

int main() {
    Minesweeper game(2);
    char input[BUFFER];
    char ch; 
    do {
        game.print();

        cout << "\n> ";
        cin.getline(input, BUFFER-1);

        auto inpt = string(input);
        if(inpt.substr(0,1) == "f") {
            if(flag(&game, inpt)) {
                cout << "\nGame Win\n" << endl;
                break;
            }
        } else if(inpt.substr(0,1) == "c") {
            if(check(&game, inpt)) {
                game.revealBoard();
                cout << "\nGame Over\n" << endl;
                break;
            }
        }
    } while(input[0] != 'q');
}

