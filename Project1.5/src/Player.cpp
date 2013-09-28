/*
 * Player.cpp
 *  Created on: Sep 24, 2013
 *      Author: tgjackson
 */

#include "Player.h"
#include <iostream>

Player::Player() {
    playerName="";
    playerId=0;
    numTags=0;
    playerScore=0;
    tagList=0;
}

//player constructor takes the name of the player and the player's id number as args
Player::Player(string name, int idnum) {
	playerName=name;
	playerId=idnum;
	numTags=0;
	playerScore=0;
	tagList=0;
}
Player::Player(const Player& orig){
	this->playerId=orig.playerId;
	this->numTags=orig.numTags;
	this->playerScore=orig.playerScore;
	tagList=new Tag[this->numTags];
	for(int i=0;i<this->numTags;i++){
		tagList[i]=orig.tagList[i];
	}
	this->playerName=orig.playerName;

}
Player& Player::operator=(const Player& rhs){
	//if(this != rhs){
		if(tagList!=0){
			delete []tagList;
		}
	//}
	this->playerName=rhs.playerName;
	this->playerId=rhs.playerId;
	this->numTags=rhs.numTags;
	this->playerScore=rhs.playerScore;
	tagList=new Tag[this->numTags];
	for(int i=0;i<this->numTags;i++){
		tagList[i]=rhs.tagList[i];
	}
	return *this;
}
//remember if you add a tag to a player already on a team, that you need to update the
//team score--this is only updated when a new player is added, not when a new tag is added
void Player::addTag(Tag a){
    Tag* temp=new Tag [numTags+1];
    for(int i=0;i<numTags;i++){
        temp[i]=tagList[i];
    }
    temp[numTags]=a;
    delete []tagList;
    numTags++;
    tagList=temp;
    updatePlayerScore();
}

//this updates the player score which is useful because I add tags occasionally and
//we always want this to be up to date
void Player::updatePlayerScore() {
    playerScore=0;
    for(int i=0;i<numTags;i++){
        playerScore=playerScore+tagList[i].getTagScore();
    }
}

int Player::getPlayerScore() {
	return playerScore;
}

int Player::getPlayerId() {
	return playerId;
}

int Player::getNumTags() {
	return numTags;
}

string Player::getPlayerName() {
	return playerName;
}

//returns a tag based on where it is in the array so that I can figure out
//who this player tagged
Tag& Player::getTag(int index) {
	return tagList[index];
}
//destructor removes dynamic data
Player::~Player() {
	delete []tagList;
}

