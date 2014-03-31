/*
 * CodeKata.h
 *
 *  Created on: Mar 26, 2014
 *      Author: tim
 */
#include <tr1/unordered_map>
#include <string>
#include <vector>
#ifndef CODEKATA_H_
#define CODEKATA_H_

using namespace std;

class CodeKata {
public:
	int NUM_LINES_PER_ACCT = 3;
	int ACCT_NUM_DIGITS = 9;
	//Number of characters to parse per digit per input line
	int TO_PARSE_PER_DIGIT = 3;
	CodeKata();
	virtual ~CodeKata();
	string acctNumToString(string kataAcctNum);
	int mapToInt(string kataInput);
	vector<int> parseKataAcctNumber(string kataAcctNum);
	int processInput();
	bool validateKataChecksum(vector<int> kataParsedToInts);
private:
	//Eight segment display string to integer map
	std::tr1::unordered_map<string, int> eightSegToIntMap;
	void initEightSegToIntMap();
};


#endif /* CODEKATA_H_ */
