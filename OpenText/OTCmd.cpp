#include "StdAfx.h"
#include "OTCmd.h"
#include "OTObject.h"
#include <string>

CCmd::CCmd(const std::string& strParam)
{
}
CCmd::~CCmd()
{
}


/////////////////////////////////////////

CCmdSet::CCmdSet(const std::string& strParam)
	: CCmd(strParam)
	, m_strName()
	, m_strValue()
{
	/// SET propertyname=newvalue
	const std::string strAssign("=");
	std::size_t nPos = strParam.find(strAssign);
	if (nPos != std::string::npos)
	{
		m_strName = strParam.substr(0, nPos);
		m_strValue = strParam.substr(nPos+1, strParam.size()-nPos-1);
	}
}

CCmdSet::~CCmdSet()
{
}

int CCmdSet::commit(std::string& strRet)
{
	int nError = 0;
	///. should accept an arbitrary object in future, like SET id=1 ..., 
	COTObjects* pOTObjects = COTObjects::getInstance();
	int nId = 1;
	COTObject* pOTObject = pOTObjects->getObject(nId);
	if (pOTObject)
	{
		/// SET propertyname=newvalue will change the target object’s member named “propertyname” 
		/// to have a value equal to “newvalue”.
		pOTObject->setValue(m_strName, m_strValue, strRet);
	}
	else
	{
		///. there is no such object
		strRet = "We can not find the object\n";
		nError = -1;
	}
	return nError;
}


/////////////////////////////////////////

CCmdGet::CCmdGet(const std::string& strParam)
	: CCmd(strParam)
	, m_strName(strParam)
{
	///. GET propertyname
	///. GET *
}

CCmdGet::~CCmdGet()
{
}

int CCmdGet::commit(std::string& strRet)
{
	int nError = 0;
	///. should accept an arbitrary object in future, like SET id=1 ..., 
	COTObjects* pOTObjects = COTObjects::getInstance();
	int nId = 1;
	COTObject* pOTObject = pOTObjects->getObject(nId);
	if (pOTObject)
	{
		pOTObject->getValue(m_strName, strRet);
	}
	else
	{
		///. there is no such object
		strRet = "We can not find the object\n";
		nError = -1;
	}
	return nError;
}
