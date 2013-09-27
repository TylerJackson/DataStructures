//============================================================================
// Name        : 5.cpp
// Author      : TJ
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "LaserTagGame.h"
using namespace std;

int main(int argc, const char * argv[]) {
	//test tag class
	//are constructors created correctly, and do the getters work correctly
	cout<<endl;
	cout<<"---------------------TAG TESTER-------------------"<<endl;
	cout<<endl;
	cout<<endl;
	Tag a(5,2,1234);
	Tag b=a;
	b=a;
	Tag c(10,4,11111);
	Tag d(c);
	cout<<"My tag target is: "<<a.getTargetId()<<" (should say 5)"<<endl;
	cout<<"    My tag score is: "<<a.getTagScore()<<" (should say 8)"<<endl;
	cout<<"My tag target is: "<<b.getTargetId()<<" (should say 5)"<<endl;
	cout<<"    My tag score is: "<<b.getTagScore()<<" (should say 8)"<<endl;
	cout<<"My tag target is: "<<c.getTargetId()<<" (should say 10)"<<endl;
	cout<<"    My tag score is: "<<c.getTagScore()<<" (should say 20)"<<endl;
	cout<<"My tag target is: "<<d.getTargetId()<<" (should say 15)"<<endl;
	cout<<"    My tag score is: "<<d.getTagScore()<<" (should say 25)"<<endl;
	cout<<endl;
	cout<<endl;
	//test player class
	//are constructors set correctly, are tags getting added correctly, and
	//are getters working right
	cout<<"-----------------------PLAYER TESTER--------------------"<<endl;
	cout<<endl;
	cout<<endl;
	Tag aa(1,4,12555);
	Tag ab(1,4,12553);
	Tag ac(2,4,12522);
	Tag ad(2,4,125);
	Tag ae(2,1,155);
	Tag af(4,3,125553);
	Tag ag(5,1,1257);
	Tag ah(5,1,1257);
	Tag ai(6,3,1257);
	Tag aj(6,4,1257);
	Tag ak(6,2,1257);
	Tag al(6,1,1257);
	Player joe("Joe",1);   //on team with 4,5
	Player Font("Mark",2);
	Player Abe("Abe",3);
	Player Tyler("Tyler",4);  //on team with 6,3,
	Player Harry("Harrison",5);
	Player Jason("Jason",6);
	//just make sure none of the tags are assigned to tagging themself
	joe.addTag(af); //tagged Tyler worth 10
	joe.addTag(ag); //tagged Harrison worth 5
	Font.addTag(ah);//tagged Harrison worth 5
	joe.addTag(ai);//tagged Jason worth 10
	Font.addTag(aj);//tagged Jason worth 15
    Font.addTag(ak);//tagged Jason worth 8
    Font.addTag(al);//tagged Jason worth 5
	Tyler.addTag(aa);//tagged Joe worth 15
	Tyler.addTag(ab);//tagged Joe worth 15
	Harry.addTag(ac);//tagged Mark worth 15
	Jason.addTag(ad);//tagged Mark worth 15
	Jason.addTag(ae);//tagged Mark worth 5
	cout<<"My name is "<<joe.getPlayerName()<<".  My player ID is "<<joe.getPlayerId()<<" and I had"<<endl;
	cout<<"    "<<joe.getNumTags()<<" tags."<<" My score is "<<joe.getPlayerScore()<<"."<<endl;
	cout<<"This should say (My name is Joe.  My player ID is 1 and I had 3 tags. My score is 25.)"<<endl;
	cout<<endl;
	cout<<"My name is "<<Tyler.getPlayerName()<<".  My player ID is "<<Tyler.getPlayerId()<<" and I had"<<endl;
	cout<<"    "<<Tyler.getNumTags()<<" tags."<<" My score is "<<Tyler.getPlayerScore()<<"."<<endl;
	cout<<"This should say (My name is Tyler.  My player ID is 4 and I had 2 tags. My score is 30.)"<<endl;
	cout<<endl;
	cout<<"My name is "<<Harry.getPlayerName()<<".  My player ID is "<<Harry.getPlayerId()<<" and I had"<<endl;
	cout<<"    "<<Harry.getNumTags()<<" tags."<<" My score is "<<Harry.getPlayerScore()<<"."<<endl;
	cout<<"This should say (My name is Harrison.  My player ID is 5 and I had 1 tags. My score is 15.)"<<endl;
	cout<<endl;
	cout<<"My name is "<<Font.getPlayerName()<<".  My player ID is "<<Font.getPlayerId()<<" and I had"<<endl;
	cout<<"    "<<Font.getNumTags()<<" tags."<<" My score is "<<Font.getPlayerScore()<<"."<<endl;
	cout<<"This should say (My name is Mark.  My player ID is 2 and I had 4 tags. My score is 33.)"<<endl;
	cout<<endl;
	cout<<"My name is "<<Abe.getPlayerName()<<".  My player ID is "<<Abe.getPlayerId()<<" and I had"<<endl;
	cout<<"    "<<Abe.getNumTags()<<" tags."<<" My score is "<<Abe.getPlayerScore()<<"."<<endl;
	cout<<"This should say (My name is Abe.  My player ID is 3 and I had 0 tags. My score is 0.)"<<endl;
	cout<<endl;
	cout<<"My name is "<<Jason.getPlayerName()<<".  My player ID is "<<Jason.getPlayerId()<<" and I had"<<endl;
	cout<<"    "<<Jason.getNumTags()<<" tags."<<" My score is "<<Jason.getPlayerScore()<<"."<<endl;
	cout<<"This should say (My name is Jason.  My player ID is 6 and I had 2 tags. My score is 20.)"<<endl;
	cout<<endl;
	cout<<endl;
	//test the team class tests constructor as well as whether or not the players are getting
	//added correctly.  Also tests whether or not the score is what it should be
	cout<<"-----------------------TEAM TESTER--------------------"<<endl;
	cout<<endl;
	cout<<endl;
	Team freak("The Freakers");
	Team pluck("The Pluckers");
	freak.addPlayer(joe);
	freak.addPlayer(Font);
	freak.addPlayer(Abe);
	pluck.addPlayer(Tyler);
	pluck.addPlayer(Harry);
	pluck.addPlayer(Jason);
	cout<<"The first team's name is "<<freak.getTeamName()<<".  There are ";
	cout<<freak.getNumPlayers()<<" players on the team."<<endl;
	cout<<"    Our Score is "<<freak.getTeamScore()<<"."<<endl;
	cout<<"The second team's name is "<<pluck.getTeamName()<<".  There are ";
	cout<<pluck.getNumPlayers()<<" players on the team."<<endl;
	cout<<"    Our Score is "<<pluck.getTeamScore()<<"."<<endl;
	cout<<"(Should say that the first team name is The Freakers and the second team is The Pluckers.)"<<endl;
	cout<<"(Freakers have 3 players and score is 58.  Pluckers have 4 players and score is 80.)"<<endl;
    /*make sure the first arg is the team A text file
                    second arg is the team B text file
                    third arg is the match file
                    fourth arg is the file you want the results to but output to
                    fifth argument is the detail level of the output*/
	LaserTagGame game=LaserTagGame(argv[1], argv[2], argv[3]);

    if(strcmp(argv[5],"vlow")==0){
        game.printVLow(argv[4]);
    }else if(strcmp(argv[5],"vmed")==0){
        game.printVMed(argv[4]);
    }else if(strcmp(argv[5],"vhigh")==0){
        game.printVHigh(argv[4]);
    }
    return 0;
}
