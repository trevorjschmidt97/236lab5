//
//  dataLog.h
//  dataLog
//
//  Created by Trevor Schmidt on 10/2/19.
//  Copyright © 2019 Trevor Schmidt. All rights reserved.
//

#ifndef dataLog_h
#define dataLog_h

#include <stdio.h>
#include <vector>
#include <iostream>
#include "token.h"
#include "predicate.h"
#include "rule.h"

using namespace std;

class dataLog
{
public:
	dataLog(void){};

	void executeDataLog() {
		datalogProgram();
	}

   	void setVect(vector <token*> vect) {
		tokenVect = vect;
   	}


	vector <predicate*> getSchemeVect() {
		return schemeVect;
	}
	vector <predicate*> getFactVect() {
		return factVect;
	}
	vector <predicate*> getQuerieVect() {
		return querieVect;
	}
	vector <rule*> getRuleVect() {
		return ruleVect;
	}
	vector <predicate*> getRulePredVect() {
		return rulePredVect;
	}


private:
   	vector <token*> tokenVect;
    	vector <predicate*> schemeVect;
    	vector <predicate*> factVect;
    	vector <predicate*> querieVect;
    	vector <predicate*> rulePredVect;
    	vector <rule*> ruleVect;
    	vector <string> domainVect;
    	vector <string> idListStrings;
    	vector <string> factListStrings;
    	vector <string> ruleListStrings;
    	vector <string> parameterStrings;

    	bool forexpression = false;
    	string expressionString = "";

    	void checkNPop(string);
    	void datalogProgram();
    	void schemeList();
    	void factList();
    	void ruleList();
    	void queryList();
    	void scheme();
    	void fact();
    	void ruleMethod();
    	void query();
    	predicate* headPredicate();
    	predicate* predicateMethod();
    	void predicateList();
    	void parameterList();
    	void stringList();
    	void idList();
    	void parameter();
    	void expression();
    	void operate();
};

#endif /* dataLog_h */
