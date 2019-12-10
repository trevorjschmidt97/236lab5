#include "relation.h"

relation relation::join(relation& input) {

	set<pair<int, int>> columnMatch;
	vector<int> notMatch;

	relation newRelation;
	newRelation.setName("Joined Predicate");
	vector<string> newAttributeStringVect = attributeNames;
	//cout << "before for loop of join\n";
	for (unsigned int i = 0; i < input.getAttribute().size(); ++i) {
		bool isIn = false;
		for (unsigned int j = 0; j < attributeNames.size(); ++j) {
			//bool isIn = false;
			if (input.getAttribute().at(i) == attributeNames.at(j)) {
				isIn = true;
				columnMatch.insert(make_pair(j,i));
				break;
			}
		}
		if (!isIn) {
			newAttributeStringVect.push_back(input.getAttribute().at(i));
			notMatch.push_back(i);
		}
	}
	//cout << "after for loop of join\n";
	newRelation.setAttribute(newAttributeStringVect);
	//cout << "before tuple loop of join\n";
	for (auto t : tupleSet) {
		for (auto r : input.getTuple()) {
			bool theyMatch = true;
			for (auto c : columnMatch) {
				if (t.at(c.first) != r.at(c.second)) {
					theyMatch = false;
					break;
				}
			}
			if (theyMatch) {
				Tuple newTuple = t;
				for (unsigned int i = 0; i < notMatch.size(); ++i) {
					newTuple.push_back(r.at(notMatch.at(i)));
				}
				newRelation.addTuple(newTuple);
			}
		}
	}
	//cout << "after tuple loop\n";
	return newRelation;
}

void relation::unionize(relation& input) {
	for (auto t : input.getTuple()) {
		if (tupleSet.insert(t).second){
			cout << "  ";
                        cout << attributeNames.at(0) << "=" << t.at(0);
                        for (unsigned int j = 1; j < input.getAttribute().size(); ++j) {
                                cout << ", " << attributeNames.at(j) << "=" << t.at(j);
                        }
                        cout << endl;
		}
	}
	/* // Old union function, later optimized above
	bool added;
	relation newRelation;
	newRelation.setName(name);
	newRelation.setAttribute(attributeNames);
	for (auto t : tupleSet) {
		newRelation.addTuple(t);
	}
	for (auto t : input.getTuple()) {
		added = true;
		Tuple j;

        	for (unsigned int i = 0; i < t.size(); ++i) {
                	j.push_back(t.at(i));
        	}


		pair<set<Tuple>::iterator,bool> ret = newRelation.getTuple().insert(j);

        	if(ret.second==false) {
			added = false;
		}
		unsigned int size = newRelation.getTuple().size();

		newRelation.addTuple(t);

		if (size == newRelation.getTuple().size()) {
			added = false;
		}
		if (added) {
			cout << "  ";
			cout << newRelation.getAttribute().at(0) << "=" << t.at(0);
			for (unsigned int j = 1; j < newRelation.getAttribute().size(); ++j) {
				cout << ", " << newRelation.getAttribute().at(j) << "=" << t.at(j);
			}
			cout << endl;
		}
	}
	return newRelation;
}*/
}

void relation::select1(int index, string input) {
	set<Tuple> newTupleSet;

        for (auto t : tupleSet) {
        	if (t.at(index) == input) {
                   	newTupleSet.insert(t);
                }
      	}

     	tupleSet = newTupleSet;
}

void relation::select2(int index, int index2) {
     	set<Tuple> newTupleSet;

      	for (auto t : tupleSet) {
           	if (t.at(index) == t.at(index2)) {
                      	newTupleSet.insert(t);
            	}
      	}

	tupleSet = newTupleSet;
}

void relation::project(map<string, int>& mapp, vector<string>& stringVector) {
  	set<Tuple> newTupleSet;

    	for (auto t : tupleSet) {
           	Tuple newTuple;
            	for (unsigned int i = 0; i < stringVector.size(); ++i) {
                  	newTuple.push_back(t.at(mapp.at(stringVector.at(i))));
            	}
            	if (newTuple.size() != 0) {
                	newTupleSet.insert(newTuple);
              	}
   	}
     	tupleSet = newTupleSet;
}

void relation::addTuple(vector<string>& inputVector) {
   	Tuple t;

     	for (unsigned int i = 0; i < inputVector.size(); ++i) {
             	t.push_back(inputVector.at(i));
    	}

     	tupleSet.insert(t);
}

void relation::toString() {
  	if (tupleSet.size() != 0) {
           	for (auto t : tupleSet) {
                   	cout << "  ";
                     	cout << attributeNames.at(0) << "=" << t.at(0);
                     	for (unsigned int j = 1; j < attributeNames.size(); ++j) {
                          	cout << ", " << attributeNames.at(j) << "=" << t.at(j);
                    	}
                      	cout << endl;
             	}
      	}
}
