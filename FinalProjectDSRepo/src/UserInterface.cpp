#include "UserInterface.h"
#include "StressTester.h"

using namespace std;

UserInterface::UserInterface() {
	keepRunning = 1;
	modeSwitch = 0;

}

UserInterface::~UserInterface() {

}

void UserInterface::run() {
	cout << "C++ Search Engine" << endl;

	while(keepRunning)
	{
		cout << "\nMain Menu:" << endl;
		cout << "1: Maintenance Mode" << endl;
		cout << "2: Interactive Mode" << endl;
		cout << "3: Stress Test Mode" << endl;
		cout << "4: Exit Program" << endl;
		cout << "Enter 1, 2, or 3 for mode, or 4 to exit program:";
		cin >> modeSwitch;
		switch(modeSwitch)
		{
		case 1:
			maintenanceMode();
			break;
		case 2:
			interactiveMode();
			break;
		case 3:
			stressTestMode();
			break;
		default:
			cout << "\nExiting Program!" << endl;
			keepRunning = 0;
			break;
		}
	}

}

void UserInterface::maintenanceMode() {
	cout << "\nMaintenance Mode" << endl;
	cout << "Enter 1 to add a file to the index." << endl;
	cout << "Enter 2 to clear the index." << endl;
	cout << "Enter 3 for main menu." << endl;
	cout << "Enter 1 or 2 for mode, or 3 for main menu:";
	cin >> modeSwitch;
	switch(modeSwitch)
	{
		case 1:
			cout << "\nEnter the filename of XML document you'd like to add:";
			cin >> documentName;
			docParser.add(documentName);
			break;
		case 2:
			cout << "\nClearing file index." << endl;
			docParser.clearIndex();
			break;
		default:
			cout << "\nReturning to main menu." << endl;
			break;
	}
}

void UserInterface::interactiveMode() {
	bool isLoaded = 0;
	bool stayInIntMode = true;
	while(stayInIntMode){
		cout << "\nInteractive Mode" << endl;
		cout << "Enter 1 to load the index into an AVL tree." << endl;
		cout << "Enter 2 to load the index into a hash table." << endl;
		cout << "Enter 3 to search the index." << endl;
		cout << "Enter 4 for main menu." << endl;
		cout << "Enter 1, 2, or 3 for search functions, or 4 for main menu:";
		cin >> modeSwitch;
		switch(modeSwitch)
		{
			case 1:
				cout << "\nLoading index into AVL tree." << endl;
				indexIF = new AVLIF();
				indexIF->index("/home/tgjackson/workspace/FinalProjectDSRepo/InvertedFileIndex.txt");
				//load into tree
				isLoaded = 1;
				break;
			case 2:
				cout << "\nLoading index into hash table." << endl;
				indexIF = new HashIF();
				indexIF->index("InvertedFileIndex.txt");
				//load into hash table
				isLoaded = 1;
				break;
			case 3:
				if(!isLoaded)
				{
					cout << "\nERROR: Index must be loaded into either AVL tree or hash table." << endl;
					break;
				}else{
				cout << "\nEnter a search query:";
				bool b = true;
				while(getline(cin,searchQuery) && b){
					b = false;
				}
				indexIF->search(searchQuery);
				}
				break;
			default:
				stayInIntMode = false;
				cout << "\nReturning to main menu." << endl;
				break;
		}
	}
}

void UserInterface::stressTestMode() {
	StressTester stressTester;
	cout << "\nStress Test Mode" << endl;
	cout << "Enter 1 to supply a command file." << endl;
	cout << "Enter 2 for main menu." << endl;
	cout << "Enter 1 to supply commands, or 2 for main menu:";
	cin >> modeSwitch;
	switch(modeSwitch)
	{
		case 1:
			cout << "\nEnter the filename of the command file:";
			cin >> documentName;
			stressTester.run(documentName);
			break;
		default:
			cout << "\nReturning to main menu." << endl;
			break;
	}
}
