//
//  main.cpp
//  Project2
//
//  Created by Tyler JACKSON on 9/5/13.
//
//

#include <iostream>
#include "readInObject.h"
using namespace std;

int main(int argc, const char * argv[])
{
    for(int i=1;i<argc;i++){
    	cout<<argv[i]<<endl;
    }
    Category A=Category("franklin");
    Category AB=Category("franklin");

    readInObject readIn=readInObject();
   // readIn.readInTextFile(argv[1]);
    readIn.readInHelperFile(argv[2]);
    //readIn.printCategories();
	cout << "Hello, World2!\n";

    return 0;
}
