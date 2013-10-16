/*
 * SortingCompetition main driver
 * CSE 2341
 * Spring 2013
 * Written by Jason Murphy
 */

#include <iostream>
#include <chrono>
#include "SortingCompetition.h"
using namespace std;
int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cerr << "Invalid arguments" << std::endl;
        std::cerr << "Usage: ./a.out <input file> <output file>" << std::endl;
        return 1;
    }

    //Number of times to run sort
    const int NUM_REPS = 5;
    unsigned int totalMilliseconds = 0;

    //Create the sorter object and load the data from a file
    SortingCompetition sorter(argv[1]);
    if (!sorter.readData())
    {
        std::cerr << "Error reading data" << std::endl;
        return 1;
    }

    for (int i = 0; i < NUM_REPS; i++)
    {
        //Load the unsorted data into our sorter object
        if (!sorter.prepareData())
        {
            std::cerr << "Error preparing data" << std::endl;
            return 1;
        }

        //Sort the data, and time the results
        chrono::time_point<chrono::system_clock> start, end;
        start = chrono::system_clock::now();
        sorter.sortData();
        end = chrono::system_clock::now();
        unsigned int milliseconds = chrono::duration_cast<chrono::milliseconds>(end-start).count();
        totalMilliseconds += milliseconds;
        std::cout << "Sort #" << i+1 << " Time: " << milliseconds << " milliseconds" << std::endl;
    }

    //Print sorted data to a file, and print the avg.
    sorter.outputData(argv[2]);
    std::cout << "Average sorting time: " << totalMilliseconds / NUM_REPS << " milliseconds" << std::endl;
}