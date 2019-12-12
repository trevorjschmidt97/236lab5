//
//  main.cpp
//  dataLog
//
//  Created by Trevor Schmidt on 9/18/19.
//  Copyright © 2019 Trevor Schmidt. All rights reserved.
//

//#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include "scanner.h"
#include "dataLog.h"
#include "interpreter.h"

using namespace std;
//using namespace std::chrono;

int main(int argc, const char * argv[]) {

	//auto start = high_resolution_clock::now();

	//Create string in which to read the file
    	string input;

	//Create and open the file
    	ifstream fin;
    	fin.open(argv[1]);

    	//Reads in entire file to string
    	while (getline(fin, input, '\0')) {}

    	//Passes the entire file to the scanner LAB 1
    	scanner lexer(input);
      	//Creates a vector of tokens
    	lexer.executeLexer();

	//Uses the tokens to create a datalog program LAB 2
	dataLog parser;
	parser.setVect(lexer.getVect());
	parser.executeDataLog();

	//Uses the datalog program to interpret the queries LAB 3
	interpreter interpreterr;
	interpreterr.setSchemeVect(parser.getSchemeVect());
	interpreterr.setFactVect(parser.getFactVect());
	interpreterr.setQuerieVect(parser.getQuerieVect());
	interpreterr.setRuleVect(parser.getRuleVect());
	interpreterr.setRulePredVect(parser.getRulePredVect());


	interpreterr.executeInterpreter();


	//lexer.toString();

    	lexer.deleteVector();

	//auto stop = high_resolution_clock::now();
	//auto duration = duration_cast<seconds>(stop - start);
	//cout << "Time taken by program: " << duration.count() << " seconds" << endl;
	//cout << "Or " << duration.count()/60 << " minutes" << endl;

	return 0;
}
