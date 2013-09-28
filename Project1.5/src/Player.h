/*
 * Player.h
 *	This is my player class.  It holds their name, their id number, and a list of their tags.
 *  Created on: Sep 24, 2013
 *      Author: tgjackson
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include "Tag.h"
#include <string>
using namespace std;
class Player {
public:
    Player ();
    Player(string name,int idnum);
	Player (const Player& orig);
	Player& operator=(const Player& rhs);
    void addTag(Tag a);
    void updatePlayerScore();
    int getPlayerScore();
    int getPlayerId();
    int getNumTags();
    string getPlayerName();
    Tag& getTag(int index);
    virtual~ Player();
private:
    string playerName;
    int playerId;
    int numTags;
    int playerScore;
    Tag* tagList;
};

#endif /* PLAYER_H_ */
