/*
 * CodeKata.cpp
 *
 *  Created on: Mar 26, 2014
 *      Author: tim
 */
#include <exception>
#include <iostream>
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

//Parse account number string input into separate digits
//Return as an array of type string
vector<string> CodeKata::parseKataAcctNumber(string kataAcctNum){
	vector<string> kataAcctNumDigits;
	//int * kataAcctNumDigits = (int *)malloc(10*sizeof(int));
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
	return kataAcctNumDigits;
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

//Add the string/value pairs to the hash map that
//will be used for converting file input to integers
void CodeKata::initEightSegToIntMap() {
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

