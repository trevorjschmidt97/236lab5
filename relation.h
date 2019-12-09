#ifndef relation_h
#define relation_h

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include "Tuple.h"

using namespace std;

class relation
{
public:
	relation(){}
	void setName(string input) {
		name = input;
	}
	string getName() {
		return name;
	}
	void setAttribute(vector<string> input) {
		attributeNames = input;
	}
	vector<string> getAttribute() {
		return attributeNames;
	}
	void setTuple(set<Tuple> input) {
		tupleSet = input;
	}
	set<Tuple> getTuple() {
		return tupleSet;
	}

	void select1(int index, string input);

	void select2(int index, int index2);

	void project(map<string, int>& mapp, vector<string>& stringVector);

	void addTuple(vector<string>& inputVector);

	void toString();

	relation join(relation& input);

	void unionize(relation& input);

private:
	string name;
	vector <string> attributeNames;
	set<Tuple> tupleSet;
	//Tuple t;

};

#endif //relation.h
