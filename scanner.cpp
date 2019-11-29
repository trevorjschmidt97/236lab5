//
//  scanner.cpp
//  dataLog
//
//  Created by Trevor Schmidt on 10/2/19.
//  Copyright © 2019 Trevor Schmidt. All rights reserved.
//

#include "scanner.h"

void scanner::executeLexer() {
    	unsigned int lineCount = 1;

    	for (unsigned int i = 0; i < file.size(); ++i) {
        	//cout << "My line count is " << lineCount << endl;
        	if (file.at(i) == '\n') {
            		++lineCount;
        	}

        	else if (file.at(i) == 'Q' && file.at(i + 1) == 'u' && file.at(i + 2) == 'e' &&
                 	 file.at(i + 3) == 'r' && file.at(i + 4) == 'i' && file.at(i + 5) == 'e' &&
                 	 file.at(i + 6) == 's' && file.at(i + 7) == ':') {
            		createToken("QUERIES", "Queries", lineCount);
            		i = i + 6;
        	}

        	else if (file.at(i) == 'S' && file.at(i + 1) == 'c' && file.at(i + 2) == 'h' &&
                 	 file.at(i + 3) == 'e' && file.at(i + 4) == 'm' && file.at(i + 5) == 'e' &&
                 	 file.at(i + 6) == 's' && file.at(i + 7) == ':') {
            		createToken("SCHEMES", "Schemes", lineCount);
            		i = i + 6;
        	}

        	else if (file.at(i) == 'F' && file.at(i + 1) == 'a' && file.at(i + 2) == 'c' &&
                 	 file.at(i + 3) == 't' && file.at(i + 4) == 's' && isspace(file.at(i + 5)
                 	 && file.at(i + 6) == ':')) {
            		createToken("FACTS", "Facts", lineCount);
            		i = i + 4;
        	}

        	else if (file.at(i) == 'R' && file.at(i + 1) == 'u' && file.at(i + 2) == 'l' &&
                 	 file.at(i + 3) == 'e' && file.at(i + 4) == 's' && isspace(file.at(i + 5)
                 	 && file.at(i + 6) == ':')) {
            		createToken("RULES", "Rules", lineCount);
            		i = i + 4;
        	}

        	else if (file.at(i) == ':' && file.at(i + 1) != '-') {
            		createToken("COLON", ":", lineCount);
        	}

        	else if (file.at(i) == ':' && file.at(i + 1) == '-') {
           		createToken("COLON_DASH", ":-", lineCount);
            		++i;
        	}

        	else if (file.at(i) == '(') {
            		createToken("LEFT_PAREN", "(", lineCount);
        	}

        	else if (file.at(i) == ')') {
            		createToken("RIGHT_PAREN", ")", lineCount);
        	}

        	else if (file.at(i) == '?') {
            		createToken("Q_MARK", "?", lineCount);
        	}

        	else if (file.at(i) == ',') {
            		createToken("COMMA", ",", lineCount);
        	}

        	else if (file.at(i) == '.') {
            		createToken("PERIOD", ".", lineCount);
        	}

        	else if (file.at(i) == '*') {
            		createToken("MULTIPLY", "*", lineCount);
        	}

        	else if (file.at(i) == '+') {
            		createToken("ADD", "+", lineCount);
        	}

        	// IDENTIFIERS
        	else if (isalpha(file.at(i))) {
            		string id;
            		id = id + file.at(i);
            		while(isalpha(file.at(i+1)) || isdigit(file.at(i+1))) {
                		++i;
                		id = id + file.at(i);
            		}
            		if (id == "Rules") {
                		createToken("RULES", id, lineCount);
            		}
            		else if (id == "Queries") {
                		createToken("QUERIES", id, lineCount);
            		}
            		else if (id == "Schemes") {
                		createToken("SCHEMES", id, lineCount);
            		}
            		else if (id == "Facts") {
                		createToken("FACTS", id, lineCount);
            		}
            		else {
                		createToken("ID", id, lineCount);
            		}
        	}

        	//STRING
        	else if (file.at(i) == '\'') {
            		int thisLine = lineCount;
            		++i;
            		string str = "\'";

            		if (file.at(i) == '\'' && file.at(i + 1) == '\'') {
                		str += "\'\'";
                		i += 2;
            		}
            		if (file.at(i) == '\'' && file.at(i + 1) == '\'') {
                		str += "\'\'";
                		i += 2;
            		}
            		if (file.at(i) == '\'' && file.at(i + 1) == '\'') {
                		str += "\'\'";
                		i += 2;
            		}
            		if (file.at(i) == '\'' && file.at(i + 1) == '\'') {
                		str += "\'\'";
                		i += 2;
            		}
            		if (file.at(i) == '\'' && file.at(i + 1) == '\'') {
                		str += "\'\'";
                		i += 2;
            		}

            		while (file.at(i) != '\'') {
                		if (i == file.size() - 1) {
                    			if (file.at(i) == '\n') {
                        			//++lineCount;
                        			str += "\n";
                    			}
                    			++i;

                    			lineCount += 1;
                    			createToken("UNDEFINED", str, thisLine);
                    			break;
                		}

                		if (file.at(i) == '\n') {
                    			++lineCount;
                		}

                		str += file.at(i);
                		++i;

                		while (file.at(i) == '\'') {
                    			if (i != file.size() - 1) {
                        			if (file.at(i + 1) == '\'') {
                            				str += "\'\'";
                            				i += 2;
                        			}
                        			else {
                            				break;
                        			}
                    			}
                    			else {
                        			break;
                    			}
                		}
            		}

            		str += "\'";

            		if (i != file.size() - 1 && i != file.size()) {
                		createToken("STRING", str, thisLine);
            		}
        	}

        	//Multi line comment
        	else if ((file.at(i) == '#') && (file.at(i + 1) == '|')) {
            		i = i + 2;
            		string comment = "#|";
            		int thisLine = lineCount;
            		while ((file.at(i) != '|') || (file.at(i + 1) != '#')) {
                		if (file.at(i) == '\n') {
                    			lineCount++;
                		}
                		comment = comment + file.at(i);
                		++i;

                		if (i == file.size() - 1) {
                    			comment += "\n";
                    			lineCount++;
                    			createToken("UNDEFINED", comment, thisLine);
                    			break;
                		}
            		}
            		++i;
            		comment = comment + "|#";

            		if (i != file.size()) {
                		//createToken("COMMENT", comment, thisLine);
            		}
        	}

        	//Comment
        	else if (file.at(i) == '#') {
            		string comment;
            		comment = comment + file.at(i);
            		while((file.at(i + 1) != '\n')) {
                		++i;
                		comment = comment + file.at(i);
            		}
            		//createToken("COMMENT", comment, lineCount);
        	}

        	else if (!isspace(file.at(i)) && (file.at(i) != '\n')) {
            		string undefined;
            		undefined += file.at(i);
            		createToken("UNDEFINED", undefined, lineCount);
        	}

    	} // End for loop of entire file
    	createToken("EOF", "", lineCount);
}
