#include "StdAfx.h"
#include "CmdGenerator.h"
#include "OTCmd.h"
#include <sstream>


int CCmdGenerator::help(std::string& strCmds)
{
	int nRet = 0;
	std::stringstream ssTemp;
	ssTemp << "SET propertyname=newvalue" << std::endl
		<< "GET propertyname" << std::endl
		<< "GET *" << std::endl;
	strCmds = ssTemp.str();
	return nRet;
}

int CCmdGenerator::commit(
		const std::string& strCmd, const std::string& strParam, 
		std::string& strResponse)
{
	int nError = 0;
	if ("GET" == strCmd || "get" == strCmd)
	{
		CCmdGet cmd(strParam);
		nError = cmd.commit(strResponse);
	}
	else if ("SET" == strCmd || "set" == strCmd)
	{
		CCmdSet cmd(strParam);
		nError = cmd.commit(strResponse);
	}
	else
	{
		///. unknown command
		strResponse = "The command has wrong name.";
		nError = -1;
	}
	return nError;
}
