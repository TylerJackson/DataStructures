/*
 * Tag.cpp
 *
 *  Created on: Sep 24, 2013
 *      Author: tgjackson
 */

#include "Tag.h"

namespace std {

Tag::Tag(){
	targetId=0;
	tagSpot=0;
	tagScore=0;
	tagTime=0;
}

Tag::Tag(int tempTargetId, int tempTagSpot, int tempTagTime) {
	targetId=tempTargetId;
	tagSpot=tempTagSpot;
	tagScore=calcScore(tagSpot);
	tagTime=tempTagTime;
}

Tag::Tag(const Tag& orig) {
	this->targetId=orig.targetId;
	this->tagSpot=orig.tagSpot;
	this->tagScore=orig.tagScore;
	this->tagTime=orig.tagTime;
}
Tag& Tag::operator= (const Tag& rhs) {
	this->targetId=rhs.targetId;
	this->tagSpot=rhs.tagSpot;
	this->tagScore=rhs.tagScore;
	this->tagTime=rhs.tagTime;
	return *this;
}

int Tag::calcScore(int tempSpot) {
	if(tempSpot==1){
		return 5;
	}else if(tempSpot==2){
		return 8;
	}else if(tempSpot==3){
		return 10;
	}else {//tempSpot=4
		return 15;
	}
}

int Tag::getTargetId() {
	return targetId;
}

int Tag::getTagScore() {
	return tagScore;
}

Tag::~Tag() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
