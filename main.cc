#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "grid.h"
#include "state.h"
using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;

  // Add code here
  try {
  while (true) {
    cin >> cmd;
    if (cmd == "new") {
      int n;
      cin >> n;
      // Add code here
      g.init(n);
    }
    else if (cmd == "play") {
      int r = 0, c = 0;
      cin >> r >> c;
      // Add code here
      g.setPiece(r, c, Colour::NoColour);
    }
    if(g.isFull()) {
      Colour w = g.whoWon();
      if(w == Colour::Black) {
        cout << "Black Wins!";
      } else if(w == Colour::White) {
        cout << "White Wins!";
      } else {
        cout << "Tie!";
      }
      cout << endl;
      break;
    }
  }
  }
  catch (ios::failure &) {}  // Any I/O failure quits
}
