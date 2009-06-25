/*
 *  optionparser.cpp
 *  Mothur
 *
 *  Created by Sarah Westcott on 6/8/09.
 *  Copyright 2009 Schloss Lab UMASS Amherst. All rights reserved.
 *
 */

#include "optionparser.h"

/***********************************************************************/

OptionParser::OptionParser(string option) {
	try {
		
		if (option != "") {
			
			string key, value;		
			//reads in parameters and values
			while((option.find_first_of(',') != -1)) {  //while there are parameters
				splitAtComma(value, option);
				splitAtEquals(key, value);
				parameters[key] = value;
			}
			
			//in case there is no comma and to get last parameter after comma
			splitAtEquals(key, option);
			parameters[key] = option;
		}
	}
	catch(exception& e) {
		errorOut(e, "OptionParser", "parse");
		exit(1);
	}
}

/***********************************************************************/

map<string, string> OptionParser::getParameters() {	return parameters;	}

/***********************************************************************/
