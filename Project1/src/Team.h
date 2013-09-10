//
//  Team.h
//  TJackson
//  The team class holds all the info for each team
//  -The team name, the team score, and an array of all the players that were on the team
#ifndef __TJackson__Team__
#define __TJackson__Team__
#include <iostream>
#include <string>
#include "Player.h"
using namespace std;
class Team{
public:
    Team(string name);
    Team();
    void addPlayer(Player a);
    int getTeamScore();
    string getTeamName();
    Player &getPlayer(int playId);
    Player &getPlayerByIndex(int playIndex);
    Player& getHighScorer();
    bool playerOnTeam(int playId);
    void updateTeamScore();
    int getNumPlayers();
    void sortPlayers();
private:
    string teamName;
    int numPlayers;
    Player * playerList;
    int teamScore;
};
#endif /* defined(__TJackson__Team__) */