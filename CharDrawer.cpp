#include "CharDrawer.h"
using std::cin; using std::cout; using std::endl;


int CharDrawer::nLastCol() const;
int CharDrawer::nLastRow() const;
/* Format of printing:
  12345.789111
           012
1 xxxxxxxxxxxx
2 xxxxxxxxxxxx
. xxxxxxxxxxxx
4 xxxxxxxxxxxx
5 xxxxxxxxxxxx
6 xxxxxxxxxxxx
7 xxxxxxxxxxxx
8 xxxxxxxxxxxx
9 xxxxxxxxxxxx
10xxxxxxxxxxxx
11xxxxxxxxxxxx

no, never mind, this is better:
    .   
 xxxxxxx
.xxxxxxx
 xxxxxxx

really lame, but so what.
honestly, this is actually more effort than I want to put into it....
*/
void CharDrawer::print(bool bDrawingMode = false) const { //prints. we call this after every change.
  //print top row with a '.' so we know where we are

  //print each row.
  for(int i = 0; i < nLastCol; ++i) {
    //first, print the '.' that shows where we are
    //now print the row.
    FINISH
    if(bDrawingMode && i == nRow) {//also draw '.' as the cursor
    FINISH
    }
    else { //just draw the row
FINISH
    }
  }
}


void CharDrawer::draw();
void CharDrawer::navigate() {
  cout << "Options:\n(d) Return to drawing mode\n(s) Save current file\n(l) Load file\n(c) Create file\n" <<
          "(p) Print current picture\n(q) Quit\n(r) Repeat this menu" << endl;
  cout << "Warning! A file must be created or opened before the program will enable drawing to it,\n"
       << "and most changes are automatically saved. There is no double-checking with you\n"
       << "to save before loading/quitting, either of which will close the currently open file\nwithout saving." << endl;
  char c;
  cin >> c;
  tolower(c);
  switch(c) {
    case 'd': //draw
      draw();
      break;
    case 's': //save
      save(); //this one might actually be redundant, based on the klutzy way I actually intend to save.
      //that is, I save whenever the user is done changing a row! or maybe each time the user is done changing anything!
      break;
    case 'l': //load
      load();
      break;
    case 'c': //create
      create();
      break;
    case 'p': //print
      print();
      break;
    case 'q': //quit
      //quit(); //huh. a bit of a strange place to put this, in a member function. Not sure I'll actually do anything in this case...
      return; //now we are out anyway.
    case 'r': default:
      //navigate(); is called at the end of this function anyway, since we want to return to the menu.
  }
  navigate();
}
void CharDrawer::load() {
    //if (fileopen)
    //  cout << "Current file will be discarded." << endl;
    
}
void CharDrawer::save() {

}