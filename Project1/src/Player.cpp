//
//  Player.cpp
//  TJackson
//  The player class holds each players info
//  - his player id, his name, his score, and an array of all the tags he's made
#include "Player.h"
Player::Player(string name,int idplayer){
    playerName=name;
    playerId=idplayer;
    tagList= new Tag [5];
    numTags=0;
    playerScore=0;
}
Player::Player(){
    playerName="";
    playerId=0;
    tagList= new Tag [5];
    numTags=0;
    playerScore=0;
}
void Player::addTag(Tag a){
    Tag * temp=new Tag [numTags+1];
    for(int i=0;i<numTags;i++){
        temp[i]=tagList[i];
    }
    temp[numTags]=Tag(a);
    numTags++;
    tagList=temp;
    updatePlayerScore();
}
int Player::getPlayerScore(){
    return playerScore;
}
int Player::getPlayerId(){
    return playerId;
}
void Player::updatePlayerScore(){
    playerScore=0;
    for(int i=0;i<numTags;i++){
        playerScore=playerScore+tagList[i].getTagScore();
    }
}
int Player::getNumTags(){
    return numTags;
}
string Player::getPlayerName(){
    return playerName;
}
Tag & Player::getTag(int index){
    return tagList[index];
}

