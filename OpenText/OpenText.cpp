// OpenText.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "CmdGenerator.h"
#include "OTObject.h"

int _tmain(int argc, _TCHAR* argv[])
{
	///. start the app
	std::cout << "Changeing Settings on Particular Objcet." << std::endl;
	std::string strInput;
	CCmdGenerator::help(strInput);
	std::cout << strInput;

	///. Keep doing commit until Exit command
	bool bContinue = true;
	do
	{
		std::string strOutput;
		///. get command line
		std::cout << "Please enter a command (EXIT to terminate):" << std::endl;
		std::getline(std::cin, strInput);

		///. find command name, like "SET propertyname=newvalue"
		const std::string strSpace(" ");
		std::size_t nPos = strInput.find(strSpace);
		if (nPos != std::string::npos)
		{
			std::string strCmd = strInput.substr(0, nPos);
			std::string strParam = strInput.substr(nPos+1, strInput.size()-nPos-1);
			///. have the command commited
			CCmdGenerator::commit(strCmd, strParam, strOutput);
		}
		else if ("EXIT" == strInput || "exit" == strInput)
		{
			///. terminate the app
			strOutput = "\nSee you again.";
			bContinue = false;
		}
		else
		{
			///. wrong format
			strOutput = "Could not find the command.";
		}
		///. show the response
		std::cout << strOutput << std::endl;
	}
	while (bContinue);

	///. release singleton object
	COTObjects::release();

	///. Exit
	system("pause");
	return 0;
}
