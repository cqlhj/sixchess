#include "ai.h"
#include <iostream>

u_int setqgot( u_char zq,u_char qzs,u_char fqzs,u_char zs )
{
	u_int t = zs;
	t <<= 3;
	t |= fqzs;
	t <<= 3;
	t |= qzs;
	t <<= 2;
	t |= zq;
	return t;
}

AI::AI( QgData sqg ):qd( sqg )
{
	ts.setqg( sqg.qg );
	u_char zq = getzq( sqg.ot );
	ts.setzq( zq );
	ts.dispqg();
	std::cout<<"AI Class create"<<std::endl;
	std::cout<<"ot="<<std::hex<<qd.ot<<std::endl;
}

AI::~AI()
{

}

u_char AI::getzq( u_int ot )
{
	return ( u_char )( ot & 0x3 );
}

u_char AI::getqzs( QgData qd )
{
	u_char zq = qd.ot & 0x3;
	return ( u_char )ts.getqzsu( qd.qg,zq );
}

