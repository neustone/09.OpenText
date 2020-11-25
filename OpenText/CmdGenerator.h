#pragma once
#include <string>

class CCmdGenerator
{
public:

	///. get list of commands
	static int help(std::string& strCmds);

	///. perform the command
	static int commit(
		const std::string& strCmd, const std::string& strParam, 
		std::string& strResponse);
};

