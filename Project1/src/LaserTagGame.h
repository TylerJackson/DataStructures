//
//  LaserTagGame.h
//  TJackson
//  The game class holds all the info for the laser tag game
//  -The info for the two teams that we got from the three files
//  -It handles reading in the data from the two team files and assigning it to team
//  -It handles reading in the match file and adding tags for all the tags to the right
//   teams/players
//  -Also handles writing out the 3 different verbosity levels to the output file
#ifndef __TJackson__LaserTagGame__
#define __TJackson__LaserTagGame__
#include <iostream>
#include <fstream>
#include "Team.h"
class LaserTagGame{
 public:
    LaserTagGame(string teamAF,string teamBF, string teamMatchF);
    void printVLow(string output);
    void printVMed(string output);
    void printVHigh(string output);
    Team processInputTeamFile(string inputFileName);
    void processInputMatchFile(string inputMatchName,Team & A,Team & B);
private:
    string team1File;
    string team2File;
    string teamMatchFile;
    Team teamA;
    Team teamB;
};
#endif /* defined(__TJackson__LaserTagGame__) */