/*
 * CodeKataTest.cpp
 *
 *  Created on: Mar 26, 2014
 *      Author: tim
 */
#include "CodeKata.h"

#include <iostream>
#include <CppUTest/TestHarness.h>

using namespace std;

TEST_GROUP(CodeKata){
};

//Test whether each possible string expected from
//input file exists in the CodeKata hash map
//Expect -1 if the key does not exist
TEST(CodeKata, ValidateKataInputToIntConversion){
	CodeKata myCodeKata;

	CHECK(myCodeKata.mapToInt(" _ "
							  "| |"
							  "|_|") == 0);

	CHECK(myCodeKata.mapToInt("   "
							  "  |"
							  "  |") == 1);
	CHECK(myCodeKata.mapToInt(" _ "
							  " _|"
							  "|_ ") == 2);
	CHECK(myCodeKata.mapToInt(" _ "
							  " _|"
							  " _|") == 3);
	CHECK(myCodeKata.mapToInt("   "
							  "|_|"
							  "  |") == 4);
	CHECK(myCodeKata.mapToInt(" _ "
							  "|_ "
							  " _|") == 5);
	CHECK(myCodeKata.mapToInt(" _ "
							  "|_ "
							  "|_|") == 6);
	CHECK(myCodeKata.mapToInt(" _ "
							  "  |"
							  "  |") == 7);
	CHECK(myCodeKata.mapToInt(" _ "
							  "|_|"
							  "|_|") == 8);
	CHECK(myCodeKata.mapToInt(" _ "
							  "|_|"
							  " _|") == 9);
	//Expect -1 return if input matches no key in the unordered map
	CHECK(myCodeKata.mapToInt("NONEXISTENT") == -1);

}

//Validate account number input is parsed into separate digits
//correctly using randomly-selected possible account numbers
TEST(CodeKata, ValidateParseKataAcctNumber){
	CodeKata myCodeKata;
	//Create string and associated array of integers to test mapping
	//of digits

	string kataTestAcctNum1 = " _  _  _     _     _  _  _ "
							  " _||_ |_|  ||_||_|  | _||_ "
							  " _| _| _|  ||_|  |  ||_ |_|";
	int kataTestAcctInts1[] = {3,5,9,1,8,4,7,2,6};
	//Parse kataTestAcctNum1 into vector of integers
	vector<int> kataDigits1 = myCodeKata.parseKataAcctNumber(kataTestAcctNum1);
	//Check that each parsed digit matches each digit in kataTestAcctInts1
	for(int i = 0; i < myCodeKata.ACCT_NUM_DIGITS ; i++){
		CHECK(kataDigits1[i] == kataTestAcctInts1[i]);
	};

	string kataTestAcctNum2 = "       _  _  _  _  _       "
							  "  |  |  ||_ |_| _||_ |_|  |"
							  "  |  |  | _| _| _||_|  |  |";
	int kataTestAccountInts2[] = {1,1,7,5,9,3,6,4,1};
	vector<int> kataDigits2 = myCodeKata.parseKataAcctNumber(kataTestAcctNum2);
	for(int j = 0; j < myCodeKata.ACCT_NUM_DIGITS ; j++){
		CHECK(kataDigits2[j] == kataTestAccountInts2[j]);
	};

	string kataTestAcctNum3 = "    _  _  _  _  _  _  _  _ "
							  "|_||_   ||_ | ||_|| || || |"
							  "  | _|  | _||_||_||_||_||_|";
	int kataTestAccountInts3[] = {4,5,7,5,0,8,0,0,0};
	vector<int> kataDigits3 = myCodeKata.parseKataAcctNumber(kataTestAcctNum3);
	for(int j = 0; j < myCodeKata.ACCT_NUM_DIGITS ; j++){
		CHECK(kataDigits3[j] == kataTestAccountInts3[j]);
	};
}

//Validate account number passes checksum
TEST(CodeKata, ValidateKataChecksum){
	CodeKata myCodeKata;
	//Test that valid account number passes (returns true)
	string validAcct =  "    _  _  _  _  _  _  _  _ "
						"|_||_   ||_ | ||_|| || || |"
						"  | _|  | _||_||_||_||_||_|";
	vector<int> validAcctToInts = myCodeKata.parseKataAcctNumber(validAcct);
	for(int i = 0; i < validAcctToInts.size()-1; i++)
		cout << "&" + validAcctToInts[i];
	CHECK(myCodeKata.validateKataChecksum(validAcctToInts) == true);

	//Test that invalid account number fails (returns false)
	string invalidAcct = " _  _     _  _        _  _ "
						 "|_ |_ |_| _|  |  ||_||_||_ "
						 "|_||_|  | _|  |  |  | _| _|";

	vector<int> invalidAcctToInts = myCodeKata.parseKataAcctNumber(invalidAcct);
	CHECK(myCodeKata.validateKataChecksum(invalidAcctToInts) == false);
}

//Validate output of account numbers into string for output
TEST(CodeKata, ValidateAcctNumToString){
	CodeKata myCodeKata;
	//Test that valid acct number is formatted properly
	string validAcct =  "    _  _  _  _  _  _  _  _ "
						"|_||_   ||_ | ||_|| || || |"
						"  | _|  | _||_||_||_||_||_|";
	string expectedValidOutput = "457508000";
	vector<int> validAcctToInts = myCodeKata.parseKataAcctNumber(validAcct);
	CHECK(myCodeKata.validateKataChecksum(validAcctToInts) == true);
	CHECK(myCodeKata.acctNumToString(validAcct).compare(expectedValidOutput) == 0);
	//Test that acct number that fails checksum is output properly
	//Displays ERR with acct number
	//Test that invalid account number fails (returns false)
	string invalidAcct = " _  _  _     _     _  _  _ "
						 " _||_ |_|  ||_||_|  | _||_ "
						 " _| _| _|  ||_|  |  ||_ |_|";
	string expectedInvalidOutput = "359184726 ERR";
	CHECK(myCodeKata.acctNumToString(invalidAcct).compare(expectedInvalidOutput) == 0);
	//Test that acct number with eror upon input is output properly
	//Displays ILL with acct number
	//Test that invalid account number fails (returns false)
	string ILLAcct = " _  _  _     _     _     _ "
						 " _|   |_|  ||_||_   | _||_ "
						 " _| _| _   ||_|  |  ||_ |_|";
	string expectedILLOutput = "3??18?7?6 ILL";
	CHECK(myCodeKata.acctNumToString(ILLAcct).compare(expectedILLOutput) == 0);
}

