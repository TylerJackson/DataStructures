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
    this->calcTagScore();
}
Tag::Tag(){
    taggerid=0;
    taggedid=0;
    tagtime=0;
    tagspot=0;
    tagScore=0;
}
void Tag::calcTagScore(){
    if(this->tagspot ==1){
        tagScore=5;
    }
    else if(this->tagspot == 2){
        tagScore=8;
    }
    else if(this->tagspot == 3){
        tagScore=10;
    }
    else{
        tagScore=15;
    }
}
int Tag::getTagScore(){
    return tagScore;
}
int Tag::getTaggedId(){
    return taggedid;
}