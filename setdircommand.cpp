/*
 *  setoutdircommand.cpp
 *  Mothur
 *
 *  Created by westcott on 1/21/10.
 *  Copyright 2010 Schloss Lab. All rights reserved.
 *
 */

#include "setdircommand.h"

//**********************************************************************************************************************

SetDirectoryCommand::SetDirectoryCommand(string option)  {
	try {
		abort = false;
		
		//allow user to run help
		if(option == "help") { help(); abort = true; }
		
		else {
			//valid paramters for this command
			string Array[] =  {"output","input","outputdir","inputdir"};
			vector<string> myArray (Array, Array+(sizeof(Array)/sizeof(string)));
			
			OptionParser parser(option);
			map<string, string> parameters = parser.getParameters();
			
			ValidParameters validParameter;
			//check to make sure all parameters are valid for command
			for (map<string,string>::iterator it = parameters.begin(); it != parameters.end(); it++) { 
				if (validParameter.isValidParameter(it->first, myArray, it->second) != true) {  abort = true;  }
			}
		
			output = validParameter.validFile(parameters, "output", false);			
			if (output == "not found") {  output = "";  } 
			
			input = validParameter.validFile(parameters, "input", false);			
			if (input == "not found") {  input = "";  }
				
			if ((input == "") && (output == "")) {	
				m->mothurOut("You must provide either an input or output for the set.outdir command."); m->mothurOutEndLine(); abort = true;
			}
		}
	}
	catch(exception& e) {
		m->errorOut(e, "SetDirectoryCommand", "SetDirectoryCommand");
		exit(1);
	}
}
//**********************************************************************************************************************

void SetDirectoryCommand::help(){
	try {
		m->mothurOut("The set.dir command can be used to direct the output files generated by mothur to a specific place, the directory must exist.\n");
		m->mothurOut("The set.dir command can also be used to specify the directory where your input files are located, the directory must exist.\n");
		m->mothurOut("The set.dir command parameter is output and is required.\n");
		m->mothurOut("To return the output to the same directory as the input files you may enter: output=clear.\n");
		m->mothurOut("To return the input to the same directory as the mothur.exe you may enter: input=clear.\n");
		m->mothurOut("The set.dir command should be in the following format: set.dir(output=yourOutputDirectory, input=yourInputDirectory).\n");
		m->mothurOut("Example set.outdir(output=/Users/lab/desktop/outputs, input=/Users/lab/desktop/inputs).\n");
		m->mothurOut("Note: No spaces between parameter labels (i.e. output), '=' and parameters (i.e.yourOutputDirectory).\n\n");
	}
	catch(exception& e) {
		m->errorOut(e, "SetDirectoryCommand", "help");
		exit(1);
	}
}
//**********************************************************************************************************************

SetDirectoryCommand::~SetDirectoryCommand(){}

//**********************************************************************************************************************

int SetDirectoryCommand::execute(){
	try {
		
		if (abort == true) { return 0; }
		
		commandFactory = CommandFactory::getInstance();
		
		//redirect output
		if ((output == "clear") || (output == "")) {  output = "";  commandFactory->setOutputDirectory(output);  }
		else {
			//add / to name if needed
			string lastChar = output.substr(output.length()-1);
			#if defined (__APPLE__) || (__MACH__) || (linux) || (__linux)
				if (lastChar != "/") { output += "/"; }
			#else
				if (lastChar != "\\") { output += "\\"; }	
			#endif
			
			//test to make sure directory exists
			output = getFullPathName(output);
			string outTemp = output + "temp";
			ofstream out;
			out.open(outTemp.c_str(), ios::trunc);
			if(!out) {
				m->mothurOut(output + " directory does not exist or is not writable."); m->mothurOutEndLine(); 
			}else{
				out.close();
				remove(outTemp.c_str());
				m->mothurOut("Changing output directory to " + output); m->mothurOutEndLine();  
				commandFactory->setOutputDirectory(output);
			}
		}
		
		//redirect input
		if ((input == "clear") || (input == "")) {  input = "";  commandFactory->setInputDirectory(input);  }
		else {
			//add / to name if needed
			string lastChar = input.substr(input.length()-1);
			#if defined (__APPLE__) || (__MACH__) || (linux) || (__linux)
				if (lastChar != "/") { input += "/"; }
			#else
				if (lastChar != "\\") { input += "\\"; }	
			#endif
			
			//test to make sure directory exists
			input = getFullPathName(input);
			string inTemp = input + "temp";
			ofstream in;
			in.open(inTemp.c_str(), ios::trunc);
			if(!in) {
				m->mothurOut(input + " directory does not exist or is not writable."); m->mothurOutEndLine(); 
			}else{
				in.close();
				remove(inTemp.c_str());
				m->mothurOut("Changing input directory to " + input); m->mothurOutEndLine();  
				commandFactory->setInputDirectory(input); 
			}
		}

		return 0;
	}
	catch(exception& e) {
		m->errorOut(e, "SetDirectoryCommand", "execute");
		exit(1);
	}
}
//**********************************************************************************************************************/
