//  main.cpp
//  Project1-Laser Tag
//  Created by Tyler JACKSON on 9/5/13.

#include <iostream>
#include <fstream>
#include <string>
#include "LaserTagGame.h"
#include <cstring>
#include <cstdlib>
using namespace std;
int main(int argc, const char * argv[])
{
    /*make sure the first arg is the team A text file
                    second arg is the team B text file
                    third arg is the match file
                    fourth arg is the file you want the results to but output to*/
    LaserTagGame game=LaserTagGame(argv[1], argv[2], argv[3]);
    if(strcmp(argv[5],"vlow")==0){
        game.printVLow(argv[4]);
    }else if(strcmp(argv[5],"vmed")==0){
        game.printVMed(argv[4]);
    }else if(strcmp(argv[5],"vhigh")==0){
        game.printVHigh(argv[4]);
    }
    return 0;
}