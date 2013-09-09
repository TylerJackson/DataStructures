//
//  Tag.h
//  TJackson
//  Each Tag holds the data from the match file
//  -who shot it, who got shot, when it happened, and how much it was worth
#ifndef __TJackson__Tag__
#define __TJackson__Tag__
#include <iostream>
class Tag
{
public:
    Tag(int taggerid, int taggedid,int tagtime, int tagspot);
    Tag();
    void calcTagScore();
    int getTagScore();
    int getTaggedId();
private:
    int taggerid;
    int taggedid;
    int tagtime;
    int tagspot;
    int tagScore;
};
#endif /* defined(__TJackson__Tag__) */
