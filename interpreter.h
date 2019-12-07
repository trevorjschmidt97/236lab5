#ifndef interpreter_h
#define interpreter_h

#include <bits/stdc++.h>
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
#include "node.h"

using namespace std;

class interpreter
{
public:
	interpreter(void){};

	void dfsR(node* n);
	void dfsP(node* n);

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

	map<int, node> dependencyMap;
	map<int, node> reverseMap;

	bool success;
	int postNum = 0;

	vector<int> sccIntVect;
	vector<vector<int>> sccVect;
};

#endif //interpreter_h
