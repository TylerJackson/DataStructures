####################################################
#
#               makefile for Project 3
#
#               Tyler Jackson
#               Math 3316
#               11/5/2013
####################################################


# make file targets

all:    BEERTESTER.exe

BEERTESTER.exe : HashTab.cpp RapidDocParser.cpp Word.cpp BEERTESTER.cpp
				g++ $^ -o $@ -std=c++11 -lpthread               

clean : 
				\rm -f *.exe *~

realclean : clean
				\rm -f *.exe *~

############ End of Makefile ##############
                