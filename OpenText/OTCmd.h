#pragma once
#include <string>

///////////////////////////
//
// base class
//
class CCmd
{
public:
	CCmd(const std::string& strParam);
	virtual ~CCmd();
	///.
	virtual int commit(std::string& strRet) = 0;
};

///////////////////////////
///.
///. command SET
///. SET propertyname=newvalue will change the target object’s member named “propertyname”
///. to have a value equal to “newvalue”.  
///. If the input value is incompatible (i.e. an int being set to a string), 
///. print out an appropriate error message.
///.
class CCmdSet : public CCmd
{
	///. property name, property value
	std::string m_strName, m_strValue;

public:
	CCmdSet(const std::string& strParam);
	virtual ~CCmdSet();
	///.
	virtual int commit(std::string& strRet);
};

///////////////////////////
///.
///.command GET
///. GET propertyname will print out the current value of 
///. the target object’s member named “propertyname”.
///. GET * will print out a list of all target object members 
///. and their current values.
///.
class CCmdGet : public CCmd
{
	///. property name,
	std::string m_strName;

public:
	CCmdGet(const std::string& strParam);
	virtual ~CCmdGet();
	///.
	virtual int commit(std::string& strRet);
};
