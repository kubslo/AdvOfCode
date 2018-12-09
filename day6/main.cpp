#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

class Point
{
public:
	Point(int x,int y) : m_x(x),m_y(y)
	{}
	int getX() const {return m_x;}
	int getY() const {return m_y;}

private:
	int m_x;
	int m_y;
};

int main()
{

	fstream file;
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
	int table_of_points[maxX+1][maxY+1] = { 0 };
	//cout<<table_of_points[29][72]<<endl;
	for(int i = 0; i < point.size() ; i++)
		table_of_points[point[i].getX()][point[i].getY()] = i+1;

	for(int i = 0 ; i <= maxX ; i++)
	{
		for(int j = 0 ; j <= maxY ; j++)
		{
			cout<<table_of_points[i][j];
		}
	}
	


	return 0;
}