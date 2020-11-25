#pragma once
#include <vector>

/********************************************
The system should be extensible for future commands,
and should accept an arbitrary object, 
such that another developer could insert another object into the system
and rely on the command console to get and set the properties correctly.
********************************************/

/////////////////////////////////////////////////
///. 
///. the container of objects
///.
class COTObject;
class COTObjects
{
public:
	///. get singleton object.
	static COTObjects* getInstance();
	///. release the object at the end.
	static void release();

	///. The system should accept an arbitrary object.
	///. get the object by using its Id.
	COTObject* getObject(int nId);
	///. add an object into this container, and it will be released by the container.
	int addObject(COTObject* pObject);

private:

	///. singleton object.
	static COTObjects* m_pInstance;

	///. there is list of arbitrary objects to manipulate.
	std::vector<COTObject*> m_vObjects;

	////////////////////////////

	COTObjects(void);
	~COTObjects(void);
};

/////////////////////////////////////////////////
///. 
///. base class of Object
///. another developer could insert another object into the system
///. new object must be derived of class COTObject
///.
///. we may consider to add a mutex here for thread-safe in future
///.
class COTObject
{
public:
	///. 
	COTObject(int nId);
	virtual ~COTObject();

	///. get the identity
	int getId() const;
	///. have the property valued, and will return the response
	virtual int setValue(
		const std::string& strName, const std::string& strValue, std::string& strResp) = 0;
	///. enter a name, and will return the response
	virtual int getValue(
		const std::string& strName, std::string& strResp) = 0;

protected:
	///. object identity
	int m_nId;
};
