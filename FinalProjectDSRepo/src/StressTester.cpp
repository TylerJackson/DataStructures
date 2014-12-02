#include "StressTester.h"

StressTester::StressTester() {

}

StressTester::~StressTester() {

}

void StressTester::run(string filename) {
	ifs.open(filename);
	while(ifs.good())
	{
		if(!getline(ifs, input))
			break;
		istringstream ss(input);
		std::vector<std::string> line;
		while (ss)
		{
			std::string s;
			if(!getline(ss, s, ' '))
				break;
			line.push_back(s);
		}
		if(line[0] == "addDocs")
		{
			std::chrono::time_point<std::chrono::system_clock> start, end;
			cout << "Adding document to index took: ";
			start = std::chrono::system_clock::now();
			UserInterface::docParser.add(line[1]);
			end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsedSeconds = end-start;
			cout << elapsedSeconds.count() << " seconds." << endl;
		}
		else if(line[0] == "clearIndex")
		{
			std::chrono::time_point<std::chrono::system_clock> start, end;
			cout << "Clearing file index took: ";
			start = std::chrono::system_clock::now();
			UserInterface::docParser.clearIndex();
			end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsedSeconds = end-start;
			cout << elapsedSeconds.count() << " seconds." << endl;
		}
		else if(line[0] == "AVLtree")
		{
			std::chrono::time_point<std::chrono::system_clock> start, end;
			cout << "Loading AVL tree took: ";
			start = std::chrono::system_clock::now();
			UserInterface::indexIF = new AVLIF();
			UserInterface::indexIF->index("InvertedFileIndex.txt");
			end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsedSeconds = end-start;
			cout << elapsedSeconds.count() << " seconds." << endl;
		}
		else if(line[0] == "hashTable")
		{
			std::chrono::time_point<std::chrono::system_clock> start, end;
			cout << "Loading hash table took: ";
			start = std::chrono::system_clock::now();
			UserInterface::indexIF = new HashIF();
			UserInterface::indexIF->index("InvertedFileIndex.txt");
			end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsedSeconds = end-start;
			cout << elapsedSeconds.count() << " seconds." << endl;
		}
		else if(line[0] == "query")
		{
			string theQuery;
			for(unsigned int i=1; i<line.size(); i++)
				theQuery += (line[i] + " ");
			std::chrono::time_point<std::chrono::system_clock> start, end;
			cout << "Searching query took: ";
			start = std::chrono::system_clock::now();
			UserInterface::indexIF->search(theQuery);
			end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsedSeconds = end-start;
			cout << elapsedSeconds.count() << " seconds." << endl;
		}
		else
		{
			cout << "\nInvalid command in file, returning to menu." << endl;
			return;
		}
	}
	ifs.close();
}
