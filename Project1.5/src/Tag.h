/*
 * Tag.h
 *	This is my tag class, it holds all the data needed for each tag
 *  Created on: Sep 24, 2013
 *      Author: tgjackson
 */

#ifndef TAG_H_
#define TAG_H_


class Tag {
public:
	Tag();
	Tag(int tempTargetId,int tempTagSpot,int tempTagTime);
	Tag (const Tag& orig);
	Tag& operator=(const Tag& rhs);
	int calcScore(int tempSpot);
	int getTargetId();
	int getTagScore();
	virtual ~Tag();
private:
	int targetId;
	int tagSpot;
	int tagScore;
	int tagTime;
};

#endif /* TAG_H_ */
