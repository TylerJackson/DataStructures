//============================================================================
// Name        : HW2.cpp
// Author      : TJ
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <math.h>
#include <ctime>
#include <cstring>
#include <chrono>
using namespace std;

int exponentiation(int base, int power);
void printFigure(int m,int n);
void printNumToWord(int number);
int sumArray(int* arr,int length);
void calcFibonacci(int n,unsigned long long one,unsigned long long two);
bool isEqualTo(char * a, char* b,int index);

int main() {
	//problem 1
	int base=2;
	int power=16;
	cout<<"The answer should be: "<<pow(2,16)<<endl;
	cout<<"    The answer using my function is: "<<exponentiation(base,power)<<endl;
	cout<<endl;

	//problem 2
	printFigure(10,4);
	cout<<endl;

	//problem 3
	printNumToWord(44444);
	cout<<endl;

	//problem 4
	int arr[4]={1,252,10,4};
	cout<<sumArray(arr,4)<<endl;
	cout<<endl;

	//problem 5
	int n=95000;
	chrono::high_resolution_clock::period::den;
	auto start_time = chrono::high_resolution_clock::now();
	calcFibonacci(n,0,1);
	auto end_time = chrono::high_resolution_clock::now();
	unsigned int totalSeconds = chrono::duration_cast<chrono::seconds>(end_time-start_time).count();
	unsigned int totalMilliseconds = chrono::duration_cast<chrono::milliseconds>(end_time-start_time).count();
	cout<<endl;
	cout<<"The Time it took was: "<<totalMilliseconds<<" millisecs"<<endl;
	cout<<"The Time it took was: "<<totalSeconds<<" secs"<<endl;
	cout<<endl;

	//problem 6
	char * a="apples";
	char * b="apples";
	cout<<"Are these two words equal (if yes 1, if no 0): "<<isEqualTo(a,b,0);
	cout<<endl;
	return 0;
}

int exponentiation(int base, int power){
	if(power==0){
		return 1;
	}else if(power==1){
		return base;
	}else if(power==2){
		return base*base;
	}else{
		if(power%2 != 0)
			return base*exponentiation(base,power/2)*
					exponentiation(base,power/2);
		else{
			return exponentiation(base,power/2)*
					exponentiation(base,power/2);
		}
	}
}
void printFigure(int m,int n){
	if(m==n){
		for(int i=0;i<m;i++){
			cout<<"*";
		}
		cout<<endl;
	}else{
		for(int i=0;i<m;i++){
			cout<<"*";
		}
		cout<<endl;
		printFigure(m-1,n);
	}
	for(int i=0;i<m;i++){
		cout<<"*";
	}
	cout<<endl;
}
void printNumToWord(int number){
	if(number!=0){
		int tens=1;
		while(number/tens!=0){
			tens=tens*10;
		}
		tens/=10;
		if(number/tens==1){
			cout<<"one ";
		}else if(number/tens==2){
			cout<<"two ";
		}else if(number/tens==3){
			cout<<"three ";
		}else if(number/tens==4){
			cout<<"four ";
		}else if(number/tens==5){
			cout<<"five ";
		}else if(number/tens==6){
			cout<<"six ";
		}else if(number/tens==7){
			cout<<"seven ";
		}else if(number/tens==8){
			cout<<"eight ";
		}else if(number/tens==9){
			cout<<"nine ";
		}else if(number/tens==0){
			cout<<"zero ";
		}
		while(number-number/tens*tens < tens/10){
			cout<<"zero ";
			tens/=10;
		}
		printNumToWord(number%tens);
	}
}
int sumArray(int* arr,int length){
	if(length-1 == 0){
		return arr[0];
	}else{
		return arr[length-1]+sumArray(arr,length-1);
	}
}
void calcFibonacci(int n,unsigned long long one,unsigned long long two){
	if(n==1 && one==0){
		cout<<"0 "<<endl;
	}else if(n==2  && one==0){
		cout<<"0 1 "<<endl;
	}else if(n>2 && one==0){
		cout<<"0 1 "<<endl;
	}else{
		cout<<two<<" "<<endl;
	}
	if(n>=3){
		calcFibonacci(n-1,two,one+two);
	}
}
bool isEqualTo(char * a, char* b, int index){
	if(strlen(a)!= strlen(b))
		return false;
	if(index==strlen(a)){
		return true;
	}else{
		if(a[index]==b[index]){
			isEqualTo(a,b,index+1);
		}else{
			return false;
		}
	}
}




