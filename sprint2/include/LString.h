
/**********************************************************************************************************
 * *
 * * FILENAME : LString.h
 * *
 * * DESCRIPTION : Create a string class called LString that enables sharing of internal buffer between 
 * *               different objects, if they are holding the same copy. e.g. if a copy of a LString object 
 * *               is created, the new LString object will point to the same buffer as that of the old 
 * *               LString object 
 * *********************************************************************************************************/

#ifndef LSTRING_H
#define LSTRING_H
#include <iostream>
#include <vector>
#include<string.h>
using namespace std;
/***********************************************************************************************************
 * *
 * * CLASS Name : LString
 * *
************************************************************************************************************/
class LString {

	private:
		char *m_pBuffer;
		int *m_pCount;

		int m_Length;

		static std::vector<LString *> objectPool;

	public:
		LString();
		LString(const char* pstr);
		~LString();

		LString(const LString &other);
		LString & operator=(const LString &pstr);
		LString & operator=(const char* pstr);

		int GetLength() const {
			return m_Length;
		}

		const char * GetString() const {
			return m_pBuffer;
		}

		char operator[](int index) const {
			if(index > m_Length)
				exit(-1);
			return m_pBuffer[index] ;
		}
		// SetString
		void SetString(const char *pstr);
		// Insert a string at index
		void Insert(int index, const char *pstr);
		// Insert a character at index count times
		void Insert(int index, char ch, int count);
		// Remove a character from index
		void Remove(int index);
		// Remove all occurrences of a character
		void RemoveAll(char ch);
		// Trim n characters from left
		void TrimLeft(int n);
		// Trim n characters from right
		void TrimRight(int n);
		// find the count of the string
		int Find(const char *pstr);
		// Concatenate 2 LString objects
		LString & operator +(const LString &second);
		// Concatenate LString object with a string 
		LString & operator +(const char *second);
		// Concatenate and assign an LString object with other LString object
		LString & operator +=(const LString &second);
		// Concatenate and assign an LString object with a string
		LString & operator +=(const char *second);
		// Concatenate and assign an LString object with a character
		LString & operator +=(const char);



		void ValidateAndAllocateString(const char* pstr);
};
// Comparison operator to compare two LString objects and LString object with C-style string
bool operator==(const LString &left, const LString &right);
bool operator!=(const LString &left, const LString &right);
// Comparison operator to compare two LString objects and LString object with C-style string
bool operator==(const LString &left, const char* right);

#endif
