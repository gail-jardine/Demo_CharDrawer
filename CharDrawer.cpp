#include "CharDrawer.h"
using std::cin; using std::cout; using std::endl; using std::ios;
using std::string;


int CharDrawer::nLastCol() const;
int CharDrawer::nLastRow() const;
/* Format of printing:
ideally, it could be like this:
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

But never mind, this is all I really want:
    .   
 xxxxxxx
.xxxxxxx
 xxxxxxx

really lame, but so what.
honestly, this is actually more effort than I want to put into it....
*/
/*
  bDrawingMode determines whether (false) we print the image as it is (still maintaining the row and column),
  or (true) we use '.' to represent the cursor on the image.
*/
void CharDrawer::print(bool bDrawingMode = false) const { //prints. we call this after every change.
  //print top row with a '.' so we know where we are
  iostream is
  //print each row.
  int nEnd = nLastRow();
  for(int i = 0; i < nEnd; ++i) {
    //first, print the '.' that shows where we are
    //now print the row.
    if(bDrawingMode && i == nCursorRow) { //also draw '.' as the cursor
      int j = 0;
      char c;
      //by assumption, nCursorCall is at most 1 past the last drawn pt.
      //otherwise, going right will automatically print a ' ' to the file,... or maybe be prohibited.
      while(is.get(c) || j == nCursorCall) {
        if (j++ == nCursorCol) cout << '.';
        else                   cout << c;
        if (c == '\n' && nCursorCol > j)
          break; //come to the end
      }
      cout << "" << endl;
    }
    else {
      string strLine;
      std::getline(is, strLine);
      cout << strLine << endl;
    }
  }
}


void CharDrawer::draw() { //this one is a world to itself.
  string str;
  while (cin.get(str)) {

    cout << "To end \'draw\' mode and return to the main menu, press Esc." << endl;
    print(true);
  }
}
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
    case 'l':
      load();
      break;
    case 'c':
      create();
      break;
    case 'p':
      print();
      break;
    case 'q':
      quit();
    case 'r': default:
      //navigate(); is called at the end of this function anyway, since we want to return to the menu.
  }
  navigate();
}
void CharDrawer::create() {
  closefile(); //we won't even check if the file they want to load exists before closing current file.
  cout << "What is the name of the file in the current folder that you want to create,\n" <<
          "not including the extension? (The extension will be \'" << this->EXTENSION << "\')." << endl;
  cout << strFilename;
   //check if I need 'ios::trunc' here in order to actually create a file. If not, 
   //I am likely to replace the body of this function with a call to load().
  fs.open(strFilename + EXTENSION, ios::in | ios::out);
  if (!fs.is_open()) {
    strFilename = "";
    cout << "Sorry, " << strFilename << this->EXTENSION << " could not be created." << endl;
  }
  nCursorRow = nCursorCol = 0;
}
void CharDrawer::load() {
  closefile(); //we won't even check if the file they want to load exists before closing current file.
  cout << "What is the name of the file in the current folder that you want to open,\n" <<
          "not including the extension? (The extension must be \'" << this->EXTENSION << "\')." << endl;
  cout << strFilename;
  fs.open(strFilename + EXTENSION, ios::in | ios::out);
  if (!fs.is_open()) {
    strFilename = "";
    cout << "Sorry, " << strFilename << this->EXTENSION << " did not load." << endl;
  }
  nCursorRow = nCursorCol = 0;
}
void CharDrawer::save() {
  if(!fs.is_open()) {
    cout << "No file open to save." << endl;
    return;
  }
  cout << "Under the current implementation, this function does nothing." <<
  "\nThe file will be saved by default, anyway." << endl;
  //seriously, that is basically true, by the very fact I'm using fstream, it seems...
}
void CharDrawer::quit() {
  closefile(); // clearly, this is all we really want to do here.
  exit(0);
  //c.f. exit(EXIT_FAILURE);
}
void CharDrawer::closefile() {
  if (fs.is_open())
    fs.close();
  if (fs.is_open()) {
    cout << "File still open! I recommend you call \'quit\' when you can.";
  }
  strFilename = "";
}