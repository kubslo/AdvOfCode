#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;
struct Gurad_watch
{
	friend ostream& operator<<(ostream & o,const Gurad_watch& guard)
	{
		return o<<guard.m_month<<" - "<<guard.m_day<<"  "<<guard.m_hour<<" : "<<guard.m_minute<<endl;
	}

	//Gurad_watch() : m_month(0),m_day(0),m_minute(0),m_id(0),m_hour(0) {}
	Gurad_watch(unsigned short month,unsigned short day,unsigned short minute,unsigned short id,unsigned short hour) : m_month(month),m_day(day),m_hour(hour),m_minute(minute),m_id(id)
	{
		//cout<<"test"<<endl;
	 	m_start = 0;
		for(unsigned i = 0 ; i < 60 ; i++)
			m_sleep[i] = 0;
	}

	void start_sl(unsigned short month,unsigned short day,unsigned short minute,unsigned short hour)
	{
		if(m_start == 0 )
		{
			m_start_hour = m_hour = hour;
			m_day = day;
			m_start = minute;
			m_month = month;
		}
		
		else 
			cout<<"ERROR1"<<endl;

	}

	void finish_sl(unsigned short month,unsigned short day,unsigned short minute,unsigned short hour)
	{
		if( month == m_month && (day == m_day /*|| (day == m_day + 1 && m_start_hour == 23) */ ) )
		{ 	
	//		cout<<" id : "<<m_id<<" "<<" "<<m_start<<" "<<minute<<endl;
			for(unsigned i = m_start ; i < minute ; i++)
				m_sleep[i]++;
		}
		else
			cout<<"ERROR2"<<endl;
		m_start = 0;
	}

	int sum()
	{
		int sum = 0;
		for(int i = 0 ; i < 60 ;i++)
			sum += m_sleep[i];
		return sum;
	}

	//return a minute which the guard was asleep the most frequently during his all watches
	int max()
	{
		int max = m_sleep[0];
		int iter = 0;
		for(int i = 1 ; i < 60 ; i++)
			if(max < m_sleep[i])
			{
				iter = i;
				max = m_sleep[i];
			}
		return iter;
	}	
	//return number of times when guard was asleep in the same minute (max value of all minutes)

	int max2()
	{
		return m_sleep[max()];
	}


	unsigned short m_hour;
	unsigned short m_minute;
	unsigned short m_month;
	unsigned short m_day;
	unsigned short m_id;
	unsigned short m_start;
	unsigned short m_start_hour;
	unsigned short m_sleep[60];

};

int main()
{
	fstream file;
	file.open("dane.dat",std::ios::in);
	//map<int,vector<Gurad_watch> > guard;
	vector<Gurad_watch> guard;
	vector<string> b;
	//cout<<guard.size()<<endl;
	while(!file.eof() )
	{
		string buff;
		getline(file,buff);
		b.push_back(buff);
	}
	
	sort(b.begin(),b.end() );

	//cout<<"test"<<b.size()<<endl;
	vector<Gurad_watch>::iterator iter = guard.begin();

	for(int i = 0; i < b.size() ; i++ )
	{
	//	cout<<b[i]<<endl;
		unsigned short month = stoi(b[i].substr(6,2));
		unsigned short day = stoi(b[i].substr(9,2));
		unsigned short minute =  stoi(b[i].substr(15,2));
		unsigned short hour = stoi(b[i].substr(12,2));
		

		if(guard.size() == 0 && b[i].substr(19,5) == "Guard")
		{
			int id = stoi(b[i].substr(26,4) );
		//	cout<<"test"<<endl;
			guard.push_back(Gurad_watch(month,day,minute,id,hour));
			iter = guard.begin();
		}
		else if(b[i].substr(19,5) == "Guard" && guard.size() != 0)
			{

				int id = stoi(b[i].substr(26,4) );
			//	cout<<"id = "<<id<<endl;
				bool test = true;
				//std::cout<<iter->m_id<<std::endl;
				for(iter = guard.begin() ; iter < guard.end() ; iter++)
					if(id == iter->m_id)
					{
						test = false;
			//			cout<<iter->m_id<<" \t";
						break;
					}
				if(test)	
				{ 	
			//		cout<<iter->m_id<<endl;
					guard.push_back(Gurad_watch(month,day,minute,id,hour));
					iter = guard.end() - 1;
					//iter = (guard.end() - 1 );
				}
				

			} 
		else if(b[i].substr(19,5) == "falls" )
			{
			//	cout<<*iter<<"\n";
			//	cout<<iter->m_id<<endl;
			 	iter->start_sl(month,day,minute,hour);
			}
		else if(b[i].substr(19,5) == "wakes" )
			{	
			//	cout<<*iter<<"\n";	
			 	iter->finish_sl(month,day,minute,hour);
			}		
		
	}

	vector<Gurad_watch>::iterator iter1 = guard.begin(); 
	int max = iter1->sum();
	for(vector<Gurad_watch>::iterator iter2 = guard.begin() + 1 ; iter2 < guard.end() ; iter2++)
		if(iter2->sum() > max)
		{
			max = iter2->sum();
			iter1 = iter2;
		}
	//cout<<guard.size()<<endl;
	cout<<"result = "<<iter1->m_id * (iter1->max())<<" "<<iter1->m_id<<" "<<(iter1->max())<<endl;
	//cout<<" wynik : "<<" "<<iter1->m_id<<" "<<iter1->sum()<<" "<<iter1->max()<<" " <<iter1->max() * iter1->sum()<<endl;
	//	cout<<"test"<<b.size()<<endl;

	int max_ = guard[0].max2();
	int id_ = guard[0].m_id;
	int minute_ = guard[0].max();
	for(int i = 1 ; i < guard.size() ;i++)
	{
		if(max_ < guard[i].max2())
		{
			id_ = guard[i].m_id;
			max_ = guard[i].max2();
			minute_ = guard[i].max();
		}
	}

	cout<<"id = "<<id_<<" "<<minute_<<" "<<max_<<" result = "<<id_ * minute_<<endl;




	return 0;
}
