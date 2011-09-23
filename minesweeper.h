#ifndef __MINESWEEPER_H__
#define __MINESWEEPER_H__
#include <boost/multi_array.hpp>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include <string>
#include <time.h>

using namespace std;
using namespace boost;

class Minesweeper {
    private:
        // tuple<0>: true bomb, false no bomb
        // tuple<1>: Number of bombs
        // tuple<2>: true flagged, false not flagged.
        typedef multi_array<tuple<bool, short, bool>, 2> g_array;
        g_array board;
        short level;        // Difficulty
        short numBombs;     // Number of bombs
        short numFlagged;   // Number of bombs currently flagged.
        int maxX;
        int maxY;

        void generateLevel();

        /*********************************************************************
         *  Calculate the number of bombs surrounding location.              *
         *  \param int x                                                     *
         *  \param int y                                                     *
         *  \param vector<tuple<int,int>> ignore    List of ignore values to *
         *      prevent infinite loops.                                      *
         *  \note   Changes board[x][y]'s tuple<1> to reflect calculated     *
         *          value.                                                   *
         ********************************************************************/
        void calculateAdjBombs(int x, int y,vector<tuple<int,int>> *ignore);

        /*********************************************************************
         *  Check if x is a valid region in board.                           *
         *  \param int x                                                     *
         *  \return bool    true if valid, else false.                       *
         ********************************************************************/
        bool validX(int x);

        /*********************************************************************
         *  Check if y is a valid region in the board.                       *
         *  \param int y                                                     *
         *  \return bool    true if valid, else false.                       *
         ********************************************************************/
        bool validY(int y);

    public:
        /*********************************************************************
         *  Constructor                                                      *
         *  Levels:                                                          *
         *      1 - Beginner:        10 mines, 9x9 grid.                     *
         *      2 - Intermediate:    40 mines, 16x16 grid.                   *
         *      3 - Advanced:        99 mines, 16x30 grid.                   *
         *  \param short lvl    Level of difficulty                          *
         ********************************************************************/
        Minesweeper(short lvl);

        /**********************************************************************
         *  Check if there is a bomb in location (x,y)                        *
         *  \param int x                                                      *
         *  \param int y                                                      *
         *  \return bool    True if bomb, else false                          *
         *********************************************************************/
        bool check(int x, int y);
        
        /**********************************************************************
         *  Set the flag variable at specified region.                        *
         *  \param int x                                                      *
         *  \param int y                                                      *
         *  \return bool    true if last bomb flagged, else false             *
         *********************************************************************/
        bool flag(int x, int y);

        /**********************************************************************
         *  Return a string of the current board.                             *
         *  \return string                                                    *
         *********************************************************************/
        string print();

        /**********************************************************************
         *  Return a string of the current board showing the bomb locations.  *
         *  \return string                                                    *
         *********************************************************************/
        string revealBoard();

        /**********************************************************************
         *  Get max x value.                                                  *
         *  \return int                                                       *
         *********************************************************************/
        int getX();

        /**********************************************************************
         *  Get max y value.                                                  *
         *  \return int                                                       *
         *********************************************************************/
        int getY();
};

#endif
