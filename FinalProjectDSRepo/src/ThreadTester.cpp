/*
 * ThreadTester.cpp
 *
 *  Created on: Dec 9, 2013
 *      Author: tgjackson
 */
#include <thread>
#include <iostream>

using namespace std;

void balls(){
	cout << "this sucks" << endl;
}
int main(){

	thread t(balls);
	t.join();
	return 0;
}
