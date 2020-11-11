#include "parabollicPDE.h"
#include <vector>
#include <string>
#include <cmath>

using namespace std;

double zero(double t)
{
	return 0.0;
}

double ui(double t)
{
	return 0.05*t*t;
}

double uf(double t)
{
	return -0.1*t;
}

int main()
{
	//primer punto del Burden
	vector<double> u0(100);
	string archivo1 = "punto1fdm.txt";
	string archivo2 = "punto1bdm.txt";
	string archivo3 = "punto1cn.txt";

	for( int i = 0 ; i < 100 ; i++ )
		{
			u0[i] = sin((0.5*M_PI*i*2.0)/99);
		}

	ParabollicPDE punto1( u0 , 0.0 , 2.0 , 1.0 );

	punto1.fdm( 0.1 , 50 , zero , zero , archivo1 );
	punto1.bdm( 0.1 , 50 , zero , zero , archivo2 );
	punto1.cn( 0.1 , 50 , zero , zero , archivo3 );

	return 0;
}
