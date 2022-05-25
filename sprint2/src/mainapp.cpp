
/**********************************************************************************************************
 * *
 * * FILENAME : mainapp.cpp
 * *
 * * DESCRIPTION : Create a string class called LString that enables sharing of internal buffer between 
 * *               different objects, if they are holding the same copy. e.g. if a copy of a LString object 
 * *               is created, the new LString object will point to the same buffer as that of the old 
 * *               LString object 
 * *********************************************************************************************************/

#include "LString.h"
using namespace std;
/************************************************************************************************************
 * **
 * ** FUNCTION NAME : main
 * **
 * **DESCRIPTION : execution of program starts from main function
 * **
 * **RETURNS : returns 0 on successful execution.
 * **
 * ***********************************************************************************************************/
int main()
{
	LString s1 = "Hello World! ";

	cout << "S1 object string " << s1.GetString() << " and address of the buffer " << (void *)s1.GetString() << endl;

	LString s2(s1); //s2 & s1 are pointing to same buffer	

	cout << endl << "S1 object string " << s1.GetString() << " and address of the buffer " << (void *)s1.GetString() << endl;
	cout << "S2 object string " << s2.GetString() << " and address of the buffer " << (void *)s2.GetString() << endl;

	s1 = "New string"; //s1 will allocate new memory. s2 will continue pointing to Hello World!

	cout << endl << "S1 object string " << s1.GetString() << " and address of the buffer " << (void *)s1.GetString() << endl;
	cout << "S2 object string " << s2.GetString() << " and address of the buffer " << (void *)s2.GetString() << endl;

	LString s3(s2); 	//s3 & s2 will point to same buffer
	cout << endl <<"Output for s3(s2)" <<endl;	

	cout << endl << "S1 object string " << s1.GetString() << " and address of the buffer " << (void *)s1.GetString() << endl;
	cout << "S2 object string " << s2.GetString() << " and address of the buffer " << (void *)s2.GetString() << endl;
	cout << "S3 object string " << s3.GetString() << " and address of the buffer " << (void *)s3.GetString() << endl;

	LString s4(s2); 	//s2,s3 & s4 will point to same buffer
	cout << endl <<"Output for s4(s2)" <<endl;	

	cout << endl << "S1 object string " << s1.GetString() << " and address of the buffer " << (void *)s1.GetString() << endl;
	cout << "S2 object string " << s2.GetString() << " and address of the buffer " << (void *)s2.GetString() << endl;
	cout << "S3 object string " << s3.GetString() << " and address of the buffer " << (void *)s3.GetString() << endl;
	cout << "S4 object string " << s4.GetString() << " and address of the buffer " << (void *)s4.GetString() << endl;

	s3 = s1 ; //s3 & s1 are pointing to same buffer
	cout << endl << "Output for s3=s1" <<endl;	
	cout << endl << "S1 object string " << s1.GetString() << " and address of the buffer " << (void *)s1.GetString() << endl;
	cout << "S2 object string " << s2.GetString() << " and address of the buffer " << (void *)s2.GetString() << endl;
	cout << "S3 object string " << s3.GetString() << " and address of the buffer " << (void *)s3.GetString() << endl;
	cout << "S4 object string " << s4.GetString() << " and address of the buffer " << (void *)s4.GetString() << endl;

	LString s5 = "Hello World!"; //s5, s2, s4 are pointing to same buffer
	cout << endl << "S1 object string " << s1.GetString() << " and address of the buffer " << (void *)s1.GetString() << endl;
	cout << "S2 object string " << s2.GetString() << " and address of the buffer " << (void *)s2.GetString() << endl;
	cout << "S3 object string " << s3.GetString() << " and address of the buffer " << (void *)s3.GetString() << endl;
	cout << "S4 object string " << s4.GetString() << " and address of the buffer " << (void *)s4.GetString() << endl;
	cout << "S5 object string " << s5.GetString() << " and address of the buffer " << (void *)s5.GetString() << endl;

	s3.SetString("Hello World!"); //s3,s2,s4 & s5 are pointing to the same buffer
	cout << endl <<"Output for s3.SetString('Hello World!')" <<endl;
	cout << endl << "S1 object string " << s1.GetString() << " and address of the buffer " << (void *)s1.GetString() << endl;
	cout << "S2 object string " << s2.GetString() << " and address of the buffer " << (void *)s2.GetString() << endl;
	cout << "S3 object string " << s3.GetString() << " and address of the buffer " << (void *)s3.GetString() << endl;
	cout << "S4 object string " << s4.GetString() << " and address of the buffer " << (void *)s4.GetString() << endl;
	cout << "S5 object string " << s5.GetString() << " and address of the buffer " << (void *)s5.GetString() << endl << endl;

	s3.Insert(0, "1My ");
	s3.Insert(s3.GetLength(), " Program ");
	cout << "GetString for s3.Insert(0, '1My ') after Insert method --> "<< s3.GetString() << endl << endl;

	s3.Insert(10,'z', 5);
	cout << "GetStrig  for s3.Insert(10,'z', 5) after inserting a char in a position for n times --> "<< s3.GetString() << endl << endl;

	s3.Remove(0);
	cout << "GetString for s3.Remove(0) after removing a character through index --> "<< s3.GetString() << endl << endl;

	s3.RemoveAll('z');
	cout << "GetString for s3.RemoveAll('z') after removing all occurrences of a character(z) --> "<< s3.GetString() << endl << endl;

	cout << "GetString  before call Trim method--> "<< s1.GetString() << endl << endl;
	s1.Insert(0, "abc");
	s1.Insert(s1.GetLength(), "abc");
	cout << "GetString for s1.Insert(0, 'abc') after Insert method--> "<< s1.GetString() << endl << endl;

	s1.TrimLeft(3);
	cout << "GetString after Trim n characters from left of s1 --> "<< s1.GetString() << endl << endl;

	s1.TrimRight(3);
	cout << "GetString after Trim n characters from Right of s1--> "<< s1.GetString() << endl << endl;

	cout << "Index of given pattern in string --> "<< s1.Find("ring") << endl << endl;

	s3 = s3 + s5;
	cout << "GetString for s3=s3+s5 after + operator with LString object --> "<< s3.GetString() << endl << endl;

	s3 = s3 + "added ";
	cout << "GetString for s3=s3+'added' after + operator with string --> "<< s3.GetString() << endl << endl;

	s3 += "twice";
	cout << "GetString for s3 += 'twice' after += operator with string --> "<< s3.GetString() << endl << endl;

	s3 += '.';
	cout << "GetString for s3 += '.' after += operator with char --> "<< s3.GetString() << endl << endl;

	s3 += s5;
	cout << "GetString for s3 += s5 after += operator with LString object --> "<< s3.GetString() << endl << endl;

	LString s6 = "Sample1";
	LString s7 = "Sample2";

	if (operator==(s6,s7))
	{
		cout << "LString objects are same"<< endl << endl;
	}
	else
	{
		cout << "LString objects are not same"<< endl << endl;
	}

	if (operator==(s6,"Sample1"))
	{
		cout << "LString object and string constant are same"<< endl << endl;
	}
	else
	{
		cout << "LString object and string are not same"<< endl << endl;
	}
}

