/*
 * LaserTagGame.h
 *
 *  Created on: Sep 26, 2013
 *      Author: tgjackson
 */

#ifndef LASERTAGGAME_H_
#define LASERTAGGAME_H_
#include "Team.h"
#include <fstream>
#include <cstring>
#include <cstdlib>
namespace std {

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

} /* namespace std */
#endif /* LASERTAGGAME_H_ */
