/*
 * Owner: alex
 * subclass of user interface, can use all members
 * History of all changes:
 * Added ability to read stressTest file
 * Added ability to execute actions
 * Added chrono to time functions
 */

#ifndef STRESSTESTER_H_
#define STRESSTESTER_H_

#include "UserInterface.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>

class StressTester : public UserInterface {
private:
	ifstream ifs;
	string input;
public:
	StressTester();
	virtual ~StressTester();

	void run(std::string);
};

#endif
