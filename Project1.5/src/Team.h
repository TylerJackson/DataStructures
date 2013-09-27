/*
 * Team.h
 *
 *  Created on: Sep 24, 2013
 *      Author: tgjackson
 */

#ifndef TEAM_H_
#define TEAM_H_
#include "Player.h"
namespace std {

class Team {
public:
    Team();
    Team(string name);
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

} /* namespace std */
#endif /* TEAM_H_ */
