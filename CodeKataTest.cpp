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
	CHECK(myCodeKata.mapToInt("NONEXISTANT") == -1);

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
	vector<string> kataDigits1 = myCodeKata.parseKataAcctNumber(kataTestAcctNum1);
	for(int i = 0; i < myCodeKata.ACCT_NUM_DIGITS ; i++){
		CHECK(myCodeKata.mapToInt(kataDigits1[i]) == kataTestAcctInts1[i]);
	};

	string kataTestAcctNum2 = "       _  _  _  _  _       "
							  "  |  |  ||_ |_| _||_ |_|  |"
							  "  |  |  | _| _| _||_|  |  |";
	int kataTestAccountInts2[] = {1,1,7,5,9,3,6,4,1};
	vector<string> kataDigits2 = myCodeKata.parseKataAcctNumber(kataTestAcctNum2);
	for(int j = 0; j < myCodeKata.ACCT_NUM_DIGITS ; j++){
		CHECK(myCodeKata.mapToInt(kataDigits2[j]) == kataTestAccountInts2[j]);
	};
}
