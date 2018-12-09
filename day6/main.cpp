#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


using namespace std;

class Point
{
public:
	Point(int x,int y) : m_x(x),m_y(y),m_id(-1)
	{}
	int getX() const {return m_x;}
	int getY() const {return m_y;}
	int getId() const {return m_id;}
	void setId(int id) {m_id = id;}

private:
	int m_x;
	int m_y;
	int m_id;
};

int main()
{

	fstream file,file2;
	file2.open("test.dat",ios::out);
	file.open("data.dat",ios::in);
	vector<Point> point;
	int maxX = -1;
	int maxY = -1;
	while(!file.eof() )
	{
		string line;
		getline(file,line);
		point.push_back( Point(stoi( line.substr(0,3) ),stoi( line.substr(5,3) ) ) );
		//cout<<point.back().getX()<<" "<<point.back().getY()<<endl;
		if(maxY < point.back().getY())
			maxY = point.back().getY();

		if(maxX < point.back().getX())
			maxX = point.back().getX();

	}

	cout<<maxX<<" "<<maxY<<endl;
	//int table_of_points[maxX+1][maxY+1] = { 0 };
	int table_of_points_temp[maxX+1][maxY+1] = { 0 };
	int table_of_frequence[point.size() + 1] = { 0 };
	
	for(int i = 0; i < point.size() ; i++)
	{
		point[i].setId(i+1);
		//cout<<i<<" "<<point[i].getId()<<endl;
		//cout<<point[i].getX()<<" "<<point[i].getY()<<endl;
	}



	for(int i = 0 ; i <= maxX ; i++)
	{
		for(int j = 0 ; j <= maxY ; j++)
		{
			bool is_equal = false;
			//double length = sqrt(pow(point[0].getX() - i,2) + pow(point[0].getY() - j,2) );
			double length = abs(point[0].getX() - i) + abs(point[0].getY() - j);
			int id = point[0].getId();
			//int id = 0;
			for(int k = 1 ; k < point.size() ; k++)
			{
				//double length2 = sqrt(pow(point[k].getX() - i,2) + pow(point[k].getY() - j,2));
				double length2 = abs(point[k].getX() - i) + abs(point[k].getY() - j);
				if(length2 == length)
				{
					//cout<<length<<" "<<length2<<" "<<point[k].getX()<<" "<<point[0].getX()<<endl;
					is_equal = true;
					id = 0;
				}
				else if(length2 < length)
				{
					is_equal = false;
					length = length2;
					id = point[k].getId();
				}
				//if(i == 64)
					//cout<<length<<" "<<length2<<" "<<point[k].getId
			}

			if(is_equal)
				table_of_points_temp[i][j] = 0;
			else
				table_of_points_temp[i][j] = id;
			//table_of_frequence[id]++;
			//cout<<i<<" "<<j<<" "<<id<<endl;

			file2<<table_of_points_temp[i][j]<<" ";
		}
		file2<<endl;
	}

	for(int i = 0 ; i <= maxX ; i++)
		for(int j = 0 ; j <= maxY ; j++)
			table_of_frequence[table_of_points_temp[i][j] ]++;

	//removing infinite areas
	for(int i = 0 ; i <= maxX ; i++)
		for(int j = 0 ; j <= maxY ; j++)
			if(i == 0 || j == 0 || j == maxY || i == maxX)
				table_of_frequence[table_of_points_temp[i][j] ] = 0;
	

	int max = table_of_frequence[1];
	cout<<"0 "<<table_of_frequence[0]<<"\n 1 "<<table_of_frequence[1]<<endl;
	for(int i = 2 ; i < point.size() + 1;i++ )
	{
		cout<<i<<" "<<table_of_frequence[i]<<endl;
		if(max < table_of_frequence[i])
			max = table_of_frequence[i];
	}
	cout<<"czestotliwosc "<<max<<endl;


	


	return 0;
}