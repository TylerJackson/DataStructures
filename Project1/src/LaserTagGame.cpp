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
    fileout.open(outputFileName);
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
    ofstream fileout;
    fileout.open(outputFileName);
    fileout<<teamA.getTeamName()<<endl;
    int numPlayTeamA=teamA.getNumPlayers();
    for(int i=0;i<numPlayTeamA;i++){
        fileout<<"     "<<teamA.getPlayerByIndex(i).getPlayerName();
        fileout<<" had a total of "<<teamA.getPlayerByIndex(i).getNumTags()<<" tags"<<endl;
    }
    fileout<<teamB.getTeamName()<<endl;
    int numPlayTeamB=teamB.getNumPlayers();
    for(int i=0;i<numPlayTeamB;i++){
        fileout<<"     "<<teamB.getPlayerByIndex(i).getPlayerName();
        fileout<<" had a total of "<<teamB.getPlayerByIndex(i).getNumTags()<<" tags"<<endl;
    }
    fileout<<endl;
    fileout<<"Best score from "<<teamA.getTeamName()<<": ";
    fileout<<teamA.getHighScorer().getPlayerName()<<"(";
    fileout<<teamA.getHighScorer().getPlayerScore()<<" points)"<<endl;
    
    fileout<<"Best score from "<<teamB.getTeamName()<<": ";
    fileout<<teamB.getHighScorer().getPlayerName()<<"(";
    fileout<<teamB.getHighScorer().getPlayerScore()<<" points)"<<endl;
    
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
void LaserTagGame::printVHigh(string outputFileName){
    ofstream fileout;
    fileout.open(outputFileName);
    fileout<<teamA.getTeamName()<<endl;
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
            fileout<<"     ";
            fileout<<tempTagger.getPlayerName()<<" tagged "<<tempTarget.getPlayerName();
            fileout<<" "<<count<<" times"<<endl;
        }
        fileout<<"     ";
        fileout<<tempTagger.getPlayerName()<<" had a total of "<<tempTagger.getNumTags();
        fileout<<" tags"<<endl;
    }
    fileout<<teamA.getTeamName()<<": "<<teamA.getTeamScore()<<" points"<<endl;

    fileout<<endl;
    fileout<<teamB.getTeamName()<<endl;
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
            fileout<<"     ";
            fileout<<tempTagger.getPlayerName()<<" tagged "<<tempTarget.getPlayerName();
            fileout<<" "<<count<<" times"<<endl;
        }
        fileout<<"     ";
        fileout<<tempTagger.getPlayerName()<<" had a total of "<<tempTagger.getNumTags();
        fileout<<" tags"<<endl;
    }
    fileout<<teamB.getTeamName()<<": "<<teamB.getTeamScore()<<" points"<<endl;
    fileout<<endl;
    if(teamA.getTeamScore()>teamB.getTeamScore()){
        fileout<<"Winners:  "<<teamA.getTeamName()<<endl;
    }else if(teamB.getTeamScore()>teamA.getTeamScore()){
        fileout<<"Winners:  "<<teamB.getTeamName()<<endl;
    }else{
        fileout<<"The Two Teams Tied"<<endl;
    }
    fileout.close();
}
Team LaserTagGame::processInputTeamFile(string inputFileName){
    
    //create a char ** with the lines of the file
    ifstream filein;
    filein.open(inputFileName);
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
    filein.open(inputMatchName);
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
        int tempGameTime=stoi(tempstr);
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
