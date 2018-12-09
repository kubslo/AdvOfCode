#include <iostream>
#include <fstream>
#include <vector>

	int min(int a, int b)
	{
	//	std::cout << "Nazawa typu obiektu: " << typeid(T).name() << std::endl;
		if(a<b)
			return a;
		else
			return b;
	}
class Rect
{
public:
	Rect(int x,int y,int x2,int y2): m_x1(x),m_x2(x2+x),m_y1(y),m_y2(y2+y)
	{};
	
	void print() const
	{
		std::cout<<" "<<m_x1<<" "<<m_y1<<" "<<m_x2<<" "<<m_y2<<std::endl;
	}

	int getX() const
	{
		return m_x1;
	}
	
	int getY() const
	{
		return m_y1;
	}
	
	int getX2() const
	{
		return m_x2;
	}
	
	int getY2() const
	{
		return m_y2;
	}

private:
	int m_x1;
	int m_x2;
	int m_y1;
	int m_y2;
};
using namespace std;
int main()
{
	fstream file;
	file.open("data.dat",ios::in);
	std::vector<Rect> v;
	int maxX = 0,maxY = 0;
	while(!file.eof() )
	{ 	
		string str;
		getline(file,str,'@');
		getline(file,str,',');
		int x1 = stoi(str);
		getline(file,str,':');
		int y1 = stoi(str);
		getline(file,str,'x');
		int x2 = stoi(str);
		getline(file,str);
		int y2 = stoi(str);
		Rect r(x1,y1,x2,y2);
		//r.print();
		if(maxY < r.getY2() )
			maxY = r.getY2();
		if(maxX < r.getX2() )
			maxX = r.getX2();
		v.push_back(r);
	}	
	cout<<maxX<<" "<<maxY<<endl;

	//bool 
	int tab_test[maxX+1][maxY+1];
	for(int i = 0 ; i < maxX + 1 ;i++)
		for(int j = 0 ; j < maxY+1 ;j++)
			tab_test[i][j] = 0;

	for(int i = 0 ; i < v.size() /*- 1*/ ; i++)
	{
		for(int j = v[i].getX() ;j < v[i].getX2(); j++)
			for(int k = v[i].getY() ; k < v[i].getY2() ; k++ )
				tab_test[j][k]++;

		int wspolne_z = 0;
		//if(i < v.size()/2 )
			for(int j = 0; j < v.size()-1 ; j++)
			{

				if(i==j)
					j++;
				//////////int licznik = 0;
				if(v[i].getX() <= v[j].getX() && v[i].getY() <= v[j].getY() && v[j].getX() <= v[i].getX2() && v[j].getY() <= v[i].getY2() )
				{
					wspolne_z++;
					// for(int k = v[j].getX() ; k < min(v[i].getX2(),v[j].getX2() ) ; k++ )
					// 	for(int l = v[j].getY()  ; l < min(v[i].getY2(),v[j].getY2() ) ; l++ )
					// 	//	tab_test[k][l] = true;
				}

				else if(v[i].getX() >= v[j].getX() && v[i].getY() <= v[j].getY() && v[i].getX() <= v[j].getX2() && v[j].getY() <= v[i].getY2() )
				{
					wspolne_z++;
					// for(int k = v[i].getX() ; k < min(v[i].getX2(),v[j].getX2() ) ; k++ )
					// 	for(int l = v[j].getY() ; l < min(v[i].getY2(),v[j].getY2() ) ; l++ )
					// 		//tab_test[k][l] = true;
				}

				else if(v[i].getX() >= v[j].getX() && v[i].getY() >= v[j].getY() && v[i].getX() <= v[j].getX2() && v[i].getY() <= v[j].getY2() )
				{
					wspolne_z++;			
					// for(int k = v[i].getX() ; k < min(v[i].getX2(),v[j].getX2() ) ; k++ )
					// 	for(int l = v[i].getY(); l <min(v[i].getY2(),v[j].getY2() ) ; l++ )
					// 	//	tab_test[k][l] = true; 				
				}

				else if(v[i].getX() <= v[j].getX() && v[i].getY() >= v[j].getY() && v[j].getX() <= v[i].getX2() && v[i].getY() <= v[j].getY2() )
				{
					wspolne_z++;			
					// for(int k = v[j].getX() ; k < min(v[i].getX2(),v[j].getX2() ) ; k++ )
					// 	for(int l = v[i].getY() ; l < min(v[i].getY2(),v[j].getY2() ) ; l++ )
					// 	//	tab_test[k][l] = true;				
				}

			}
		if(wspolne_z == 0)
		{
			cout<<"brak wpsolnych pol dla : "<<i+1<<endl;
		}
	}

		int licznik = 0;
		for(int i = 0 ; i < maxX + 1 ;i++)
			for(int j = 0 ; j < maxY+1 ;j++)
				if(tab_test[i][j] >= 2)
					licznik++;

		cout<<"licznik : "<<licznik<<endl;
				







	return 0;
}