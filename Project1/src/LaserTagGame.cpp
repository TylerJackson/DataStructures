//
//  LaserTagGame.cpp
//  TJackson
//  The game class holds all the info for the laser tag game
//  -The info for the two teams that we got from the three files
//  -It handles reading in the data from the two team files and assigning it to team
//  -It handles reading in the match file and adding tags for all the tags to the right
//   teams/players
//  -Also handles writing out the 3 different verbosity levels to the output file
#include "LaserTagGame.h"
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include <cstdlib>
using namespace std;
LaserTagGame::LaserTagGame(string teamAF,string teamBF, string teamMatchF){
    Team tempTeamA=processInputTeamFile(teamAF);
    Team tempTeamB=processInputTeamFile(teamBF);
    if(tempTeamA.getTeamName()<tempTeamB.getTeamName()){
        teamA=processInputTeamFile(teamAF);
        teamB=processInputTeamFile(teamBF);
    }else{
        teamB=processInputTeamFile(teamAF);
        teamA=processInputTeamFile(teamBF);
    }
    processInputMatchFile(teamMatchF, teamA, teamB);
}
void LaserTagGame::printVLow(string outputFileName){
    ofstream fileout;
    fileout.open(outputFileName.c_str());
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
void LaserTagGame::printVMed(string outputFileName){
    ofstream fileout1;
    fileout1.open(outputFileName.c_str());
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
void LaserTagGame::printVHigh(string outputFileName){
    ofstream fileout2;
    fileout2.open(outputFileName.c_str());
    fileout2<<teamA.getTeamName()<<endl;
    int numPlayTeamA=teamA.getNumPlayers();
    int numPlayTeamB=teamB.getNumPlayers();
    for(int i=0;i<numPlayTeamA;i++){
        Player tempTagger=teamA.getPlayerByIndex(i);
        int numTagsForTagger=tempTagger.getNumTags();
        for(int j=numPlayTeamA+1;j<=numPlayTeamA+numPlayTeamB;j++){
            Player tempTarget=teamB.getPlayer(j);
            int count=0;
            for(int k=0;k<numTagsForTagger;k++){
                if(tempTagger.getTag(k).getTaggedId()== tempTarget.getPlayerId())
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
    fileout2<<teamB.getTeamName()<<endl;
    for(int i=0;i<numPlayTeamB;i++){
        Player tempTagger=teamB.getPlayerByIndex(i);
        int numTagsForTagger=tempTagger.getNumTags();
        for(int j=1;j<=numPlayTeamA;j++){
            Player tempTarget=teamA.getPlayer(j);
            int count=0;
            for(int k=0;k<numTagsForTagger;k++){
                if(tempTagger.getTag(k).getTaggedId()== tempTarget.getPlayerId())
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
Team LaserTagGame::processInputTeamFile(string inputFileName){
    
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
    int numplayersteam1=(int)team1[1][0]-'0';
    for(int i=2;i<numplayersteam1+2;i++){
        filein.getline(buffer,80);
        team1[i]=new char[strlen(buffer)+1];
        strcpy(team1[i],buffer);
    }
    filein.close();
    
    //create team
    Team tempTeam=Team(team1[0]);
    
    //create players for team
    for(int i=0;i<numplayersteam1;i++){
        int tempPlayerId=team1[2+i][0]-'0';
        string tempPlayerName=*(team1+2+i)+2;
        Player temp=Player(tempPlayerName,tempPlayerId);
        tempTeam.addPlayer(temp);
    }
    return tempTeam;
    
}
void LaserTagGame::processInputMatchFile(string inputMatchName,Team & A,Team & B){
    //read in match file and store in char**
    ifstream filein;
    filein.open(inputMatchName.c_str());
    char buffer[80];
    filein.getline(buffer,80);
    int numberOfTags=(int)buffer[0]-'0';
    char ** matchfile=new char *[numberOfTags];
    for (int i=0;i<numberOfTags;i++){
        filein.getline(buffer,80);
        matchfile[i]=new char[strlen(buffer)+1];
        strcpy(matchfile[i],buffer);
    }
    
    //assign tags to the players
    for(int i=0;i<numberOfTags;i++){
        int tempShooterId=(int)matchfile[i][0]-'0';
        int tempTargetId=(int)matchfile[i][2]-'0';
        int endOfTimeIndex=4;
        while(matchfile[i][endOfTimeIndex]!=' '){
            endOfTimeIndex++;
        }
        string tempstr=*(matchfile+i);
        tempstr=tempstr.substr(4,endOfTimeIndex);
        int tempGameTime=atoi(tempstr.c_str());
        int tempTagSpot=matchfile[i][endOfTimeIndex+1]-'0';
        Tag tempTag=Tag(tempShooterId, tempTargetId, tempGameTime, tempTagSpot);
        if(A.playerOnTeam(tempShooterId)==true){
            A.getPlayer(tempShooterId).addTag(tempTag);
        }else if(B.playerOnTeam(tempShooterId)==true){
            B.getPlayer(tempShooterId).addTag(tempTag);
        }
    }
    A.updateTeamScore();
    A.sortPlayers();
    B.updateTeamScore();
    B.sortPlayers();
}