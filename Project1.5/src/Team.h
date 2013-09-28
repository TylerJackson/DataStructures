/*
 * Team.h
 *	This is my team class. It holds an array of players, and has functions to hold the teams score.
 *	It also has functions to order the players on the team based on their number of tags
 *  Created on: Sep 24, 2013
 *      Author: tgjackson
 */

#ifndef TEAM_H_
#define TEAM_H_
#include "Player.h"

#include <iostream>
using namespace std;

class Team {
public:
    Team();
    Team(string name);
    Team(const Team&);
    Team& operator=(const Team&);
    void addPlayer(Player a);
    void updateTeamScore();
    void sortPlayers();
    bool playerOnTeam(int playId);
    int getTeamScore();
    int getNumPlayers();
    string getTeamName();
    Player& getPlayer(int playId);
    Player& getPlayerByIndex(int playIndex);
    Player& getHighScorer();
	virtual ~Team();
private:
    string teamName;
    Player * playerList;
    int teamScore;
    int numPlayers;
};

#endif /* TEAM_H_ */
