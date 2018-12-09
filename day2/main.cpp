#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main()
{
	fstream file;
	file.open("dane.dat",ios::in);
	int two = 0;
	int three = 0;
	vector<string> str_data;

	while(!file.eof() )
	{
		multiset<char> values;
		string str;
		getline(file,str);
		str_data.push_back(str);
		for(int i = 0 ; i < str.size() ; i++)
			values.insert(str[i]);
		//for(multiset<char>::iterator iter = values.begin(); iter != values.end();iter++)
			//std::cout<<*iter<<std::endl;
		sort(str.begin(),str.end());
		bool check1 = true;
		bool check2 = true;
		for(int i = 0 ; i < str.size() ; i++)
		{
			if(str[i] != str[i+1])
			{ 	
				if(values.count(str[i]) == 2 && check1)
				{
					two++;
					check1 = false;
				}
				else if(values.count(str[i]) == 3 && check2)
				{
					three++;
					check2 = false;
				}
			}

		}
	//	std::cout<<str<<std::endl;
	}
	std::cout<<"wynik : "<<two* three<<std::endl;
	for(int i = 0 ; i < str_data.size() - 1 ; i++ )
	{
		for(int j = i+1 ;  j < str_data.size() ;j++)
		{
			int s = str_data[i].size();

			for(int k = 0; k < str_data[i].size() ;k++)
			{
				if(str_data[i][k] == str_data[j][k])
					s--;
			}
			if(s == 1)
			{
				cout<<str_data[i]<<std::endl;
				cout<<str_data[j]<<std::endl;
				string temp;
				for(int k = 0; k < str_data[i].size() ;k++)
				{
					if(str_data[i][k] == str_data[j][k])
						temp += str_data[i][k];
				}
				cout<<temp<<endl;
				break;
			}
		}
	}

	return 0;
}
