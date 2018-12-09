#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set> 



int main()
{
	std::fstream file;
	bool check = true;
	std::set<int> res;
	int temp = 0;
	res.insert( temp);
	std::pair<std::set<int>::iterator, bool> status;
	int i = 0;
	while(check)
	{
		file.open("data.dat",std::ios::in);
		while(!file.eof() )
		{

			std::string num;
			std::getline(file,num);
			temp += std::stoi(num); 
			status = res.insert(temp);
			if (!status.second)
   			{ 	
   				std::cout << "wartosc " << temp << " juz istnieje" <<std::endl;
   				check = false;
   				break;
			}
		
		}
		if (i++ == 0)
			std::cout<<"osotatnia wartosc : "<<temp<<std::endl;

		file.close();
	}

	return 0;
}
