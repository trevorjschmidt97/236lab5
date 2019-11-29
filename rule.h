//
//  rule.h
//  dataLog
//
//  Created by Trevor Schmidt on 10/2/19.
//  Copyright © 2019 Trevor Schmidt. All rights reserved.
//

#ifndef rule_h
#define rule_h

#include <stdio.h>
#include <vector>
#include "predicate.h"
#include <string>

class rule {
public:
    	rule () {}

    	string toString() {
        	string os;
        	os+= ruleVector.at(0)->getPredicate() + " :- " + ruleVector.at(1)->getPredicate();

        	for (unsigned int i = 2; i < ruleVector.size(); ++i) {
            		os += "," + ruleVector.at(i)->getPredicate();
        	}
		os += ".\n";
        	return os;
    	}

    	void setPredicates (vector <predicate*> input) {
        	ruleVector = input;
    	}

	vector <predicate*> getPredVect() {
		return ruleVector;
	}

private:
    	vector <predicate*> ruleVector;

};

#endif /* rule_h */
