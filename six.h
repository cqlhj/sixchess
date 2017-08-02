#pragma once
#include <vector>

/*******************************************************************************************************
用一个无符号int来表示棋格,每两位表示一个棋格点上棋子的值,为0则没有
棋子,为1表示此位置有一颗1方棋子,为2表示2方棋子,如果为3,则非法.
在一个4*4的棋格上共计有16个位置.用0-15来表示各位置,从右到左,从下到上:
15 14 13 12
11 10  9  8
 7  6  5  4
 3  2  1  0 
该u_int int 的最低两位就在0号位置,最高位置在15号.
假如给一个位置,则可以通过0*2=0来得到该位置在棋格int的第0位:0000 0000 0000 0000 0000 0000 0000 00XX
如果给定位置为8,则8*2=16来得到在棋格的第16位 :0000 0000 0000 00XX 0000 0000 0000 0000 
要移动棋子,先选择位置,再是方向.上下左右分别为8421 
*******************************************************************************************************/
typedef unsigned int u_int;
typedef unsigned char u_char;
struct zuosu
{
	u_char s;
	u_char d;
};
class six
{
	public:
		six();
		~six();
		u_int getqg();
		void setqg(u_int sqg);		//设置棋格数据
		u_char getzq();				//取执棋方
		void setzq(u_char);			//设置执棋
		u_char getfzq();			//取执棋方的反方
		bool dispqg();
		u_char testzs(u_int tqg,u_char zq,std::vector<zuosu>& zs);	//计算执棋方共有多少着数 ,将所有着数放入容器 
		bool testwin(u_int tqg,u_char zq);	//测试执棋方此时是否已经胜利 
		int getqzsu(u_int qg,u_char zq);	//取得zq方的棋子数目 
		u_char getqzz(u_int qg,u_char wz);	//取得在qg上位置wz的棋子值 
		u_int getwzfx(int wz);	//取得某个位置可以行进的方向 ,返回值为4位二进制,从高位起依次为:上下左右,该位为1可以 
		bool movqz(u_int tqg,u_char sqz,u_char fx) ;	//在棋格qg上将sqz位置的执棋方棋子移动到fx位置. fx按0b1111,最高位表示上,
		int testhxqzs(u_int tqg,u_int wz) ;	//测试位置wz棋子所在行线的所有棋子总数. 
		int testlxqzs(u_int tqg,u_int wz) ;	//                  列 
		std::vector<u_char> testcz(u_int tqg,u_int wz) ;	//测试目的位置wz 上的棋子能吃掉对方棋子吗,如果可以则将被吃掉棋子的位置放入vector 
	protected:
		u_int qg; 
		u_char zq;		//执棋方,只有1和2.为1表示此时该1方下棋. 
		const u_int wzb[16];	//位置表.通过查表法取得某个位置的棋子在qg的哪个二进制位. 比如:wzb[3]=0xc0,表示位置3的位在qg的0b000000000000000000000000XX000000 
		const u_int fxb[16];	//方向表.通过查表法取得某个位置的棋子可以行进的方向.比如:fxb[5]=0b1111,表示该位置的棋子上下左右都可以;fxb[0]=0b1010,可以上和左. 
		const u_int fxz = 0x2;	//方向左 
		const u_int fxy = 0x1;	//方向右 
		const u_int fxs = 0x8;	//方向上 
		const u_int fxx = 0x4;	//方向下 
		const u_int wzb1[16];	//1方棋子置位表.当需要将某位置的空位置为1方棋子时,用1wzb[x]里的值与棋格相或则成.
		const u_int wzb2[16];	//2方棋子置位表.当需要将某位置的空位置为2方棋子时,用1wzb[x]里的值与棋格相或则成.
		const int fxwzb[9];	//通过此方向位置表,取得某个位置棋子的上下左右的位置.比如8是向上,fxwzb[8]里的值就是-4,用当前棋子位置与-4相加及得左方向位置.fxwzb[4]里是+4.因为最大值是8,所以这个数组共有9个元素 
		const u_int hxqzb[4];	//供函数testhxqzs使用,整个棋盘共有4行,为了测试某行的棋子数,将别的行清零,再数整个qg里1的个数即可.此数组即为屏蔽数.
		const u_int lxqzb[4];	//列线棋子表 
		
		const u_int t1 ;	//将此数与qg相与后,得到数的高位则是1方棋子. 
		const u_int t2 ;	//将此数与qg相与后,得到数的高位则是2方棋子. 
		
};
