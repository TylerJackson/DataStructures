/*
 * Team.cpp
 *
 *  Created on: Sep 24, 2013
 *      Author: tgjackson
 */

#include "Team.h"

namespace std {

Team::Team() {
    teamName="";
    playerList=0;
    teamScore=0;
    numPlayers=0;
}

Team::Team(string name) {
    teamName=name;
    playerList=0;
    teamScore=0;
    numPlayers=0;
}

void Team::addPlayer(Player a) {
	if(numPlayers == 0){
		playerList=new Player[1];
		playerList[0]=a;
		teamScore=teamScore + a.getPlayerScore();
		numPlayers++;
	}else{
		Player* tempList=new Player[numPlayers+1];
		teamScore=teamScore + a.getPlayerScore();
		for(int i=0;i<numPlayers;i++){
			tempList[i]=playerList[i];
		}
		tempList[numPlayers]=a;
		//delete old player list
		delete [] playerList;
		numPlayers++;
		playerList=tempList;
	}
}

void Team::updateTeamScore() {
	teamScore=0;
	for(int i=0;i<numPlayers;i++){
		teamScore=teamScore+playerList[i].getPlayerScore();
	}
}

void Team::sortPlayers() {
	for(int j=0;j<numPlayers;j++){
		for(int i=j+1;i<numPlayers;i++){
			if(playerList[j].getNumTags()<playerList[i].getNumTags()){
				Player temp=playerList[j];
				playerList[j]=playerList[i];
				playerList[i]=temp;
			}
		}
	}
}

bool Team::playerOnTeam(int playId) {
	for(int i=0;i<numPlayers;i++){
		if(playerList[i].getPlayerId()==playId)return true;
	}
	return false;
}

int Team::getTeamScore() {
	return teamScore;
}

int Team::getNumPlayers() {
	return numPlayers;
}

string Team::getTeamName() {
	return teamName;
}

Player& Team::getPlayer(int playId) {
	for(int i=0;i<numPlayers;i++){
		if(playerList[i].getPlayerId()==playId)return playerList[i];
	}
	return playerList[0];//shouldn't ever get here because we assume they know what team the player is on
}

Player& Team::getPlayerByIndex(int playIndex){
	return playerList[playIndex]; //we assume they didn't choose an index bigger than the number of players
}

Player& Team::getHighScorer() {
	Player highscorer=playerList[0];
	for(int i=1;i<numPlayers;i++){
		if(playerList[i].getPlayerScore()>highscorer.getPlayerScore()){
			highscorer=playerList[i];
		}
	}

	return getPlayer(highscorer.getPlayerId());
}

Team::~Team() {
	delete []playerList;
}

} /* namespace std */
