#include "StdAfx.h"
#include "CmdGenerator.h"
#include "OTCmd.h"
#include <sstream>
#include <algorithm>

namespace CCmdGenerator_Pri
{
	struct CCmdInfo
	{
		char* pstrCmd;
		char* pstrDesc;
	};
	const CCmdInfo pstrCmds[] = {
		{"SET", "SET propertyname=newvalue"},
		{"GET", "GET propertyname|*"},
	};
	enum CCmd_
	{
		CCmd_Set = 0,
		CCmd_Get,
		///.
		CCmd_Total,
	};

	int getCmdId(const std::string& strCmd)
	{
		int nRet = -1;
		std::string strTemp(strCmd);
		std::transform(strTemp.begin(), strTemp.end(), strTemp.begin(), ::toupper);
		for (int i=0; i<CCmd_Total; ++i)
		{
			if (pstrCmds[i].pstrCmd == strTemp)
			{
				nRet = i;
				break;
			}
		}
		return nRet;
	}

}///. end of CCmdGenerator_Pri


int CCmdGenerator::help(std::string& strCmds)
{
	int nRet = 0;
	std::stringstream ssTemp;
	for (int i=0; i<CCmdGenerator_Pri::CCmd_Total; ++i)
	{
		ssTemp << CCmdGenerator_Pri::pstrCmds[i].pstrDesc << std::endl;
	}
	strCmds = ssTemp.str();
	return nRet;
}

int CCmdGenerator::commit(
		const std::string& strCmd, const std::string& strParam, 
		std::string& strResponse)
{
	int nError = 0;
	int nCmdId = CCmdGenerator_Pri::getCmdId(strCmd);
	switch (nCmdId)
	{
	case CCmdGenerator_Pri::CCmd_Set:
		{
			CCmdSet cmd(strParam);
			nError = cmd.commit(strResponse);
		}
		break;
	case CCmdGenerator_Pri::CCmd_Get:
		{
			CCmdGet cmd(strParam);
			nError = cmd.commit(strResponse);
		}
		break;
	default:
		///. unknown command
		strResponse = "The command has wrong name.";
		nError = -1;
		break;
	}
	return nError;
}
