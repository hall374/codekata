/*
 * CodeKata.cpp
 *
 *  Created on: Mar 26, 2014
 *      Author: tim
 */
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tr1/unordered_map>
#include <typeinfo>
#include <vector>
#include "CodeKata.h"

using namespace std;

CodeKata::CodeKata() {
	// TODO Auto-generated constructor stub
	this->initEightSegToIntMap();
}

CodeKata::~CodeKata() {
	// TODO Auto-generated destructor stub
}

//Convert kata account number to string for output
//If the account number fails the checksum, add "ERR" to output string
//If the account number has formatting errors, add "ILL" to output string
//and use '?' for badly-formatted numbers
string CodeKata::acctNumToString(string kataAcctNum) {
	vector<int> kataParsedToInts = this->parseKataAcctNumber(kataAcctNum);
	bool formatError = false;
	stringstream acctNumStream;
	//Loop through the vector of integers, convert each to type string, and
	//add to acctNumString
	for(int i = 0; i < kataParsedToInts.size(); i++){
		//Check if the acct num had a format error upon input
		//Represented with -1
		if(kataParsedToInts[i] < 0){
			formatError = true;
			acctNumStream << '?';
		}
		else
			acctNumStream << kataParsedToInts[i];
	}
	if(formatError)
		acctNumStream << " ILL";
	else{
		if(!this->validateKataChecksum(kataParsedToInts))
			acctNumStream << " ERR";
	}

	return acctNumStream.str();
}

//Return the integer value corresponding to the string input
int CodeKata::mapToInt(string kataDigit) {
	std::tr1::unordered_map<string, int> kataMap = this->eightSegToIntMap;
	std::tr1::unordered_map<string, int>::const_iterator kataMapFindResults =  this->eightSegToIntMap.find(kataDigit);
	if(kataMapFindResults == kataMap.end()){
		return -1;
	}
	else{
		return kataMapFindResults->second;
	}
}

//Parse account number string input into separate digits
//Return as a vector of type int
vector<int> CodeKata::parseKataAcctNumber(string kataAcctNum){
	vector<string> kataAcctNumDigits;
	vector<int> kataParsedToInts;
	int numCharsPerLine = this->ACCT_NUM_DIGITS * this->TO_PARSE_PER_DIGIT;
	int startSubStrIndex;
	string parsed;
	//Loop through kataAcctNum and parse each string into digit
	for(int i = 0; i < this->NUM_LINES_PER_ACCT; i++){
		for(int j = 0; j < this->ACCT_NUM_DIGITS; j++){
			startSubStrIndex = (i * numCharsPerLine) + (j * this->TO_PARSE_PER_DIGIT);
			parsed = kataAcctNum.substr(startSubStrIndex, this->TO_PARSE_PER_DIGIT);
			if(i > 0)
				kataAcctNumDigits[j] += parsed;
			else
				kataAcctNumDigits.push_back(parsed);
		}
	}
	//Convert each parsed digit to an integer and add to kataParsedToInts vector
	for(int k = 0; k < kataAcctNumDigits.size(); k++)
		kataParsedToInts.push_back(this->mapToInt(kataAcctNumDigits[k]));
	return kataParsedToInts;
}

int CodeKata::processInput() {
	ifstream kataInputFile;
	string kataFilePath;
	while(!kataInputFile.is_open()){
		cout << "Enter absolute path to Code Kata input file: ";
		cin >> kataFilePath;
		kataInputFile.open(kataFilePath.c_str());
	}

	return 0;
}

//Validate account number with checksum
bool CodeKata::validateKataChecksum(vector<int> kataParsedToInts) {
	//Check if account is valid with checksum
	int total = 0;
	//Multiple of each acct digit starts at 9 for position d9
	//and decreases by 1 for each digit excluding d1
	int toMultiply = 9;
	//Don't include item at index 0 within the loop
	//Nothing is added to d9 (so i starts at 1)
	for(int i = 0; i < kataParsedToInts.size() - 2; i++) {
		total += toMultiply * kataParsedToInts[i];
		toMultiply--;
	}
	//Add d1 to total
	total += kataParsedToInts[kataParsedToInts.size() - 1];
	if(total % 11 == 0)
		return true;
	else
		return false;

}

//Add the string/value pairs to the hash map that
//will be used for converting file input to integers
void CodeKata::initEightSegToIntMap() {
	//Insert 0 to hash map
	eightSegToIntMap.insert(std::make_pair(" _ "
										   "| |"
										   "|_|", 0));
	//Insert 1 to hash map
	eightSegToIntMap.insert(std::make_pair("   "
										   "  |"
										   "  |", 1));
	//Insert 2 to hash map
	eightSegToIntMap.insert(std::make_pair(" _ "
										   " _|"
										   "|_ ", 2));
	//Insert 3 to hash map
	eightSegToIntMap.insert(std::make_pair(" _ "
										   " _|"
										   " _|", 3));

	//Insert 4 to hash map
	eightSegToIntMap.insert(std::make_pair("   "
										   "|_|"
										   "  |", 4));

	//Insert 5 to hash map
	eightSegToIntMap.insert(std::make_pair(" _ "
										   "|_ "
										   " _|", 5));

	//Insert 6 to hash map
	eightSegToIntMap.insert(std::make_pair(" _ "
										   "|_ "
										   "|_|", 6));

	//Insert 7 to hash map
	eightSegToIntMap.insert(std::make_pair(" _ "
										   "  |"
										   "  |", 7));

	//Insert 8 to hash map
	eightSegToIntMap.insert(std::make_pair(" _ "
										   "|_|"
										   "|_|", 8));

	//Insert 9 to hash map
	eightSegToIntMap.insert(std::make_pair(" _ "
										   "|_|"
										   " _|", 9));
}

