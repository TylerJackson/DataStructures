//
//  Team.cpp
//  TJackson
//  The team class holds all the info for each team
//  -The team name, the team score, and an array of all the players that were on the team
#include "Team.h"
Team::Team(string name)
{
    teamName=name;
    numPlayers=0;
    playerList= new Player [5];
    teamScore=0;
}
Team::Team(){
    teamName="";
    numPlayers=0;
    playerList= new Player [5];
    teamScore=0;
}
void Team::addPlayer(Player temp){
    Player * tempList=new Player[numPlayers+1];
    teamScore=teamScore + temp.getPlayerScore();
    for(int i=0;i<numPlayers;i++){
        tempList[i]=playerList[i];
    }
    tempList[numPlayers]=temp;
    numPlayers++;
    playerList=tempList;
    teamScore=teamScore + temp.getPlayerScore();
}
int Team::getTeamScore(){
    return teamScore;
}
Player& Team::getPlayer(int playId){
    if(playerOnTeam(playId)==true){
        for(int i=0;i<numPlayers;i++){
            if(playerList[i].getPlayerId()==playId){
                return playerList[i];
            }
        }
    }
    return playerList[0];
}
bool Team::playerOnTeam(int playId){
    for(int i=0;i<numPlayers;i++){
        if(playerList[i].getPlayerId()==playId) return true;
    }
    return false;
}
string Team::getTeamName(){
    return teamName;
}
void Team::updateTeamScore(){
    teamScore=0;
    for(int i=0;i<numPlayers;i++){
        teamScore=teamScore +playerList[i].getPlayerScore();
    }
}
int Team::getNumPlayers(){
    return numPlayers;
}
Player& Team::getHighScorer(){
    Player temp=playerList[5];
    for(int i=1;i<numPlayers;i++){
        if(playerList[i].getPlayerScore()>temp.getPlayerScore()){
            temp=playerList[i];
        }
    }
    for(int i=0;i<numPlayers;i++){
        if(temp.getPlayerId()==playerList[i].getPlayerId())
            return playerList[i];
    }
}
void Team::sortPlayers(){
    for(int i=1;i<numPlayers;i++){
        for(int j=0;j<i;j++)
            if(playerList[i].getNumTags()>playerList[j].getNumTags()){
                Player tempPlayer=Player(playerList[j].getPlayerName(),playerList[j].getPlayerId());
                for(int k=0;k<playerList[j].getNumTags();k++){
                    tempPlayer.addTag(playerList[j].getTag(k));
                }
                playerList[j]=playerList[i];
                playerList[i]=tempPlayer;
            }
    }
}
Player & Team::getPlayerByIndex(int playIndex){
    return playerList[playIndex];
}
