#include "StdAfx.h"
#include "OTObject.h"
#include <string>
#include <sstream>
#include <map>

///////////////////////////////////////////////////

COTObject::COTObject(int nId)
	: m_nId(nId)
{
}

COTObject::~COTObject(void)
{
}

int COTObject::getId() const
{
	return m_nId;
}

///////////////////////////////////////////////////

class COTObjectSample: public COTObject
{
	std::map<std::string, int> m_mapNumbers;
	std::map<std::string, std::string> m_mapStrings;

public:
	COTObjectSample(int nId)
		: COTObject(nId)
		, m_mapNumbers()
		, m_mapStrings()
	{
		m_mapNumbers["P1"] = 1;
		m_mapNumbers["P2"] = 2;
//		m_mapNumbers["P3"] = 3;

		m_mapStrings["PA"] = "A";
//		m_mapStrings["PB"] = "B";
//		m_mapStrings["PC"] = "C";
	}
	~COTObjectSample()
	{
	}
	
	int setValue(
		const std::string& strName, const std::string& strValue, std::string& strResp)
	{
		int nRet = 0;
		strResp = strName;
		if (m_mapNumbers.find(strName) != m_mapNumbers.end())
		{
			///. If the input value is incompatible (i.e. an int being set to a string), 
			///. print out an appropriate error message.
			try
			{
				m_mapNumbers[strName] = std::stoi(strValue);
				///. integer member
				std::stringstream ssTemp;
				ssTemp << " = " << m_mapNumbers[strName] << std::endl;
				strResp.append(ssTemp.str());
			}
			catch (...)
			{
				// error management
				strResp.append(" is an integer member\n");
				nRet = -1;
			}  
		}
		else if (m_mapStrings.find(strName) != m_mapStrings.end())
		{
			m_mapStrings[strName] = strValue;
			///. string member
			strResp.append(" = ");
			strResp.append(m_mapStrings[strName]);
			strResp.append("\n");
		}
		else
		{
			///. there is no such name
			strResp.append(" is not an object member\n");
			nRet = -1;
		}
		return nRet;
	}///. end of int setValue(...)
	
	int getValue(
		const std::string& strName, std::string& strResp)
	{
		int nRet = 0;
		if ("*" == strName)
		{
			///. GET * will print out a list of all target object members and their current values.
			std::stringstream ssTemp;
			///. integer members
			auto it = m_mapNumbers.begin();
			auto itEnd = m_mapNumbers.end();
			while (it != itEnd)
			{
				std::stringstream ssTemp;
				ssTemp << it->first << " = " << it->second << std::endl;
				strResp.append(ssTemp.str());
				///.
				++ it;
			}
			///. string members
			auto it2 = m_mapStrings.begin();
			auto itEnd2 = m_mapStrings.end();
			while (it2 != itEnd2)
			{
				std::stringstream ssTemp;
				ssTemp << it2->first << " = " << it2->second << std::endl;
				strResp.append(ssTemp.str());
				///.
				++ it2;
			}
		}
		else
		{
			///. GET propertyname will print out the current value of the target object’s member named “propertyname”
			strResp = strName;
			if (m_mapNumbers.find(strName) != m_mapNumbers.end())
			{
				///. integer member
				std::stringstream ssTemp;
				ssTemp << " = " << m_mapNumbers[strName] << std::endl;
				strResp.append(ssTemp.str());
			}
			else if (m_mapStrings.find(strName) != m_mapStrings.end())
			{
				///. string member
				strResp.append(" = ");
				strResp.append(m_mapStrings[strName]);
				strResp.append("\n");
			}
			else
			{
				///. there is no such name
				strResp.append(" is not object member\n");
				nRet = -1;
			}
		}///. end of if ("*" == strName)
		return nRet;
	}///. end of int getValue(...)

};///. end of class COTObjectSample ...

///////////////////////////////////////////////////
//
//	COTObjects
//
COTObjects* COTObjects::m_pInstance = nullptr;

COTObjects::COTObjects(void)
	: m_vObjects()
{
	///. add a Object sample for test
	COTObject* pObject = new COTObjectSample(1);
	COTObjects::addObject(pObject);
}


COTObjects::~COTObjects(void)
{
	auto it  = m_vObjects.begin();
	while (it != m_vObjects.end())
	{
		delete *it;
		++ it;
	}
	m_vObjects.clear();
}
	
COTObjects* COTObjects::getInstance()
{
	if (nullptr == m_pInstance)
	{
		m_pInstance = new COTObjects;
	}
	return m_pInstance;
}
	
void COTObjects::release()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

COTObject* COTObjects::getObject(int nId)
{
	COTObject* pObject = nullptr;
	auto it  = m_vObjects.begin();
	while (it != m_vObjects.end())
	{
		if (nId == (*it)->getId())
		{
			pObject = *it;
			break;
		}
		++ it;
	}
	return pObject;
}

int COTObjects::addObject(COTObject* pObject)
{
	int nRet = -1;
	if (pObject)
	{
		m_vObjects.push_back(pObject);
		nRet = m_vObjects.size();
	}
	return nRet;
}