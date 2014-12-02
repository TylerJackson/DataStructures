//============================================================================
// Name        : hw3.cpp
// Author      : TJ
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
	char temp [20]="balls";
	for(int i=0;i<6;i++){
		if(temp[i]== NULL){
			cout<<"yay"<<endl;
		}
		else
			cout<<temp[i]<<endl;
	}
	return 0;
}
