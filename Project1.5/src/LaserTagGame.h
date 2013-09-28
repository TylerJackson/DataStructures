/*
 * LaserTagGame.h
 *	My Laser Tag Game class has two teams, one for each in the game.
 *	It also has three strings that represent the two team files getting passed in
 *	---as well as the match file that holds the tag data.
 *	This class also handles all the file data and printing the 3 different verbosity
 *	---levels to an output file.
 *  Created on: Sep 26, 2013
 *      Author: tgjackson
 */

#ifndef LASERTAGGAME_H_
#define LASERTAGGAME_H_
#include "Team.h"
#include <fstream>
#include <cstring>
#include <cstdlib>

class LaserTagGame {
public:
	LaserTagGame();
    LaserTagGame(string teamAF,string teamBF, string teamMatchF);
    void printVLow(string output);
    void printVMed(string output);
    void printVHigh(string output);
    void printNames();
    void processInputMatchFile(string inputMatchName);
    Team processInputTeamFile(string inputFileName);
	virtual ~LaserTagGame();
private:
    string team1File;
    string team2File;
    string teamMatchFile;
    Team teamA;
    Team teamB;
};

#endif /* LASERTAGGAME_H_ */
