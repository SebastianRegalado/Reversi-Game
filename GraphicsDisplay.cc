#include "GraphicsDisplay.h"
#include <iostream>
#include "state.h"

using namespace std;

// Prints the colour of the Cell to the window
void GraphicsDisplay::notify(Subject<Info, State> &whoFrom) {
    Info I = whoFrom.getInfo();
    if(I.colour == Colour::Black) {
        w.fillRectangle(I.col * width, I.row * width, width, width);
    } else if (I.colour == Colour::White) {
        w.fillRectangle(I.col * width, I.row * width, width, width, 0);
    }
}

// Fills the initial window
GraphicsDisplay::GraphicsDisplay(int n) : n{n}, width{500/n} {
    for(int r = 0; r < n; ++r) {
        for(int c = 0; c < n; ++c) {
            w.fillRectangle(r * width, c * width, width, width, 4);
        }
    }
}

// Prints the winner on the window
void GraphicsDisplay::Winner(Colour c) {
    for(int r = 0; r < n; ++r) {
        for(int c = 0; c < n; ++c) {
            w.fillRectangle(r * width, c * width, width, width, 0);
        }
    }
    for(int i = 0; i < 50000; ++i) {
        if(c == Colour::Black) {
            w.drawString(200, 250, "Black Wins!");
        } else if (c == Colour::White) {
            w.drawString(200, 250, "White Wins!");
        } else {
            w.drawString(200, 250, "Tie!");
        }
    }
    for(int r = 0; r < n; ++r) {
        for(int c = 0; c < n; ++c) {
            w.fillRectangle(r * width, c * width, width, width, 0);
        }
    }
    for(int i = 0; i < 50000; ++i) {
        w.drawString(200, 250, "Bye, have a great day!");
    }
}
