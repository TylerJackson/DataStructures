//
//  Player.h
//  TJackson
//
//  Created by Tyler JACKSON on 9/7/13.
//  The player class holds each players info
//  - his player id, his name, his score, and an array of all the tags he's made
#ifndef __TJackson__Player__
#define __TJackson__Player__
#include <iostream>
#include <string>
#include "Tag.h"
using namespace std;
class Player{
public:
    Player(string name,int idnum);
    Player ();
    void addTag(Tag a);
    int getPlayerScore();
    int getPlayerId();
    int getNumTags();
    void updatePlayerScore();
    string getPlayerName();
    Tag & getTag(int index);
    virtual ~ Player();
private:
    string playerName;
    int playerId;
    Tag * tagList;
    int numTags;
    int playerScore;
};
#endif /* defined(__TJackson__Player__) */
