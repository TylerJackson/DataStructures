/* Tyler Jackson
 * Date: Nov. 16, 2013
 * IndexIF.cpp
 *
 *			This is my parent class for my interfaces.  I overload all the functions so
 *		Theres no implimentation here.
 */

#include "IndexIF.h"

IndexIF::IndexIF() {
}

void IndexIF::search(string query) {
}

IndexIF::~IndexIF() {
}

void IndexIF::index(string filepath) {
}

void IndexIF::print() {
}

void IndexIF::setResultsFromBoolean(string allocator) {
}

void IndexIF::printResults() {
}

void IndexIF::printRankedResults() {
}

void IndexIF::rankResults(int numResultsFromAnd) {
}

void IndexIF::setTFIDFANDS(int docID, double& tfIDF, int numResultsFromAnd) {
}

void IndexIF::setTFIDFORS(int docID, double& tfIDF) {
}
