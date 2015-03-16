#include <iostream>
#include <string>

using namespace std;
class String{
public:
	String(const char *str="");
	String(const String& copy);
	~String();
	String& operator=(const String& assign);
private:
	size_t m_size;
	char *m_data;
};

//default construction function of String
String::String(const char *str)
{
	if(str==NULL)
	{
		m_data=new char[1];
		*m_data='\0';
		m_size=0;
	}
	else
	{
		int length=strlen(str);
		m_data=new char[length+1];
		strcpy(m_data,str);
		m_size=length;
	}
}

//destruction function of String
String::~String(void)
{
	delete []m_data;
}

//copy construction function
String::String(const String &other)
{
	//
	size_t len=strlen(other.m_data);
	m_data=new char[len+1];//this.m_data
	strcpy(m_data,other.m_data);
	m_size=len;//this.m_size
}

//assignment function
String& String::operator=(const String& other)
{
	if(this!=&other)
	{
		char *temp=new char[strlen(other.m_data)+1];
		strcpy(temp, other.m_data);
		delete []m_data;
		m_data=temp;
		m_size=strlen(other.m_data);
	}
	return *this;
}