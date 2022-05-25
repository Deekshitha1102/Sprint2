
/**********************************************************************************************************
 * *
 * * FILENAME : LString.cpp
 * *
 * * DESCRIPTION : Create a string class called LString that enables sharing of internal buffer between 
 * *               different objects, if they are holding the same copy. e.g. if a copy of a LString object 
 * *               is created, the new LString object will point to the same buffer as that of the old 
 * *               LString object 
 * *********************************************************************************************************/

#include "LString.h"

//constructor
/******************************************************************************
 * **
 * ** FUNCTION NAME : LString()
 * **
 * ** DESCRIPTION : This is used to create a constructor
 * **
 * ** RETURNS : void
 * **
 * *****************************************************************************/
LString::LString()
{
	m_pBuffer = new char[1]();
	m_pCount = new int(1);

	objectPool.push_back(this);
}
//Parameterized constructor
/******************************************************************************
 * **
 * ** FUNCTION NAME : LString(const char *pstr)
 * **
 * ** DESCRIPTION : This is used to create parameterized constructor and assign the string.
 * **
 * ** RETURNS : void
 * **
 * *****************************************************************************/
LString::LString(const char* pstr)
{
	auto length = strlen(pstr);

	if (objectPool.size() == 0)
	{
		m_pBuffer = new char[length + 1]();
		strcpy(m_pBuffer, pstr);
		m_Length = length;

		m_pCount = new int(1);
	}
	else
	{
		ValidateAndAllocateString(pstr);
	}

	objectPool.push_back(this);
}
//Destructor
/******************************************************************************
 * **
 * ** FUNCTION NAME : LString
 * **
 * ** DESCRIPTION : This is used to Delete the constructor.
 * **
 * ** RETURNS : void
 * **
 * *****************************************************************************/
LString::~LString()
{
	if(--(*m_pCount) == 0){
		delete[] m_pBuffer ;
		m_pBuffer = NULL;
		delete m_pCount ;
	}
}
//Copy Constructor
/******************************************************************************
 * **
 * ** FUNCTION NAME : LString::LString(const LString &other)
 * **
 * ** DESCRIPTION : This is used to create a copy constructor for the string and assign the string.
 * **
 * ** RETURNS : void
 * **
 * *****************************************************************************/
LString::LString(const LString &other)
{
	m_pBuffer = other.m_pBuffer;
	m_Length = other.m_Length;
	m_pCount = other.m_pCount;
	++(*m_pCount);

	objectPool.push_back(this);
}
//Assignment operator - copy
/******************************************************************************
 * **
 * ** FUNCTION NAME : operator=(const LString &other)
 * **
 * ** DESCRIPTION : This is used to create a operator for the string and assign the string.
 * **
 * ** RETURNS : *this
 * **
 * *****************************************************************************/
LString& LString::operator=(const LString &other)
{
	if(this != &other) {

		if(--(*m_pCount) == 0){
			delete []m_pBuffer ;
			m_pBuffer = NULL;
			delete m_pCount ;
		}

		m_pBuffer = other.m_pBuffer;
		m_Length = other.m_Length;
		m_pCount = other.m_pCount;
		++(*m_pCount);
	}

	return *this;
}
/******************************************************************************
 * **
 * ** FUNCTION NAME : operator =(const char ch)
 * **
 * ** DESCRIPTION : This is simple assignment operator
 * **
 * ** RETURNS : *this
 * **
 * *****************************************************************************/

LString & LString::operator=(const char* pstr)
{
	SetString(pstr);

	return *this;
}
/******************************************************************************
 * **
 * ** FUNCTION NAME : SetString(const char *pstr)
 * **
 * ** DESCRIPTION : Allocate a memory for the string and assign the string.
 * **
 * ** RETURNS : void
 * **
 * *****************************************************************************/

void LString::SetString(const char *pstr)
{
	if (strcmp(m_pBuffer,pstr) != 0)
	{
		if(--(*m_pCount) == 0){
			delete []m_pBuffer ;
			m_pBuffer = NULL;
			delete m_pCount ;
		}

		ValidateAndAllocateString(pstr);
	}
}
/******************************************************************************
 * **
 * ** FUNCTION NAME : Insert(int index, const char *pstr)
 * **
 * ** DESCRIPTION : Insert a character at the index.
 * **
 * ** RETURNS : void
 * **
 * *****************************************************************************/
void LString::Insert(int index, const char *pstr)
{
	if(index > m_Length)
		exit(-1);

	auto newLength = m_Length + strlen(pstr);
	char *pTemp = new char[newLength + 1]();

	if(index == 0) {
		strcpy(pTemp, pstr);
		strcat(pTemp, m_pBuffer);
	}else if(index == m_Length) {
		strcpy(pTemp, m_pBuffer);
		strcat(pTemp, pstr);
	}else {
		strncpy(pTemp, m_pBuffer, index);
		strcat(pTemp, pstr);
		strcat(pTemp, m_pBuffer + index);
	}

	if(--(*m_pCount) == 0){
		delete []m_pBuffer;
		m_pBuffer = NULL;
		delete m_pCount;
	}
	ValidateAndAllocateString(pTemp);

	delete []pTemp;
}
/******************************************************************************
 * **
 * ** FUNCTION NAME : Insert(int index, char ch, int count)
 * **
 * ** DESCRIPTION : Insert a character at the index.
 * **
 * ** RETURNS : void
 * **
 * *****************************************************************************/

void LString::Insert(int index, char ch, int count)
{
	if(index > m_Length)
		exit(-1);
	char* pTempChar = new char[count + 1]();
	for (auto i=0; i<count; i++)
	{
		pTempChar[i] = ch;
	}

	auto newLength = m_Length + count;
	char *pTemp = new char[newLength + 1]();

	if(index == 0) {
		strcpy(pTemp, pTempChar);
		strcat(pTemp, m_pBuffer);
	}else if(index == m_Length) {
		strcpy(pTemp, m_pBuffer);
		strcat(pTemp, pTempChar);
	}else {
		strncpy(pTemp, m_pBuffer, index);
		strcat(pTemp, pTempChar);
		strcat(pTemp, m_pBuffer + index);
	}

	if(--(*m_pCount) == 0){
		delete []m_pBuffer;
		m_pBuffer = NULL;
		delete m_pCount;
	}
	ValidateAndAllocateString(pTemp);

	delete []pTemp;
	delete []pTempChar;

}
/******************************************************************************
 * **
 * ** FUNCTION NAME : Remove(int index)
 * **
 * ** DESCRIPTION : Remove a character at the index.
 * **
 * ** RETURNS : void
 * **
 * *****************************************************************************/
void LString::Remove(int index)
{
	if(index > m_Length)
		exit(-1);

	char *pTemp = new char[m_Length]();

	int j = 0;
	for (int i=0; i <m_Length; i++)
	{
		if (i != index) {
			pTemp[j++] = m_pBuffer[i];
		}
	}
	pTemp[j] = '\0';

	if(--(*m_pCount) == 0){
		delete []m_pBuffer;
		m_pBuffer = NULL;
		delete m_pCount;
	}
	ValidateAndAllocateString(pTemp);

	delete []pTemp;
}
/******************************************************************************
 * **
 * ** FUNCTION NAME : RemoveAll(char ch)
 * **
 * ** DESCRIPTION : Remove all character ch
 * **
 * ** RETURNS : void
 * **
 * *****************************************************************************/
void LString::RemoveAll(char ch)
{
	int idxR = 0, idxW = 0;
	char *pTemp = new char[m_Length+1]();
	strcpy(pTemp, m_pBuffer);

	while (pTemp[idxR])
	{
		if (pTemp[idxR]!=ch)
		{
			pTemp[idxW++] = pTemp[idxR];
		}
		idxR++;
	}

	pTemp[idxW]='\0';

	if(--(*m_pCount) == 0){
		delete []m_pBuffer;
		m_pBuffer = NULL;
		delete m_pCount;
	}
	ValidateAndAllocateString(pTemp);

	delete []pTemp;
}
/******************************************************************************
 * **
 * ** FUNCTION NAME : TrimLeft(int n)
 * **
 * ** DESCRIPTION : Trim n character from left index.
 * **
 * ** RETURNS : void
 * **
 * *****************************************************************************/
void LString::TrimLeft(int n)
{
	if(n > m_Length)
		exit(-1);

	auto newLength = m_Length - n;
	char *pTemp = new char[newLength + 1]();

	strcpy(pTemp, m_pBuffer+n);

	if(--(*m_pCount) == 0){
		delete []m_pBuffer;
		m_pBuffer = NULL;
		delete m_pCount;
	}
	ValidateAndAllocateString(pTemp);

	delete []pTemp;
}
/******************************************************************************
 * **
 * ** FUNCTION NAME : TrimRight(int n)
 * **
 * ** DESCRIPTION : Trim n character from right index.
 * **
 * ** RETURNS : void
 * **
 * *****************************************************************************/
void LString::TrimRight(int n)
{
	if(n > m_Length)
		exit(-1);

	auto newLength = m_Length - n;
	char *pTemp = new char[newLength + 1]();

	strncpy(pTemp, m_pBuffer, newLength);

	if(--(*m_pCount) == 0){
		delete []m_pBuffer;
		m_pBuffer = NULL;
		delete m_pCount;
	}
	ValidateAndAllocateString(pTemp);

	delete []pTemp;
}
/******************************************************************************
 ** **
 ** ** FUNCTION NAME : Find(const char *pstr)
 ** **
 ** ** DESCRIPTION : find a character at the index position
 ** **
 ** ** RETURNS : void
 ** **
 ******************************************************************************/
int LString::Find(const char *pstr)
{
	int findStrLen = strlen(pstr);

	int i, j;
	for (j = 0; j <= (m_Length - findStrLen); ++j)
	{
		for (i = 0; i < findStrLen && pstr[i] == m_pBuffer[i + j]; ++i);
		if (i >= findStrLen) {
			return j;
		}
	}

	return -1;
}

/******************************************************************************
 * **
 * ** FUNCTION NAME : operator +(const LString &second)
 * **
 * ** DESCRIPTION : This is used to insert the m_pBuffer
 * **
 * ** RETURNS : *this
 * **
 * *****************************************************************************/
LString & LString::operator+(const LString &second)
{
	Insert(m_Length, second.m_pBuffer);
	return *this;
}

/******************************************************************************
 * **
 * ** FUNCTION NAME : operator +(const char *second)
 * **
 * ** DESCRIPTION : This is used to insert the character
 * **
 * ** RETURNS : *this
 * **
 * *****************************************************************************/
LString & LString::operator+(const char *second)
{
	Insert(m_Length, second);
	return *this;
}

/******************************************************************************
 * **
 * ** FUNCTION NAME : operator +=(const LString &second)
 * **
 * ** DESCRIPTION : This is used to ADD AND assignment operator.
 * **
 * ** RETURNS : *this
 * **
 * *****************************************************************************/
LString & LString::operator +=(const LString &second)
{
	Insert(m_Length, second.m_pBuffer);
	return *this;
}

/******************************************************************************
 * **
 * ** FUNCTION NAME : operator +=(const char *second)
 * **
 * ** DESCRIPTION : This is used to ADD AND assignment operator.
 * **
 * ** RETURNS : *this
 * **
 * *****************************************************************************/
LString & LString::operator +=(const char *second)
{
	Insert(m_Length, second);
	return *this;
}

/******************************************************************************
 * **
 * ** FUNCTION NAME : operator +=(const char ch)
 * **
 * ** DESCRIPTION : This is used to ADD AND assignment operator.
 * **
 * ** RETURNS : *this
 * **
 * *****************************************************************************/
LString & LString::operator +=(const char ch)
{
	Insert(m_Length, ch, 1);
	return *this;
}

/******************************************************************************
 * **
 * ** FUNCTION NAME : operator==(const LString& left, const LString& right)
 * **
 * ** DESCRIPTION : This is used to compare string operations
 * **
 * ** RETURNS : True or False
 * **
 * *****************************************************************************/
bool operator==(const LString& left, const LString& right) {
	return left.GetLength() == right.GetLength() && strcmp(left.GetString(),right.GetString()) == 0;
}

/******************************************************************************
 * **
 * ** FUNCTION NAME : operator!=(const LString& left, const LString& right)
 * **
 * ** DESCRIPTION : This is used to not compare string operations
 * **
 * ** RETURNS : True or False
 * **
 * *****************************************************************************/
bool operator!=(const LString& left, const LString& right) {
	return ! (left == right);
}

/******************************************************************************
 * **
 * ** FUNCTION NAME : operator==(const LString &left, const char* right)
 * **
 * ** DESCRIPTION : This is used to compare string operations
 * **
 * ** RETURNS : True or False
 * **
 * *****************************************************************************/
bool operator==(const LString &left, const char* right) {
	return left.GetLength() == strlen(right) && strcmp(left.GetString(),right) == 0;
}
/******************************************************************************
 ** **
 ** ** FUNCTION NAME : ValidateAndAllocateString(const char* pstr)
 ** **
 ** ** DESCRIPTION : allocate memory to the string
 ** **
 ** ** RETURNS : void
 ** **
 ** *****************************************************************************/
void LString::ValidateAndAllocateString(const char* pstr)
{
	auto length = strlen(pstr);
	bool found = false;

	std::vector<LString *>::iterator it;

	for( it = objectPool.begin(); it != objectPool.end(); it++)
	{
		if ((*it)->m_pBuffer == NULL)
			continue;

		if (strcmp((*it)->m_pBuffer, pstr) == 0)
		{
			m_pBuffer = (*it)->m_pBuffer;
			m_Length = (*it)->m_Length;
			m_pCount = (*it)->m_pCount;
			++(*m_pCount);
			found = true;
			break;
		}
	}

	if (!found)
	{
		m_pBuffer = new char[length + 1]();
		strcpy(m_pBuffer, pstr);
		m_Length = length;

		m_pCount = new int(1);
	}
}

std::vector<LString *> LString::objectPool;
