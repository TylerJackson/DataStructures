//
//  main.cpp
//  Project2
//	Main file of my project 2 that processes the arguments 1-text file and 2-helper file
//  Created by Tyler JACKSON on 9/5/13.
//
//

#include <iostream>
#include "readInObject.h"
#include <cctype>
#include <stdio.h>
using namespace std;

int main(int argc, const char * argv[])
{
	//initializes my read In Object and reads in the helper file and
	//then the book file.  Then it prints it using print answer
    readInObject readIn;
    readIn.readInHelperFile(argv[2]);
    readIn.readInTextFile(argv[1]);
    readIn.printAnswer(argv[3]);
    return 0;
}
