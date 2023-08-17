#include "CharDrawer.h"
using std::cin; using std::cout; using std::endl; using std::ios; using std::ios_base;
using std::string;

//Count number of characters (not \n or \0) in given row.
int CharDrawer::lengthRow(int nRow) {
  string str;
  fs.seekg(0, fs.beg);
  for (int i = 0; i <= nRow; ++i)
    if(!getline(fs, str)) //failed to read! assume row does not exist
      return 0;
  return str.size();
}
int CharDrawer::lengthLongestRow() {
  int nRowLength = 0;
  for (int i = 0; i <= rowsEnd(); ++i)
    nRowLength = maxsimp(nRowLength, lengthRow(i));
  return nRowLength;
}
//returns 1 plus the index of the last row,
//that is, returns the number of rows.
int CharDrawer::rowsEnd() {
  string str;
  int i = 0;
  fs.seekg(0, fs.beg);
  while (getline(fs, str))
    i++;
  return i;
}
/* Format of printing:
ideally, it could be roughly like this:
  12345.789111
           012
1 xxxxxxxxxxxx
2 xxxxxxxxxxxx
. xxxxx.xxxxxx
4 xxxxxxxxxxxx
5 xxxxxxxxxxxx
6 xxxxxxxxxxxx
7 xxxxxxxxxxxx
8 xxxxxxxxxxxx
9 xxxxxxxxxxxx
10xxxxxxxxxxxx
11xxxxxxxxxxxx

But never mind, I don't need much more than this:
    .   
 xxxxxxx
.xxx.xx
 xxxxxxxxx

really lame, but so what.
honestly, this is actually more effort than I want to put into it....
*/
/*
  bDrawingMode determines whether (false) we print the image as it is (still maintaining the row and column),
  or (true) we use '.' to represent the cursor on the image.
*/
void CharDrawer::print(bool bDrawingMode = false) {
  system("cls"); //clear screen, for the fun of it.
  int nEnd = rowsEnd();
  fs.seekg(0, fs.beg);
  //print top row with a '.' so we know where we are
  if(bDrawingMode) {
    pad(cout, 0, nCursorCol);
    cout << ".\n";
  }
  //print each row.
  for(int i = 0; i < nEnd; ++i) {
    //first, print the '.' that shows where we are
    //now print the row.
    if(bDrawingMode && i == nCursorRow) { //also draw '.' as the cursor
      cout << '.';
      int j = 0;
      char c;
      //by assumption, nCursorCol is at a valid point, or else 1 past the end of the line
      //otherwise, going right will automatically print a ' ' to the file,... or maybe be prohibited.
      while(fs.get(c) || j == nCursorCol) {
        if (j++ == nCursorCol) cout << '.';
        else if (c == '\n') {
          if (j == nCursorCol) cout << '.';
          break; 
          }
        else                   cout << c;
      }
      cout << '|' << endl;
    }
    else {
      if(bDrawingMode) cout << ' '; 
      string strLine;
      std::getline(fs, strLine);
      cout << strLine << '|' << endl;
    }
  }
}
/* this function puts the cursor in position using prepareCursor, then writes the character. */
void CharDrawer::writeValAtCursor(char c) {
  prepareCursor();
  fs << c;
}
void CharDrawer::draw() {
  string str;
  keyboardActionKey::e key;
  //assumption: at the start of the loop, the cursor is at a valid position.
  //we have to ensure this ourselves. it is a fragile position.
  prepareCursor();
  while (true) {
    print(true); //so far, print() clears the screen first.
    cout << "To exit \'draw\' mode and return to the main menu, press Esc." << endl;
    
    char cOutput = getKey(key);
    switch(key) {
      case keyboardActionKey::character:
        fs << cOutput; //writeValAtCursor(output); //possibly safer, but....
        //no break -- because we also go right after making a character
      case keyboardActionKey::arrowRight;
        nCursorCol++;
        break;
      case keyboardActionKey::arrowLeft;
        nCursorCol--;
        break;
      case keyboardActionKey::arrowUp;
        nCursorRow--;
        break;
      case keyboardActionKey::arrowDown;
        nCursorRow++;
        break;
      case keyboardActionKey::escape;
        navigate();
        break;
      default:
    }
    prepareCursor();
  }
}

/* place the cursor so that the next value fs prints will be at the cursor location.
 this may involve changing the cursor location and/or writing whitespaces to the stream. */
bool CharDrawer::prepareCursor() {
  // * start reading from the top of the file, at row=0 col=0.
  // from there, count how far down we must go. *
  int nLocation = 0;
  //!! we have to pre-compute this, or else it will alter the location of our writer in fs. !!
  int nLengthCursorRow = lengthRow(nCursorRow);
  int nRowEnd = rowsEnd();
  for(int i = 0; i < fs.seekg(0, fs.beg); ++i)
    nLocation += lengthRow(i) + 1; //+ 1 for '\n'.

  //the order of these 3 steps obviously matters!
  // * put cursor within extreme bounds *
  nCursorRow = maxsimp(nCursorRow, 0);
  nCursorCol = maxsimp(nCursorCol, 0);
  //nCursorRow = minsimp(nCursorRow, nRowMaxAllowed);
  //nCursorCol = minsimp(nCursorCol, nColMaxAllowed);

  // * make sure the row exists and position our cursor on it *
  if (nCursorRow > nRowEnd) {
    fs.seekg(0, fs.end); //append to end of file
    nLocation = fs.tellg(0, fs.end);
  } else
    fs.seekg((nLocation), fs.begin); //check for off by 1 error.
  while (nCursorRow > nRowEnd++) {
    fs << "\n";
    nLocation++;
  }
  // * make sure the column exists and get in position *
  // we are already on the row, so let's get to the correct column, or the last column if needbe.
  int nLocation += minsimp(nLengthCursorRow, nCursorCol);
  fs.seekg(nLocation, fs.beg);
  while (nCursorCol > nLengthCursorRow++) //note this is >.
    fs << " ";
  // * the cursor is now in position. *
}
void CharDrawer::navigate() {
  cout << "Options:\n(d) Return to drawing mode\n(s) Save current file\n(l) Load file\n(c) Create file\n" <<
          "(p) Print current picture\n(q) Quit\n(r) Repeat this menu" << endl;
  cout << "Warning! A file must be created or opened before the program will enable drawing to it,\n"
       << "and most changes are automatically saved. There is no double-checking with you\n"
       << "to save before loading/quitting, either of which will close the currently open file\nwithout saving." << endl;
  char c;
  cin >> c;
  c = tolower(c);
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
  fs.open(strFilename + EXTENSION, ios::in | ios::out);// | ios::trunc);
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
  closefile();
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