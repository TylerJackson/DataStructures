//
//  Tag.cpp
//  TJackson
//  Each Tag holds the data from the match file
//  -who shot it, who got shot, when it happened, and how much it was worth
#include "Tag.h"
#include <string>
#include <cstring>

Tag::Tag(int id1,int id2, int time, int spot){
    taggerid=id1;
    taggedid=id2;
    tagtime=time;
    tagspot=spot;
    tagScore=calcTagScore();
}
Tag::Tag(){
    taggerid=0;
    taggedid=0;
    tagtime=0;
    tagspot=0;
    tagScore=0;
}
int Tag::calcTagScore(){
    if(this->tagspot ==1){
        return 5;
    }
    else if(this->tagspot == 2){
        return 8;
    }
    else if(this->tagspot == 3){
        return 10;
    }
    else{
        return 15;
    }
}
int Tag::getTagScore(){
    return tagScore;
}
int Tag::getTaggedId(){
    return taggedid;
}
int Tag::getTaggerId(){
    return taggerid;
}
int Tag::getTagSpot(){
    return tagspot;
}
int Tag::getTagTime(){
    return tagtime;
}

