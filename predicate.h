//
//  predicate.h
//  dataLog
//
//  Created by Trevor Schmidt on 10/2/19.
//  Copyright © 2019 Trevor Schmidt. All rights reserved.
//

#ifndef predicate_h
#define predicate_h

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class predicate
{
public:
    	predicate () {}

    	void setID(string input) {
        	ID = input;
    	}

    	void addParameter(string input) {
        	parameterVector.push_back(input);
    	}

    	void setParameters(vector <string> inputVect) {
        	parameterVector = inputVect;
    	}

    	string getPredicate() {
        	string os = ID + "(" + parameterVector.at(0);
        	for (unsigned int i = 1; i < parameterVector.size(); i++)
        	{
            		os += "," + parameterVector.at(i);
        	}
        	os += ")";
        	return os;
    	}

	string getID() {
		return ID;
	}

	vector<string> getParameterList() {
		return parameterVector;
	}

private:
    	string ID;
    	vector<string> parameterVector;
};

#endif /* predicate_h */
