#pragma once
#include <string> //do I want to use string? maybe I will need fancy symbols from elsewhere...
#include <iostream>
#include <fstream>
#include <ctype.h> //tolower()

/*
https://cplusplus.com/doc/tutorial/files/
https://www.codesdope.com/cpp-file-io/
https://stackoverflow.com/questions/48085781/what-is-the-difference-among-iosapp-out-and-trunc-in-c#:~:text=ios%3A%3Aout%20is%20the,the%20end%20of%20the%20file.

Now, beginning to learn about how to change our cursor position, as it were:...
    https://stackoverflow.com/questions/31538554/fstream-how-to-seekg-to-position-x-from-end
        (not really for me, but useful for finding what stuff we deal with here)

https://stackoverflow.com/questions/5570361/file-vs-fstream
    FILE (C) vs fstream (C++)
    and, importantly, read the comments about memory management and remembering to close files.
    or rather, to be wary of 'fflush' in the destructor.

flags needed to io a file versus to create a file 
    http://eel.is/c++draft/filebuf#tab:filebuf.open.modes
    ...
    do I need to use 'trunc' to create? I definitely need to avoid using it to load....
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
    void print(bool bDrawingMode = false) const; //prints. we call this after every change.

    void draw();
    void navigate();
    void load();
    void save();
    void create(); //create new file.
    void closefile();
    void quit(); // questionable if this really belongs here.
private:
    int nCursorRow;
    int nCursorCol;
    //const int nColMaxAllowed = 256; //not sure if I will include this... but maybe sometime...
    //const int nRowMaxAllowed = 256;
    std::string strFilename;
    const char* EXTENSION = ".txtpic";
    std::fstream fs;
}


//how does this work?
//we have an image that we print.



