#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

string func(string data);



int main()
{

	fstream file;
	file.open("data.dat",ios::in);
	string data;
	getline(file,data);
	file.close();
	cout<<data.size()<<endl;
	string result;
	
	while(true)
	{
		result = data;
		data = func(data);

		if(data == result)
			break;
	}

	cout<<data.size() - 1<<endl;
	//cout<<data<<endl;
	int length = -1;
	for(int a = 'a' ; a <= 'z' ;a++)
	{
		//cout<<"i = "<<i<<endl;
		file.open("data.dat",ios::in);
		getline(file,data);
		
		for(int j = 0 ; j < data.size() ; j++ )
			if(data[j] == static_cast<char>(a) || data[j] == toupper(static_cast<char>(a) ) )
				data[j] = '\0';
		
		for(unsigned i = 0 ; i < data.size() ; i++)
			if(data[i] != '\0')
				result += data[i];

		while(true)
		{
			result = data;
			data = func(data);

			if(data == result)
				break;
		}
		
		if(length == -1)
			length = data.size();
		else if(data.size() < length)
			length = data.size();
		//cout<<data.size()<<endl;

		file.close();
	}
	cout<<"length = "<<length - 1<<endl;

	return 0;
}

string func(string data)
{
	for(unsigned i = 0; i < data.size() - 1 ; i++)
		{
			int j = i+1;
			if( (islower(data[i]) && isupper(data[j]) && toupper(data[i]) == data[j] ) || (isupper(data[i]) && islower(data[j]) && data[j] == tolower(data[i]) ) )
				data[j] = data[i] = '\0';
		}
			
	string result;
	for(unsigned i = 0 ; i < data.size() ; i++)
		if(data[i] != '\0')
			result += data[i];
	return result;
}