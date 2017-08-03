#pragma once
#include "six.h"

struct QgData
{
	u_int qg;
	u_int ot;	//第12位执棋，345位1方棋子数，678位2方棋子数，9,10,11,12,13位执棋方着数，
};

u_int setqgot(u_char zq,u_char qzs,u_char fqzs,u_char zs);

class AI
{
	protected:
		QgData qd;	
	public:
		AI(QgData sqg);
		~AI();
		u_char getzq( u_int ot );
		u_char getqzs( QgData qd );
		u_char getfqzs( QgData qd );
		u_char getzs( QgData qd );
		six ts;
};
