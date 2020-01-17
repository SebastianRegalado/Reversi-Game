#include <iostream>
#include "state.h"
#include "subject.h"
#include "observer.h"
#include "info.h"
#include "cell.h"

using namespace std;

// sameDirection(r1, c1, r2, c2, d) determines whethere the Cell in row r2
//   and column c2 is in the Direction d from the Cell in row r1 and column c1
bool sameDirection(size_t r1, size_t c1, size_t r2, size_t c2, Direction d)  {
    if(r1 > r2 && c1 > c2 && d == Direction::NE) { return true; }
    if(r1 == r2 && c1 > c2 && d == Direction::E) { return true; }
    if(r1 < r2 && c1 > c2 && d == Direction::SE) { return true; }
    if(r1 > r2 && c1 == c2 && d == Direction::N) { return true; }
    if(r1 < r2 && c1 == c2 && d == Direction::S) { return true; }
    if(r1 > r2 && c1 < c2 && d == Direction::NW) { return true; }
    if(r1 == r2 && c1 < c2 && d == Direction::W) { return true; } 
    if(r1 < r2 && c1 < c2 && d == Direction::SW) { return true; }
    return false; 
}

// oppositeDirection(r1, c1, r2, c2, d) determines whethere the Cell 
//   in row r2 and column c2 is in the Direction opposite to d from 
//   the Cell in row r1 and column c1
bool oppositeDirection(size_t r1, size_t c1, size_t r2, size_t c2, Direction d) {
    return sameDirection(r2, c2, r1, c1, d);
}

// Creates a Cell in the row r and column c
Cell::Cell(size_t r, size_t c) : r{r}, c{c} {}

// Place a piece of given colour here.
void Cell::setPiece(Colour colour) {
    if(this->colour == Colour::NoColour) {
        this->colour = colour;
        setState(State{StateType::NewPiece, colour, Direction::N});
        notifyObservers();
    }
}    

// Toggles my colour.
void Cell::toggle() {
    if(colour == Colour::Black) colour = Colour::White;
    else if(colour == Colour::White) colour = Colour::Black;
}

void Cell::notify(Subject<Info, State> &whoFrom) {
    Info I1 = whoFrom.getInfo();
    Info I2 = getInfo();
    State s = whoFrom.getState();

    if(s.type == StateType::NewPiece) {
        if(I2.colour == I1.colour || I2.colour == Colour::NoColour) return;
        Direction d;
        if(I1.row > I2.row && I1.col > I2.col) d = Direction::NE;
        if(I1.row == I2.row && I1.col > I2.col) d = Direction::E;
        if(I1.row < I2.row && I1.col > I2.col) d = Direction::SE;
        if(I1.row > I2.row && I1.col == I2.col) d = Direction::N;
        if(I1.row < I2.row && I1.col == I2.col) d = Direction::S;
        if(I1.row > I2.row && I1.col < I2.col) d = Direction::NW;
        if(I1.row == I2.row && I1.col < I2.col) d = Direction::W;
        if(I1.row < I2.row && I1.col < I2.col) d = Direction::SW;
        setState(State{StateType::Relay, s.colour, d});
        notifyObservers();
    } else if (s.type == StateType::Relay && I2.colour == Colour::NoColour) {
        if(sameDirection(I1.row, I1.col, I2.row, I2.col, s.direction)) {
            setState(State{StateType::Reply, Colour::NoColour, s.direction});
            notifyObservers();
        }
    } else if (s.type == StateType::Relay) {
        if(sameDirection(I1.row, I1.col, I2.row, I2.col, s.direction)) {
            if(s.colour != I2.colour) {
                setState(State{StateType::Relay, s.colour, s.direction});
            } else {
                setState(State{StateType::Reply, s.colour, s.direction});
            }
            notifyObservers();
        }
    } else if (I2.colour == Colour::NoColour && s.type == StateType::Reply) {
        // In this case nothing needs to be done!
    } else {
        State s2 = getState();
        if (s2.type != StateType::Relay) return;
        if(oppositeDirection(I1.row, I1.col, I2.row, I2.col, s.direction)) {
            if (s.colour == Colour::NoColour) {
                setState(State{StateType::Reply, colour, s2.direction});
            } else if (s2.type == StateType::Relay) {
                colour = s.colour;
                setState(State{StateType::Reply, s.colour, s.direction});
            }
            notifyObservers();
        }
    }
}// My neighbours will call this when they've changed state

Info Cell::getInfo() const {
    return Info{r, c, colour};
}
