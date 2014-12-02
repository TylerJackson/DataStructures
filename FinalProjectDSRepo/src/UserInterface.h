/*
 * Owner: alex
 * History of changes:
 * Initially only a switch
 * 1st change: added maintenance mode object and controls
 * 2nd change: added interactive mode object and controls
 * Final changes: added stress test mode, comments, and changed format
 */

#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#include "DocumentParser.h"
#include "IndexIF.h"
#include "AVLIF.h"
#include "HashIF.h"

#include <string>
#include <iostream>
#include <istream>

using namespace std;

class UserInterface {
private:
	bool keepRunning; //boolean to determine whether the program should keep running
	int modeSwitch; //input integer to change the mode
	string documentName; //contains input document names
	string searchQuery; //contains the user's search query

public:
	DocumentParser docParser; //handles reading and parsing of XML documents
	IndexIF * indexIF; //handles loading the IFI and searching for queries, as well as output

	UserInterface();
	virtual ~UserInterface();

	/*
	 * Allows the user to switch between the 3 modes
	 */
	void run();

	/*
	 * Allows the user to add files to the index, or clear all files
	 */
	void maintenanceMode();

	/*
	 * Allows the user to load the index into an AVL tree or a hash table, and search for queries
	 */
	void interactiveMode();

	/*
	 * Allows the user to supply a file containing commands that can execute all the previous functions in order.
	 */
	void stressTestMode();
};

#endif
