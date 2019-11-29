#ifndef interpreter_h
#define interpreter_h

#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "database.h"
#include "dataLog.h"
#include "predicate.h"
#include "relation.h"
#include "rule.h"

using namespace std;

class interpreter
{
public:
	interpreter(void){};

	//for Queries
	void executeInterpreter();
	relation interpretQuerie(predicate* querie);

	void setSchemeVect(vector<predicate*> x) {
		this->schemeVect = x;
	}

	void setFactVect(vector<predicate*> x) {
		this->factVect = x;
	}

	void setQuerieVect(vector<predicate*> x) {
		this->querieVect = x;
	}

	void setRuleVect(vector<rule*> x) {
		this->ruleVect = x;
	}

	void setRulePredVect(vector<predicate*> x) {
		this->rulePredVect = x;
	}

private:
	vector<predicate*> schemeVect;
	vector<predicate*> factVect;
	vector<predicate*> querieVect;
	vector<predicate*> rulePredVect;
	vector<rule*> ruleVect;

	database relationMap;

	bool success;
};

#endif //interpreter_h
