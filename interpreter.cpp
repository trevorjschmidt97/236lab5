#include "interpreter.h"

void interpreter::dfsR(node* n) {
	if (!n->isVisited()) {
		n->hasBeenVisited();
		for (auto t : n->getChildren()) {
			dfsR(&reverseMap.at(t));
		}
		n->assignPost(postNum);
		++postNum;
	}
}

void interpreter::dfsP(node* n) {
	if (!n->isVisited()) {
		n->hasBeenVisited();
		for (auto t : n->getChildren()) {
                        dfsP(&dependencyMap.at(t));
                }
                sccIntVect.push_back(n->getNum());
	}
}



relation interpreter::interpretQuerie(predicate* querie) {
	//assumme success is true, this is for the printing of the queries
	success = true;
	relation newRelation = relationMap.at(querie->getID());

        vector<string> querieParamList = querie->getParameterList();
        map<string, int> seenVariables;
        vector<string>stringVect;

	//This is the select part
        for (unsigned int i = 0; i < querieParamList.size(); ++i) {
                string param = querieParamList.at(i);

                if (param.at(0) == '\'') {
                	newRelation.select1(i, param);
                }

                else {
 	               if (seenVariables.find(param) != seenVariables.end()) {
 	                      int j = seenVariables.at(param);
                              newRelation.select2(i, j);
                       }
                       else {
                              seenVariables.insert({param, i});
                              stringVect.push_back(param);
                              //intVect.push_back(i);
                       }
                }
	}

	//At this point, we will know if the success happened
	if (newRelation.getTuple().size() == 0) {
		success = false;
	}

	//rename, super easy, just change the parameterlist
        newRelation.setAttribute(querieParamList);

        //project
        newRelation.project(seenVariables, stringVect);

	//Reset the names to make it easier
        newRelation.setAttribute(stringVect);

        return newRelation;
}

void interpreter::executeInterpreter() {
	//Create all the relations and add their attribute names
	for (unsigned int i = 0; i < schemeVect.size(); ++i) {
            	relation newRelation;
                newRelation.setName(schemeVect.at(i)->getID());
                newRelation.setAttribute(schemeVect.at(i)->getParameterList());

                relationMap.insert({ schemeVect.at(i)->getID(), newRelation});
	}

	//Adds all tuples from facts to each relation
    	for (unsigned int i = 0; i < factVect.size(); ++i) {
           	relationMap[factVect.at(i)->getID()].addTuple(factVect.at(i)->getParameterList());
     	}

	int check;
	int count = 0;

//Dependency graph
	//create a dependency graph = map from ints to nodes

	// do a for loop through all my rules, in each rule, create a node for that rule
	for (unsigned int i = 0; i < ruleVect.size(); ++i) {
		node newNode;
		newNode.setNum(i);
		node newNode2;
		newNode2.setNum(i);
		dependencyMap.insert({i,newNode});
		reverseMap.insert({i,newNode2});
	}
	// add it to the map

	for (unsigned int i = 0; i < ruleVect.size(); ++i) {
		rule* currentRule = ruleVect.at(i);
		for (unsigned int j = 1; j < currentRule->getPredVect().size(); ++j) {
			predicate* currentPred = currentRule->getPredVect().at(j);
			for (unsigned int k = 0; k < ruleVect.size(); ++k) {
				if (currentPred->getID() == ruleVect.at(k)->getPredVect().at(0)->getID()) {
					//current rule depends on rulevect.at(k)
					dependencyMap.at(i).addChild(k);
				}
			}
		}

	}
	//for through each rule
		//for each pred in the rule
			//for each rule
				//if it's the name of the head in any rule
					//add that head's number to our node's child set

	for (unsigned int i = 0; i < ruleVect.size(); ++i) {
		cout << "R" << i << ": ";
		node myNode = dependencyMap.at(i);
		for (auto j : myNode.getChildren()) {
			cout << "R" << j << " ";
		}
		cout << endl;
	}
	//for each thing in map (i could use a for loop with the rule vect size)
		//print out the name, then the whole set of children


//reverse dependency graph
	//create a new map of ints to nodes for the reverse
	//iterate through old map, using j
	for (unsigned int i = 0; i < ruleVect.size(); ++i) {
		node myNode = dependencyMap.at(i);
		for (auto j : myNode.getChildren()) {
			reverseMap.at(j).addChild(i);
		}
	}

	/* CHECK FOR REVERSE DEPENDENCY GRAPH
	for (unsigned int i = 0; i < ruleVect.size(); ++i) {
                cout << "R" << i << ": ";
                node myNode = reverseMap.at(i);
                for (auto j : myNode.getChildren()) {
                        cout << "R" << j << " ";
                }
                cout << endl;
        }*/

		//if i have a child, then go to that node in reverse graph and rule j as child




//dfs forrest of reverse dependency graph
	//jsut go through and assign post order numbers

	for (unsigned int i = 0; i < ruleVect.size(); ++i) {
		//call dfsR search on all nodes in reverseMap
		dfsR(&reverseMap.at(i));
	}
	cout << "done";
//finding scc
	//starting at hightest post order number fround from dfs forrest,
	//go through recursively in that depencdey graph to grab a scc,
/*
	vector<int> findingScc(ruleVect.size());
	for (unsigned int i = 0; i < ruleVect.size(); ++i) {
		findingScc.at(ruleVect.size() - dependencyMap.at(i).getPost()) = i;
	}

	for (unsigned int i = 0; i < ruleVect.size(); ++i) {
		dfsP(dependencyMap.at(findingScc.at(i)));
		if (sccIntVect.size() != 0) {
			sccVect.push_back(sccIntVect);
			sccIntVect.clear();
		}
	}
*/









//run the do while for each scc data structure


	cout << "Rule Evaluation\n";
	//This is the meat of project 4
	//For each rule in the rule vector




	// for each scc, do while unless its a single noded scc that does not depend on itself
		//then run just once and be done

	do {
		//reset the check
		check = 0;
		for (unsigned int i = 0; i < ruleVect.size(); ++i) {
			//First print out the rule
			cout << ruleVect.at(i)->toString();
			//Now create a new relation starting in the actual part of that rule
			relation newRelation = interpretQuerie(ruleVect.at(i)->getPredVect().at(1));
			//This will join all the meat of that rule together
			for (unsigned int j = 2; j < ruleVect.at(i)->getPredVect().size(); ++j) {
				newRelation = newRelation.join(interpretQuerie(ruleVect.at(i)->getPredVect().at(j)));
			}


			map<string, int> seenVariables;

			vector<string> simpleName = ruleVect.at(i)->getPredVect().at(0)->getParameterList();
			for (unsigned int j = 0; j < simpleName.size(); ++j) {
				for (unsigned int k = 0; k < newRelation.getAttribute().size(); ++k) {
					if (simpleName.at(j) == newRelation.getAttribute().at(k)) {
						seenVariables[simpleName.at(j)] = k;
					}
				}
			}
			newRelation.project(seenVariables, simpleName);
			newRelation.setAttribute(simpleName);

			//creat a funciton to compare the set of tuples of new relation and the original,
			//if there is a difference, change my check, and print out those different tuples

			relation poop = relationMap.at(ruleVect.at(i)->getPredVect().at(0)->getID());
			//if (newRelation.getTuple().size() != poop.getTuple().size()) {
				relationMap.at(ruleVect.at(i)->getPredVect().at(0)->getID()) = relationMap.at(ruleVect.at(i)->getPredVect().at(0)->getID()).unionize(newRelation);
			//}
			if (poop.getTuple() != relationMap.at(ruleVect.at(i)->getPredVect().at(0)->getID()).getTuple() ) {
				++check;
			}
		}
		++count;
	} while (check != 0);



	cout << endl;
	cout << "Schemes populated after " << count <<  " passes through the Rules.\n";
	cout << endl;



	cout << "Query Evaluation\n";
	//This is the meat of project 3
     	for (unsigned int i = 0; i < querieVect.size(); ++i) {
              	// Prints out the queriey
              	cout << querieVect.at(i)->getID() << "(";
               	cout << querieVect.at(i)->getParameterList().at(0);
               	for (unsigned int j = 1; j < querieVect.at(i)->getParameterList().size(); ++j) {
                	cout << "," << querieVect.at(i)->getParameterList().at(j);
             	}
     	   	cout << ")?";

                //Runs the interpreter, then prints out the quereie
                if (interpretQuerie(querieVect.at(i)).getTuple().size() != 0) {
                        cout << " Yes(" << interpretQuerie(querieVect.at(i)).getTuple().size() << ")\n";
                }
                else {
			if (success) {
				cout << " Yes(1)\n";
			}
			else {
				cout << " No\n";
			}
		}

		//print out the new relation
		interpretQuerie(querieVect.at(i)).toString();
	}
}
