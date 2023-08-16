#pragma once
#include <string> //do I want to use string? maybe I will need fancy symbols from elsewhere...
#include <iostream>
#include <fstream>
#include <ctype.h> //tolower()

/*
https://cplusplus.com/doc/tutorial/files/
*/


//do I really want to write this as a class? honestly, probably.... .... ?

//what does one save, and what does one do to update the file?
//in an actual wordprocessor, one should NOT go saving the file after every change.
//but I don't know that I really want to load the file to memory...
class CharDrawer {
public:
    enum mode { draw, navigate/*, saveload*/ };
    char c; //I don't actually have a reason to protect this one...
    //these just return the index (starting at 0) of the last col and last row that currently exists.
    int nLastCol() const;
    int nLastRow() const;
    void print() const; //prints. we call this after every change.

    void draw();
    void navigate();
    void load();
    void save();
    void create(); //create new file.
    void quit(); // questionable if this really belongs here.
private:
    int nCursorRow;
    int nCursorCol;
    int nColMaxAllowed; //not sure if I will include this... but maybe.
    std::string strFilename;
}


//how does this work?
//we have an image that we print.



