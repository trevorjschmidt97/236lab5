//
//  dataLog.cpp
//  dataLog
//
//  Created by Trevor Schmidt on 10/2/19.
//  Copyright © 2019 Trevor Schmidt. All rights reserved.
//

#include "dataLog.h"
#include <algorithm>

using namespace std;

void dataLog::checkNPop(string check)
{
    	if (tokenVect.front()->getName() == check)
    	{
        	tokenVect.erase(tokenVect.begin());
        	return;
    	}
    	throw tokenVect.front();
}

/*SCHEMES COLON scheme schemeList
FACTS COLON factList
RULES COLON ruleList
QUERIES COLON query queryList*/
void dataLog::datalogProgram()
{
    	try
    	{
        	checkNPop("SCHEMES");
        	checkNPop("COLON");
        	scheme();
        	schemeList();
        	checkNPop("FACTS");
        	checkNPop("COLON");
        	factList();
        	checkNPop("RULES");
        	checkNPop("COLON");
        	ruleList();
        	checkNPop("QUERIES");
        	checkNPop("COLON");
        	query();
        	queryList();
        	checkNPop("EOF");

        	//cout << "Success!\n";

        	//cout << "Schemes(" << schemeVect.size() << "):\n";
        	for (unsigned int i = 0; i < schemeVect.size(); ++i)
        	{
            		//cout << "  " << schemeVect.at(i)->getPredicate() << "\n";
        	}

        	//cout << "Facts(" << factVect.size() << "):\n";
        	for (unsigned int i = 0; i < factVect.size(); ++i)
        	{
            		//cout << "  " << factVect.at(i)->getPredicate() << ".\n";
        	}

        	//cout << "Rules(" << ruleVect.size() << "):\n";
        	for (unsigned int i = 0; i < ruleVect.size(); ++i)
        	{
            		//cout << "  " << ruleVect.at(i)->toString() << ".\n";
        	}

        	//cout << "Queries(" << querieVect.size() << "):\n";
        	for (unsigned int i = 0; i < querieVect.size(); ++i)
        	{
            		//cout << "  " << querieVect.at(i)->getPredicate() << "?\n";
        	}

        	sort(domainVect.begin(), domainVect.end());
        	domainVect.erase(unique(domainVect.begin(), domainVect.end()), domainVect.end());
        	//cout << "Domain(" << domainVect.size() << "):\n";
        	for (unsigned int i = 0; i < domainVect.size(); ++i)
        	{
            	//cout << domainVect.at(i) << "\n";
        	}
    	}
    	catch (token* n)
    	{
        	//cout << "Failure!\n  " << n->print() << endl;
    	}
}

/*scheme schemeList | lambda*/
void dataLog::schemeList()
{
    	while (tokenVect.front()->getName() != "FACTS")
    	{
        	scheme();
        	schemeList();
    	}
}

/*fact factList | lambda*/
void dataLog::factList()
{
    	while (tokenVect.front()->getName() != "RULES")
    	{
        	fact();
        	factList();
    	}
}

/*rule ruleList | lambda*/
void dataLog::ruleList()
{
    	while (tokenVect.front()->getName() != "QUERIES")
    	{
        	ruleMethod();
        	ruleList();
    	}
}

/*query queryList | lambda*/
void dataLog::queryList()
{
    	while (tokenVect.front()->getName() != "EOF")
    	{
        	query();
        	queryList();
    	}
}

/*ID LEFT_PAREN ID idList RIGHT_PAREN*/
void dataLog::scheme()
{
    	//Creates a empty predicate to add to schemes
    	predicate* stemPredicate = new predicate();

    	//Sets the leading ID for the scheme
    	string ID = tokenVect.front()->getValue();
    	checkNPop("ID");
    	checkNPop("LEFT_PAREN");
    	//Sets first ID inside the parenthesis for the scheme
    	idListStrings.push_back(tokenVect.front()->getValue());
    	checkNPop("ID");
    	idList();
    	checkNPop("RIGHT_PAREN");

    	stemPredicate->setID(ID);
    	stemPredicate->setParameters(idListStrings);
    	schemeVect.push_back(stemPredicate);

    	idListStrings.clear();
}

/*ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD*/
void dataLog::fact()
{
    	//Creates a empty predicate to add to facts
    	predicate* stemPredicate = new predicate();

    	//Sets the leading ID for the rule
    	string ID = tokenVect.front()->getValue();
    	checkNPop("ID");
    	checkNPop("LEFT_PAREN");
    	//Sets the first string inside the parenthesis for the fact
    	factListStrings.push_back(tokenVect.front()->getValue());
    	domainVect.push_back(tokenVect.front()->getValue());
      checkNPop("STRING");
    	stringList();
    	checkNPop("RIGHT_PAREN");
    	checkNPop("PERIOD");

    	stemPredicate->setID(ID);
    	stemPredicate->setParameters(factListStrings);
    	factVect.push_back(stemPredicate);

    	factListStrings.clear();
}

/*headPredicate COLON_DASH predicate predicateList PERIOD*/
void dataLog::ruleMethod()
{
    	rule* stemRule = new rule();

    	rulePredVect.push_back(headPredicate());
    	checkNPop("COLON_DASH");
    	rulePredVect.push_back(predicateMethod());
    	predicateList();
    	checkNPop("PERIOD");

    	stemRule->setPredicates(rulePredVect);
    	ruleVect.push_back(stemRule);

    	rulePredVect.clear();
}

/*predicate Q_MARK*/
void dataLog::query()
{
    	querieVect.push_back(predicateMethod());
    	checkNPop("Q_MARK");
}

/*ID LEFT_PAREN ID idList RIGHT_PAREN*/
predicate* dataLog::headPredicate()
{
    	predicate* stemPredicate = new predicate();

    	string ID = tokenVect.front()->getValue();
    	checkNPop("ID");
    	checkNPop("LEFT_PAREN");
    	idListStrings.push_back(tokenVect.front()->getValue());
    	checkNPop("ID");
    	idList();
    	checkNPop("RIGHT_PAREN");

    	stemPredicate->setID(ID);
    	stemPredicate->setParameters(idListStrings);

    	idListStrings.clear();

    	return stemPredicate;
}

/*ID LEFT_PAREN parameter parameterList RIGHT_PAREN*/
predicate* dataLog::predicateMethod()
{
    	predicate* stemPredicate = new predicate();

    	string ID = tokenVect.front()->getValue();
    	checkNPop("ID");
    	checkNPop("LEFT_PAREN");
    	parameter();
    	parameterList();
    	checkNPop("RIGHT_PAREN");

    	stemPredicate->setID(ID);
    	stemPredicate->setParameters(parameterStrings);

    	parameterStrings.clear();

    	return stemPredicate;
}

/*COMMA predicate predicateList | lambda*/
void dataLog::predicateList()
{
    	while (tokenVect.front()->getName() != "PERIOD")
    	{
        	checkNPop("COMMA");
        	rulePredVect.push_back(predicateMethod());
        	predicateList();
    	}
}

/*COMMA parameter parameterList | lambda*/
void dataLog::parameterList()
{
    	if (forexpression)
    	{
        	parameterStrings.push_back(expressionString);
    	}
    	expressionString = "";
    	forexpression = false;
    	while (tokenVect.front()->getName() != "RIGHT_PAREN")
    	{
        	checkNPop("COMMA");
        	parameter();
        	parameterList();
    	}
}

/*COMMA STRING stringList | lambda*/
void dataLog::stringList()
{
    	while (tokenVect.front()->getName() != "RIGHT_PAREN")
    	{
        	checkNPop("COMMA");
        	factListStrings.push_back(tokenVect.front()->getValue());
        	domainVect.push_back(tokenVect.front()->getValue());
        	checkNPop("STRING");
        	stringList();
    	}
}

/*COMMA ID idList | lambda*/
void dataLog::idList()
{
    	while (tokenVect.front()->getName() != "RIGHT_PAREN")
    	{
        	checkNPop("COMMA");
        	idListStrings.push_back(tokenVect.front()->getValue());
        	checkNPop("ID");
        	idList();
    	}
}

/*STRING | ID | expression*/
void dataLog::parameter()
{
    	if (tokenVect.front()->getName() == "STRING")
    	{
        	if (forexpression == false)
        	{
            		parameterStrings.push_back(tokenVect.front()->getValue());
        	}
        	else
        	{
            		expressionString += tokenVect.front()->getValue();
        	}
        	checkNPop("STRING");
        	return;
    	}
    	else if (tokenVect.front()->getName() == "ID")
    	{
        	if (forexpression == false)
        	{
            		parameterStrings.push_back(tokenVect.front()->getValue());
        	}
        	else
        	{
            		expressionString += tokenVect.front()->getValue();
        	}
        	checkNPop("ID");
        	return;
    	}
    	else
    	{
        	expression();
    	}
}

/*LEFT_PAREN parameter operator parameter RIGHT_PAREN*/
void dataLog::expression()
{
    	forexpression = true;
    	expressionString += "(";
    	checkNPop("LEFT_PAREN");
    	parameter();
    	operate();
    	parameter();
    	expressionString += ")";
    	checkNPop("RIGHT_PAREN");
}

/*ADD | MULTIPLY*/
void dataLog::operate()
{
    	expressionString += tokenVect.front()->getValue();
    	if (tokenVect.front()->getName() == "ADD")
    	{
        	checkNPop("ADD");
    	}
    	else
    	{
        	checkNPop("MULTIPLY");
    	}
}
