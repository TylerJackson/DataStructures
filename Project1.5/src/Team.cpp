/*
 * Team.cpp
 *
 *  Created on: Sep 24, 2013
 *      Author: tgjackson
 */

#include "Team.h"

Team::Team() {
    teamName="";
    playerList=0;
    teamScore=0;
    numPlayers=0;
}

//constructor with the team name as the arg
Team::Team(string name) {
    teamName=name;
    playerList=0;
    teamScore=0;
    numPlayers=0;
}
Team::Team(const Team& orig){
	this->teamName=orig.teamName;
	this->teamScore=orig.teamScore;
	this->numPlayers=orig.numPlayers;
	playerList=new Player[numPlayers];
	for(int i=0;i<numPlayers;i++){
		playerList[i]=orig.playerList[i];
	}
}
Team& Team::operator =(const Team& rhs){
	//if(this!=rhs){
		if(playerList!=0){
			delete [] playerList;
		}
	//}
	this->teamName=rhs.teamName;
	this->teamScore=rhs.teamScore;
	this->numPlayers=rhs.numPlayers;
	playerList=new Player[numPlayers];
	for(int i=0;i<numPlayers;i++){
		playerList[i]=rhs.playerList[i];
	}
	return *this;
}

//the add player function so that I can add a player when reading in from the
//team file.  It will not only add the player, but it will make sure to bring that
//players tag list with it
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

//updates the team score which is important because the team score gets updated whenever
//a player is added.  However, if a tag is added to a player already on a team, the team score
//doesn't get updated automatically.  So in this case we need to call this function
void Team::updateTeamScore() {
	teamScore=0;
	for(int i=0;i<numPlayers;i++){
		teamScore=teamScore+playerList[i].getPlayerScore();
	}
}

//this sorts the players based on the number of tags they had
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

//returns a player based on his player ID
Player& Team::getPlayer(int playId) {
	for(int i=0;i<numPlayers;i++){
		if(playerList[i].getPlayerId()==playId)return playerList[i];
	}
	return playerList[0];//shouldn't ever get here because we assume they know what team the player is on
}

//returns a player based on his index in the player array--good for looping through the player list
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

//deletes dynamic data player list
Team::~Team() {
	delete []playerList;
}
