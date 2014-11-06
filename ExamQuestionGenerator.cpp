// ExamQuestionGenerator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <math.h>


int _tmain(int argc, _TCHAR* argv[])
{
	std::string templateFileName = "template1.txt";
	std::string variableNamesFileName = "var_names01.txt";
	std::string outputFileName = "template1_output.txt";

	// Read in template documents
	std::ifstream templateFile("Input Files/" +  templateFileName); // template file stream
	std::string templateRawText; // raw text read in from the template file.

	if (templateFile.is_open())
	{
		std::string line;
		while (std::getline(templateFile,line) )
		{
			templateRawText.append(line + "\n");
		}
		templateFile.close();
	}
	
	// debug print to see if we are reading the template
	std::cout << templateRawText;

	// Read in Variable documents, store in the dictionary
	std::map<std::string, std::vector<std::string>> variableStringCatagories;

	std::ifstream variableNamesFile("Input Files/" +  variableNamesFileName); // template file stream
	std::vector<std::string> names01; // vector of each name under this catagory

	if (variableNamesFile.is_open())
	{
		std::string line;
		while (std::getline(variableNamesFile,line) )
		{
			names01.push_back(line);
		}
		variableStringCatagories.insert(std::make_pair("names01", names01));
		variableNamesFile.close();
	}

	// Search for variables in the templates
	std::string startToken = "<$";
	std::string endToken = "$>";
	std::vector<size_t> positions; // holds all the positions that sub occurs within str

	size_t pos = templateRawText.find(startToken, 0);
	while(pos != std::string::npos)
	{
		positions.push_back(pos);
		// Resolve all variables
		int nameIndex = rand() % variableStringCatagories["names01"].size();
		templateRawText.replace(pos, templateRawText.find(endToken, pos) - pos + endToken.length(), variableStringCatagories["names01"][nameIndex]);
		pos = templateRawText.find(startToken,pos+1);
	}

	// Write out the results file
	std::ofstream outputFile ("Output Files/" + outputFileName);
	if (outputFile.is_open())
	{
		outputFile << templateRawText;
		outputFile.close();
	}
	else std::cout << "Unable to open output file: " << outputFile << "\n";

	system("PAUSE");
	return 0;
}

