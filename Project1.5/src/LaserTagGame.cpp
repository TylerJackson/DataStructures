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
namespace std {

LaserTagGame::LaserTagGame() {
    team1File="";
    team2File="";
    teamMatchFile="";
}

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
    printNames();
}

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
                if(tempTagger.getTag(k).getTargetId()== tempTarget.getPlayerId())
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
                if(tempTagger.getTag(k).getTargetId() == tempTarget.getPlayerId())
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

void LaserTagGame::processInputMatchFile(string inputMatchName) {
    //read in match file and store in char **

	ifstream filein1;
    filein1.open(inputMatchName.c_str());
    char *buffer=new char[80];
    filein1.getline(buffer,80);
    int numberOfTags=(int)buffer[0]-'0';
    cout<<"::::num tags should be 6, it is: "<<numberOfTags<<endl;
    /*
    char ** matchfile=new char *[numberOfTags];
    for (int i=0;i<numberOfTags;i++){
        filein1.getline(buffer,80);
        matchfile[i]=new char[strlen(buffer)+1];
        strcpy(matchfile[i],buffer);
    }
    //print the match file to make sure it was read in correctly
    for(int i=0;i<numberOfTags;i++){
    	cout<<matchfile[i]<<endl;
    }
    //assign tags to the players
    for(int i=0;i<numberOfTags;i++){
    	cout<<"Info for tag "<<i+1<<" is----"<<endl;
    	int indexOfShooter=0;
    	while(matchfile[i][indexOfShooter]!=' '){
    		indexOfShooter++;
    	}
    	//this holds the shooterID as a char string
    	cout<<"    numDigits in shooter id is: "<<indexOfShooter<<endl;
    	char * tempshoot=new char[indexOfShooter+1];
    	for(int l=0;l<indexOfShooter;l++){
    		tempshoot[l]=matchfile[i][l];
    	}
    	tempshoot[indexOfShooter]='\0';
        int tempShooterId=atoi(tempshoot);
        cout<<"    The Shooter id is "<<tempShooterId<<endl;

    	int indexOfTarget=indexOfShooter+1; //shoot=2
    	while(matchfile[i][indexOfTarget]!=' '){
    		indexOfTarget++;
    	}
    	//this holds the targetID as a char string
    	cout<<"    numDigits in target id is: "<<indexOfTarget-indexOfShooter-1<<endl;
    	char * temptarg=new char[indexOfTarget-indexOfShooter];
    	for(int l=0;l<indexOfTarget-indexOfShooter-1;l++){
    		temptarg[l]=matchfile[i][l+indexOfTarget-indexOfShooter+1];
    	}
    	temptarg[indexOfTarget-indexOfShooter-1]='\0';
        int tempTargetId=atoi(temptarg);
        cout<<"    The Target id is "<<tempTargetId<<endl;

        int endOfTimeIndex=4;
        while(matchfile[i][endOfTimeIndex]!=' '){
            endOfTimeIndex++;
        }
        string tempstr=*(matchfile+i);
        tempstr=tempstr.substr(4,endOfTimeIndex);
        int tempGameTime=atoi(tempstr.c_str());
        int tempTagSpot=matchfile[i][endOfTimeIndex+1]-'0';
        Tag tempTag=Tag(tempTargetId, tempTagSpot, tempGameTime);
        if(A.playerOnTeam(tempShooterId)==true){
            A.getPlayer(tempShooterId).addTag(tempTag);
        }else if(B.playerOnTeam(tempShooterId)==true){
            B.getPlayer(tempShooterId).addTag(tempTag);
        }
    }*/
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
    	cout<<"For tag # "<<i+1<<endl;
    	cout<<"    the shooter ID is "<<tempShooterId<<endl;
    	cout<<"    the target ID is "<<tempTargetId<<endl;
    	cout<<"    the game time is "<<tempGameTime<<endl;
    	cout<<"    the tag spot is "<<tempTagSpot<<endl;
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
    for(int i=0;i<tempTeam.getNumPlayers();i++){
    	cout<<"Player "<<i+1<<": "<<tempTeam.getPlayerByIndex(i).getPlayerName()<<endl;
    }
    /*for(int i=2;i<numplayersteam1+2;i++){
        filein.getline(buffer,80);
        team1[i]=new char[strlen(buffer)+1];
        strcpy(team1[i],buffer);
    }
    filein.close();

    //create team
    Team tempTeam(team1[0]);

    //create players for team
    for(int i=0;i<numplayersteam1;i++){
        int tempPlayerId=team1[2+i][0]-'0';
        string tempPlayerName=*(team1+2+i)+2;
        Player temp=Player(tempPlayerName,tempPlayerId);
        tempTeam.addPlayer(temp);
    }*/
    filein.close();
    return tempTeam;
}

LaserTagGame::~LaserTagGame() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
