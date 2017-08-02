#include <iostream>
#include <vector>
#include "six.h"
#include "ai.h"

int main(int argc, char** argv) 
{

	six s;

	QgData t;
	t.qg = s.getqg();
	t.ot = setqgot(s.getzq(),s.getqzsu(t.qg,s.getzq()),0,0);
	AI ai(t);

	s.dispqg();
	int sqz,fx;
	while (std::cin >> sqz >> fx)
	{
		s.movqz(s.getqg(),sqz,fx) ;
		s.dispqg() ;
		if (s.testwin(s.getqg() ,s.getzq() ) )
		{
			std::cout<<s.getfzq()<<"获得胜利!"<<std::endl;
			break;
		}
		std::vector<zuosu> tz;
		s.testzs(s.getqg(),s.getzq() ,tz);
		if (tz.empty() )
		{
			std::cout<<"对方已经无路可走"<<std::endl;
		}
		else
		{
			std::cout<<"共有"<<tz.size()<<"步"<<std::endl;
			for (auto i:tz)
			{
				std::cout<<"可以从"<<(int)i.s<<"走到"<<(int)i.d<<std::endl;
			}
		}
		//std::cout << "位置" << wz << "的棋子:"<< s.getqzz(s.getqg() ,wz) << std::endl; 
	}
	return 0;
}

