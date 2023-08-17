#pragma once
//warning: this class assumes Windows operating system.
#include <string> //do I want to use string? maybe I will need fancy symbols from elsewhere...
#include <iostream>
#include <fstream>
#include <ctype.h> //tolower()
#include <stdlib.h> //but specifically the Windows version, so as to use system("cls");
#include <conio.h>

#include "UtilA.h" //put the actual path here.

//what does one save, and what does one do to update the file?
//in an actual wordprocessor, one should NOT go saving the file after every change.
//but I don't know that I really want to load the file to memory...
class CharDrawer {
public:
    enum mode { draw, navigate/*, saveload*/ };

    void print(bool bDrawingMode = false); //prints. we call this after every change.
    void draw();
    void navigate();
    void load();
    void save();
    void create(); //create new file.
    void closefile();
    void quit(); //questionable if this really belongs here.
private:
    // (nCursorRow, nCursorCol) will be the location of the the character drawn by writeValAtCursor,
    // or in general the character drawn by prepareCursor(); fs << c;
    // note that for this to work, prepareCursor() sets fs.fset to nCursorRow, but the column right
    // before nCursorCol
    int nCursorRow;
    int nCursorCol;
    //const int nColMaxAllowed = 256; //not sure if I will include this... but maybe sometime... could be lower val, like 80, too...
    //const int nRowMaxAllowed = 256;
    std::string strFilename;
    const char* EXTENSION = ".txtpic";
    std::fstream fs;


/*  if the cursor is not at a valid position, we use these routines until it is a valid position,
    meaning that nCursorRow, nCursorCol is either a location in the picture as stands, or is one column
    after a location in the picture as stands.

    if the cursor is completely out of bounds we move the cursor itself until it is within the extreme bounds.
    we add newlines and spaces until the position does exist.
    
    additionally, this function makes it so that our filestream is positioned so that the next write operation
    will write to the valid cursor location.
    
    return true if the cursor is unmoved, false if fixing the cursor requires modifying nCursorRow and nCursorCol */
    bool prepareCursor();
    void writeValAtCursor(char c);

    //caution! these 3 functions ALTER the position of our filereader!
    //I could do something to prevent them from doing so, but...
    int rowsEnd(); //the number of rows, hence, we have rows of indices [0, nRowEnd();).
    int lengthRow(int nRow);
    int lengthLongestRow(); //currently not needed.
}