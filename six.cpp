#include "six.h"
#include <iostream>
//#include <nmmintrin.h> 

six::six()
	:wzb{(0x3),(0xc),(0x30),(0xc0),(0x300),(0xc00),(0x3000),(0xc000),(0x30000),(0xc0000),(0x300000),(0xc00000),(0x3000000),(0xc000000),(0x30000000),(0xc0000000)},
	fxb{(0b1010),(0b1011),(0b1011),(0b1001),(0b1110),(0b1111),(0b1111),(0b1101),(0b1110),(0b1111),(0b1111),(0b1101),(0b0110),(0b0111),(0b0111),(0b0101)},
	wzb1{(0x01),(0x4),(0x10),(0x40),(0x100),(0x400),(0x1000),(0x4000),(0x10000),(0x40000),(0x100000),(0x400000),(0x1000000),(0x4000000),(0x10000000),(0x40000000)},
	wzb2{(0x02),(0x08),(0x20),(0x80),(0x200),(0x800),(0x2000),(0x8000),(0x20000),(0x80000),(0x200000),(0x800000),(0x2000000),(0x8000000),(0x20000000),(0x80000000)},
	fxwzb{(0),(-1),(1),(0),(-4),(0),(0),(0),(4)} ,
	hxqzb{(0xff),(0xff00),(0xff0000),(0xff000000)},
	lxqzb{(0x03030303),(0x0c0c0c0c),(0x30303030),(0xc0c0c0c0)},
	t1(0b01010101010101010101010101010101),
	t2(0b10101010101010101010101010101010),
	zq(1) 
{
	qg=0b10101010100000100100000101010101;
	//qg=0b10010110100000100100000101010001;
	//qg=0b10101010100001100101010101010101;
}

six::~six()
{

}

u_int six::getqg()
{
	return qg;
}

void six::setqg(u_int sqg)
{
	qg = sqg;
	return;	
}

u_char six::testzs(u_int tqg,u_char zq,std::vector<zuosu>& zs)
{
	auto tmpqg = tqg;
	switch (zq)
	{
		case 1:
			tmpqg &= t1 ;
			break;
		case 2:
			tmpqg &= t2 ;
			break;		
		default:
			tmpqg = 0;
			break; 
	}
	for (u_char i=0; i<15; ++i)
	{
		if (getqzz(tqg,i) == zq)
		{
			auto w = getwzfx(i);
			zuosu tzs;			
			if ((w & fxy)> 0 && getqzz(tqg,i + fxwzb[fxy]) == 0)
			{
				tzs.s = i;
				tzs.d = i + fxwzb[fxy];
				zs.push_back(tzs) ;
			}			
			if ((w & fxz )> 0 && getqzz(tqg,i + fxwzb[fxz]) == 0)
			{
				tzs.s = i;
				tzs.d = i + fxwzb[fxz];
				zs.push_back(tzs) ;
			}
			if ((w & fxx )> 0 && getqzz(tqg,i + fxwzb[fxx]) == 0)
			{
				tzs.s = i;
				tzs.d = i + fxwzb[fxx];
				zs.push_back(tzs) ;
			}
			if ((w & fxs )> 0 && getqzz(tqg,i + fxwzb[fxs]) == 0)
			{
				tzs.s = i;
				tzs.d = i + fxwzb[fxs];
				zs.push_back(tzs) ;
			}
		}
	}
	return zs.size() ;
}

bool six::testwin(u_int tqg,u_char zq)
{
	std::vector<zuosu> zs;
	auto z = testzs(tqg,zq,zs);
	if ( z )
		return false;
	else
		return true;
}

u_char six::getzq()
{
	return zq;
}

void six::setzq(u_char szq)
{
	zq = szq;
	return;
}

u_char six::getfzq()
{
	return zq == 1?2:1;
}

int six::getqzsu(u_int qg,u_char zq)
{
	u_int tmp = qg ;
	switch (zq)
	{
		case 1:
			tmp &= t1 ;
			break;
		case 2:
			tmp &= t2 ;
			break;		
		default:
			tmp = 0;
			break; 
	}
	//__builtin_popcount函数取得1的个数 
	int qzs = __builtin_popcount(tmp) ;
	//int qzs = _mm_popcnt_u32(tmp);
	return qzs ;
}

u_char six::getqzz(u_int qg,u_char wz)
{
	auto twz = wzb[wz] ;
	twz &= qg ;
	twz >>= wz*2 ;
	return twz ;
}

u_int six::getwzfx(int wz)
{
	return fxb[wz];	
}

bool six::movqz(u_int tqg,u_char sqz,u_char fx)
{
	int dwz = sqz + fxwzb[fx] ;	//取得目标位置 
	//如果源棋子时执棋方棋子,且目的位置为空,且目的位置在棋盘上. 
	if ((getqzz(tqg,sqz) == zq) and (dwz < 16) and (dwz >= 0) and (getqzz(tqg,dwz) == 0))
	{
		//到此可以移动到目标位置,先清除源棋子
		u_int twz = wzb[sqz] ;
		qg &= ~twz;
		//将目标位置置为执棋方棋子
		twz = zq ;
		twz <<= (dwz * 2) ;
		qg |= twz;
		
		//计算目的位置行线棋子数
		//std::cout << "该行有棋子数:" << testhxqzs(qg,dwz) <<" 该列有棋子数:" << testlxqzs(qg,dwz) << std::endl;
		
		//std::cout << "吃掉对方";
		std::vector<u_char> bcz = testcz(qg,dwz);
		if (bcz.empty())
		{
			//std::cout << "0" << std::endl;
		}
		else
		{
			//std::cout << bcz.size() << "个棋子,被吃掉棋子:" << bcz[0] << std::endl;
			for (auto bczwz : bcz)
			{
				u_int b;
				if (1 == zq)
				{
					b = wzb2[bczwz];
				}
				else
				{
					b = wzb1[bczwz];
				}
				b = ~b;
				qg &= b;
			}
		}
		
		
		//交换执棋方
		zq = zq == 1?2:1;
		return true ; 
	}
	else
	{
		return false ;
	}
}

std::vector<u_char> six::testcz(u_int tqg, u_int wz)
{
	std::vector<u_char> bcz;//被吃棋子的位置数组
	bool zfx = false;//左方向有否己方棋子,为真有,为假没有 
	bool yfx = false;//
	bool sfx = false;
	bool xfx = false;
	bool hqz3 = false;//该行是否只有3个棋子,为真有. 
	bool lqz3 = false;
	bool wfqz2 = false;//为真表示我方棋子在该行上只有2个棋子 
	bool wfqzl2 = false;//为真表示我方棋子在该列上只有2个棋子
	bool ldk = false;//行的两端位置有否空,为真表示两端至少有一个空位 
	bool lldk = false;//列的两端位置有否空,为真表示两端至少有一个空位 

	//检测该位置在该行上吃子
	//检测该子左或右有无自己子
	//检测该子左方有无位置

	u_char jfz = getqzz(tqg, wz);//己方棋子值
	if ((getwzfx(wz) & fxz) && (jfz == getqzz(tqg, wz + 1)))	//如果该位置的左方有位置且有一个己方棋子
		zfx = true;
	if ((getwzfx(wz) & fxs) && (jfz == getqzz(tqg, wz + 4)))	//如果该位置的上方有位置且有一个己方棋子
		sfx = true;
	if ((getwzfx(wz) & fxx) && (jfz == getqzz(tqg, wz - 4)))	//如果该位置的下方有位置且有一个己方棋子
		xfx = true;
	if ((getwzfx(wz) & fxy) && (jfz == getqzz(tqg, wz - 1)))	//如果该位置的右方有位置且有一个己方棋子
		yfx = true;
	if (3 == testhxqzs(tqg, wz))	//测试该行上是否只有3个棋子
		hqz3 = true;
	if (3 == testlxqzs(tqg, wz))	//测试该列上是否只有3个棋子
		lqz3 = true;
	if ((0 == getqzz(tqg, wz / 4 * 4)) || (0 == getqzz(tqg, wz / 4 * 4 + 3)))	//测试该行的两端位置有否空
		ldk = true;
	if ((0 == getqzz(tqg, wz % 4 )) || (0 == getqzz(tqg, wz % 4 + 12)))	//测试该列的两端位置有否空
		lldk = true;
	//测试在该行上我方棋子是否只有2个.
	u_int tq = tqg & hxqzb[wz / 4];
	if (2 == getqzsu(tq, zq))
		wfqz2 = true;
	//测试在该列上我方棋子是否只有2个.
	u_int tql = tqg & lxqzb[wz % 4];
	if (2 == getqzsu(tql, zq))
		wfqzl2 = true;
	//取得对方执棋
	u_int dzq = zq == 1 ? 2 : 1;
	if (ldk && hqz3 && wfqz2 && (zfx || yfx))
	{
		//有一个对方棋子被吃,则找出该子的位置,将其写入
		for (int i = 0; i < 4; ++i)
		{
			if (getqzz(qg, wz / 4*4 + i) == dzq)
			{
				bcz.push_back(wz / 4*4 + i);
				break;
			}
		}
	}
	if (lldk && lqz3 && wfqzl2 && (sfx || xfx))
	{
		for (u_char i = 0;i < 16;i = i + 4)
		{
			if (getqzz(qg, wz % 4 + i) == dzq)
			{
				bcz.push_back(wz % 4 + i);
				break;
			}
		}
	}
	return bcz;
}

int six::testhxqzs(u_int tqg,u_int wz) 
{
	u_int t = hxqzb[wz/4] ;
	tqg &= t ;
	return __builtin_popcount(tqg);
}

int six::testlxqzs(u_int tqg,u_int wz) 
{
	u_int t = lxqzb[wz%4] ;
	tqg &= t ;
	return __builtin_popcount(tqg);
}

bool six::dispqg()
{
	u_int t = 0b11000000000000000000000000000000;
	for (int i = 0; i < 4 ; ++i)
	{
		for (int j = 0; j < 4 ; ++j)
		{
			u_int tqg = qg;
			tqg &= t;
			tqg >>= (30 - (i * 4 + j) * 2);
			std::cout << tqg << " "; 
			t >>= 2;			
		}
		std::cout << std::endl;
	}
	return true;		
} 
