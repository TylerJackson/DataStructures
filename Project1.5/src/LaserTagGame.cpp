/*
 * LaserTagGame.cpp
 *
 *  Created on: Sep 26, 2013
 *      Author: tgjackson
 */

#include "LaserTagGame.h"
#include <iostream>
#include <fstream>
#include <cstring>

LaserTagGame::LaserTagGame() {
    team1File="";
    team2File="";
    teamMatchFile="";
}

//constructor takes each team file as args as well as the file containing the tag data
LaserTagGame::LaserTagGame(string teamAF, string teamBF, string teamMatchF) {
	Team tempTeamA=processInputTeamFile(teamAF);
    Team tempTeamB=processInputTeamFile(teamBF);
    if(tempTeamA.getTeamName()>tempTeamB.getTeamName()){
        teamA=processInputTeamFile(teamBF);
        teamB=processInputTeamFile(teamAF);
    }else{
    	teamA=tempTeamA;
    	teamB=tempTeamB;
    }
    processInputMatchFile(teamMatchF);
}

//this prints the output at low verbosity to the file passed in as arg 'output'
void LaserTagGame::printVLow(string output) {
    ofstream fileout;
    fileout.open(output.c_str());
    fileout<<teamA.getTeamName()<<": "<<teamA.getTeamScore()<<" points"<<endl;
    fileout<<teamB.getTeamName()<<": "<<teamB.getTeamScore()<<" points"<<endl;
    if(teamA.getTeamScore()>teamB.getTeamScore()){
        fileout<<"Overall Winners:  "<<teamA.getTeamName()<<endl;
    }else if(teamB.getTeamScore()>teamA.getTeamScore()){
        fileout<<"Overall Winners:  "<<teamB.getTeamName()<<endl;
    }else{
        fileout<<"The Two Teams Tied"<<endl;
    }
    fileout.close();
}

//this prints the output at medium verbosity to the file passed in as arg 'output'
void LaserTagGame::printVMed(string output) {
    ofstream fileout1;
    fileout1.open(output.c_str());
    fileout1<<teamA.getTeamName()<<endl;
    int numPlayTeamA=teamA.getNumPlayers();
    for(int i=0;i<numPlayTeamA;i++){
        fileout1<<"     "<<teamA.getPlayerByIndex(i).getPlayerName();
        fileout1<<" had a total of "<<teamA.getPlayerByIndex(i).getNumTags()<<" tags"<<endl;
    }
    fileout1<<teamB.getTeamName()<<endl;
    int numPlayTeamB=teamB.getNumPlayers();
    for(int i=0;i<numPlayTeamB;i++){
        fileout1<<"     "<<teamB.getPlayerByIndex(i).getPlayerName();
        fileout1<<" had a total of "<<teamB.getPlayerByIndex(i).getNumTags()<<" tags"<<endl;
    }
    fileout1<<endl;
    fileout1<<"Best score from "<<teamA.getTeamName()<<": ";
    fileout1<<teamA.getHighScorer().getPlayerName()<<"(";
    fileout1<<teamA.getHighScorer().getPlayerScore()<<" points)"<<endl;

    fileout1<<"Best score from "<<teamB.getTeamName()<<": ";
    fileout1<<teamB.getHighScorer().getPlayerName()<<"(";
    fileout1<<teamB.getHighScorer().getPlayerScore()<<" points)"<<endl;

    fileout1<<teamA.getTeamName()<<": "<<teamA.getTeamScore()<<" points"<<endl;
    fileout1<<teamB.getTeamName()<<": "<<teamB.getTeamScore()<<" points"<<endl;
    if(teamA.getTeamScore()>teamB.getTeamScore()){
        fileout1<<"Overall Winners:  "<<teamA.getTeamName()<<endl;
    }else if(teamB.getTeamScore()>teamA.getTeamScore()){
        fileout1<<"Overall Winners:  "<<teamB.getTeamName()<<endl;
    }else{
        fileout1<<"The Two Teams Tied"<<endl;
    }
    fileout1.close();
}

//this prints the output at high verbosity to the file passed in as arg 'output'
void LaserTagGame::printVHigh(string output) {
    ofstream fileout2;
    fileout2.open(output.c_str());
    //print out team1 to file
    fileout2<<teamA.getTeamName()<<endl;
    //store number of players on each team in local variables for readability
    int numPlayTeamA=teamA.getNumPlayers();
    int numPlayTeamB=teamB.getNumPlayers();
    //loop through the taggers comparing them with each player on the other team
    //therefore another loop to go through players on other team
    //a third loop to go through each individual tag of the current tagger to see if its
    //--target id matches the current id of the player on the other team
    //This is to count the number of times the current tagger tagged the first player
    //--on the other team, and print it to the file
    for(int i=0;i<numPlayTeamA;i++){
    	//create local Player for each iteration for clarity
        Player tempTagger=teamA.getPlayerByIndex(i);
        int numTagsForTagger=tempTagger.getNumTags();
        for(int j=numPlayTeamA+1;j<=numPlayTeamA+numPlayTeamB;j++){
        	//local variable for temporary target for clarity
            Player tempTarget=teamB.getPlayer(j);
            int count=0;
            for(int k=0;k<numTagsForTagger;k++){
            	Tag tempTag=tempTagger.getTag(k);
                if(tempTag.getTargetId()== tempTarget.getPlayerId())
                    count++;
            }
            fileout2<<"     ";
            fileout2<<tempTagger.getPlayerName()<<" tagged "<<tempTarget.getPlayerName();
            fileout2<<" "<<count<<" times"<<endl;
        }
        fileout2<<"     ";
        fileout2<<tempTagger.getPlayerName()<<" had a total of "<<tempTagger.getNumTags();
        fileout2<<" tags"<<endl;
    }
    fileout2<<teamA.getTeamName()<<": "<<teamA.getTeamScore()<<" points"<<endl;
    fileout2<<endl;
    //now rinse and repeat with the second team
    fileout2<<teamB.getTeamName()<<endl;
    for(int i=0;i<numPlayTeamB;i++){
        Player tempTagger=teamB.getPlayerByIndex(i);
        int numTagsForTagger=tempTagger.getNumTags();
        for(int j=1;j<=numPlayTeamA;j++){
            Player tempTarget=teamA.getPlayer(j);
            int count=0;
            for(int k=0;k<numTagsForTagger;k++){
            	Tag tempTag1=tempTagger.getTag(k);
                if(tempTag1.getTargetId() == tempTarget.getPlayerId())
                    count++;
            }
            fileout2<<"     ";
            fileout2<<tempTagger.getPlayerName()<<" tagged "<<tempTarget.getPlayerName();
            fileout2<<" "<<count<<" times"<<endl;
        }
        fileout2<<"     ";
        fileout2<<tempTagger.getPlayerName()<<" had a total of "<<tempTagger.getNumTags();
        fileout2<<" tags"<<endl;
    }
    fileout2<<teamB.getTeamName()<<": "<<teamB.getTeamScore()<<" points"<<endl;
    fileout2<<endl;
    if(teamA.getTeamScore()>teamB.getTeamScore()){
        fileout2<<"Winners:  "<<teamA.getTeamName()<<endl;
    }else if(teamB.getTeamScore()>teamA.getTeamScore()){
        fileout2<<"Winners:  "<<teamB.getTeamName()<<endl;
    }else{
        fileout2<<"The Two Teams Tied"<<endl;
    }
    fileout2.close();
}

//this was a function I made to help when I was testing the various file processing.  Prints to console
//as opposed to a file every time
void LaserTagGame::printNames(){
	cout<<"There are two teams in our game"<<endl;
	cout<<endl;
	cout<<"Team 1: "<<teamA.getTeamName()<<endl;
	cout<<"Team 2: "<<teamB.getTeamName()<<endl;
	cout<<"Players on Team 1: "<<endl;
	for(int i=0;i<teamA.getNumPlayers();i++){
		cout<<"    "<<teamA.getPlayerByIndex(i).getPlayerName()<<endl;
		cout<<"        He/she had "<<teamA.getPlayerByIndex(i).getNumTags()<<" tag(s)"<<endl;
	}
	cout<<endl;
	cout<<"Players on Team 2: "<<endl;
	for(int i=0;i<teamB.getNumPlayers();i++){
		cout<<"    "<<teamB.getPlayerByIndex(i).getPlayerName()<<endl;
		cout<<"        He/she had "<<teamB.getPlayerByIndex(i).getNumTags()<<" tag(s)"<<endl;
	}

}

//this processes the tag data and adds each tag to a player--therefore
//this has to be called after the two team files are processed or else it will have no
//players to add the tags to.
void LaserTagGame::processInputMatchFile(string inputMatchName) {
    //read in match file and store in char **

	ifstream filein1;
    filein1.open(inputMatchName.c_str());
    char *buffer=new char[80];
    filein1>>buffer;
    int numberOfTags=atoi(buffer);
    for(int i=0;i<numberOfTags;i++){
    	char * tempShootID= new char[2];
    	char * tempTargID=new char[2];
    	char * tempGTime=new char[6];
    	char * tempTSpot=new char[1];
    	filein1>>tempShootID;
    	filein1>>tempTargID;
    	filein1>>tempGTime;
    	filein1>>tempTSpot;
    	int tempShooterId=atoi(tempShootID);
    	int tempTargetId=atoi(tempTargID);
    	int tempGameTime=atoi(tempGTime);
    	int tempTagSpot=atoi(tempTSpot);
    	Tag temp(tempTargetId,tempTagSpot,tempGameTime);
    	if(teamA.playerOnTeam(tempShooterId)==true){
    		teamA.getPlayer(tempShooterId).addTag(temp);
    	}
    	if(teamB.playerOnTeam(tempShooterId)==true){
    		teamB.getPlayer(tempShooterId).addTag(temp);
    	}
    }
    teamA.updateTeamScore();
    teamA.sortPlayers();
    teamB.updateTeamScore();
    teamB.sortPlayers();
}

Team LaserTagGame::processInputTeamFile(string inputFileName) {
    //create a char ** with the lines of the file
    ifstream filein;
    filein.open(inputFileName.c_str());
    char ** team1=new char*[12];
    char buffer[80];
    for(int i=0;i<2;i++){
        filein.getline(buffer,80);
        team1[i]=new char[strlen(buffer)+1];
        strcpy(team1[i],buffer);
    }
    int numplayersteam1=atoi(team1[1]);
    Team tempTeam(team1[0]);
    for(int i=0;i<numplayersteam1;i++){
    	char *temId=new char [3];
    	filein>>temId;
    	int tempId=atoi(temId);
    	filein>>buffer;
    	Player playerToAdd(buffer,tempId);
    	tempTeam.addPlayer(playerToAdd);
    }
    filein.close();
    return tempTeam;
}

LaserTagGame::~LaserTagGame() {
	// TODO Auto-generated destructor stub
}

