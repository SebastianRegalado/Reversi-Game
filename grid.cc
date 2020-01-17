#include "grid.h"
#include "cell.h"
#include "state.h"
#include "info.h"
#include <iostream>

using namespace std;

Grid::~Grid() {delete ob;}

void Grid::setObserver(Observer<Info, State> *ob) {
    this->ob = ob;
}

// Determines whether theGrid is full
bool Grid::isFull() const { // Is the game over, i.e., is the grid full?
    size_t n = theGrid.size();
    if(n == 0) return false;
    for (size_t r = 0; r < n; ++r) {
        for (size_t c = 0; c < n; ++c) {
            Info I = theGrid[r][c].getInfo();
            if (I.colour == Colour::NoColour) return false;    
        }
    }
    return true;
} 


// Determines who won the game
Colour Grid::whoWon() const { // Who has more pieces when the board is full?
    int black = 0, white = 0;
    size_t n = theGrid.size();

    for (size_t r = 0; r < n; ++r) {
        for (size_t c = 0; c < n; ++c) {
            Info I = theGrid[r][c].getInfo();
            if (I.colour == Colour::Black) ++black;
            else ++white;    
        }
    }
    if(black > white) return Colour::Black;
    if(white > black) return Colour::White;
    return Colour::NoColour;
} 

// Creates a new grid of size n
void Grid::init(size_t n) { // Sets up an n x n grid.  Clears old grid, if necessary.
    theGrid.clear();

    if (n % 2 == 1 || n < 4) return;

    for(size_t r = 0; r < n; ++r) {
        std::vector<Cell> v;
        for(size_t c = 0; c < n; ++c) {
            v.emplace_back(Cell(r, c));
        }
        theGrid.emplace_back(v);
    }
    BlackTurn = true;

    for(size_t r = 0; r < n; ++r) {
        for(size_t c = 0; c < n; ++c) { 
            if(r > 0) theGrid[r][c].attach(&theGrid[r-1][c]);
            if(r < n - 1) theGrid[r][c].attach(&theGrid[r+1][c]);
            if(c > 0) theGrid[r][c].attach(&theGrid[r][c-1]);
            if(c < n - 1) theGrid[r][c].attach(&theGrid[r][c+1]);
            if(r > 0 && c > 0) theGrid[r][c].attach(&theGrid[r-1][c-1]);
            if(r < n - 1 && c < n - 1) theGrid[r][c].attach(&theGrid[r+1][c+1]);
            if(r > 0 && c < n - 1) theGrid[r][c].attach(&theGrid[r-1][c+1]);
            if(r < n - 1  && c > 0) theGrid[r][c].attach(&theGrid[r+1][c-1]);
        }
    }

    theGrid[n/2-1][n/2-1].setPiece(Colour::Black);
    theGrid[n/2-1][n/2].setPiece(Colour::White);
    theGrid[n/2][n/2].setPiece(Colour::Black);
    theGrid[n/2][n/2-1].setPiece(Colour::White);

    cout << *this;
}

// Plays piece of Colour colour at row r, col c, if possible.
void Grid::setPiece(size_t r, size_t c, Colour colour) {
    
    size_t n = theGrid.size();

    if(r >= n || c >= n) return;

    Info I = theGrid[r][c].getInfo();
    if(I.colour != Colour::NoColour) return;
    if (BlackTurn) {
        theGrid[r][c].setPiece(Colour::Black);
        BlackTurn = !BlackTurn;
    } else {
        theGrid[r][c].setPiece(Colour::White);
        BlackTurn = !BlackTurn;
    }
    cout << *this;
}  

// Flips piece at row r, col c.
void Grid::toggle(size_t r, size_t c){
    theGrid[r][c].toggle();
} 

std::ostream &operator<<(std::ostream &out, const Grid &g) {
    size_t n = g.theGrid.size();
    for(size_t r = 0; r < n; ++r) {
        for(size_t c = 0; c < n; ++c) {
            Info I = g.theGrid[r][c].getInfo();
            if (I.colour == Colour::Black) { out << "B"; } 
            else if (I.colour == Colour::White) { out << "W"; }
            else { out << "-"; }
        }
        out << endl;
    }
    return out;
}
