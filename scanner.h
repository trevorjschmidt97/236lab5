//
//  scanner.h
//  dataLog
//
//  Created by Trevor Schmidt on 10/2/19.
//  Copyright © 2019 Trevor Schmidt. All rights reserved.
//

#ifndef scanner_h
#define scanner_h

#include <stdio.h>
#include <iostream>
#include "token.h"
#include <vector>
#include <string>

using namespace std;

class scanner {
public:
	scanner(string input) {
        	file = input;
    	}

    	void executeLexer();


    	void toString() {
        	unsigned int tokenCount = 0;
        	for (unsigned int i = 0; i < tokenVect.size(); ++i) {
            		cout << "(" << tokenVect.at(i)->getName() << ",\"" << tokenVect.at(i)->getValue()
                 	     << "\"," << tokenVect.at(i)->getLine() << ")" << endl;
            		++tokenCount;
        	}
        	cout << "Total Tokens = " << tokenCount << endl;
    	}

    	vector<token*> getVect() {
        	return tokenVect;
    	}

    	void deleteVector() {
        	for (unsigned int i = 0; i < tokenVect.size(); ++i) {
            		delete tokenVect.at(i);
        	}
    	}
private:
    	string file;
    	vector<token*> tokenVect;

    	void createToken(string a, string b, int c) {
        	token* newToken = new token(a, b, c);
        	tokenVect.push_back(newToken);
    	}
};

#endif /* scanner_h */
