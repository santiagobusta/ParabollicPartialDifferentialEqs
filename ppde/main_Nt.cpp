#include "parabollicPDE.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// funciones prueba para condiciones de frontera
double zero( double );
double ui( double );
double uf( double );

// funcion de solucion analitica primer punto
double uexact( double , double );

// funcion que halla la RMSE dado el archivo de datos y la solucion analitica
double rmse( vector<double> , vector<double> );

int main()
{
	//primer punto del Burden
	vector<double> u0( 10 );
	string archivo = "data/dummy.txt";
	int i;
	int Nt; // numero de divisiones temporales
	vector<double> y( 10 );
	vector<double> y0( 10 );
	ofstream rmsedatos;

	for( i = 0 ; i < 10 ; i++ )
		{
			u0[i] = sin((0.5*M_PI*i*2.0)/9);
			y0[i] = uexact( i * 2.0/9 , 0.1 );
		}

	ParabollicPDE punto1( u0 , 0.0 , 2.0 , 1.0 );

	rmsedatos.open( "data/rmsecn_Nt.txt" );

	if( rmsedatos.fail() )
	  {
	    cout << "Error al abrir archivos" << endl;
	  }
	else
	  {	
	    for( Nt = 1 ; Nt < 1000 ; Nt++ )
	      {
		punto1.cn( 0.1 , Nt , zero , zero , archivo );
		y = punto1.getu();
		rmsedatos << rmse( y , y0 ) << endl;
		//cout << Nt;
	      }
	  }
      
	rmsedatos.close();
	
	return 0;
}

double zero( double t )
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

double uexact( double x , double t )
{
  return exp( -0.25 * M_PI * M_PI * t ) * sin( 0.5 * M_PI * x );
}

double rmse( vector<double> y , vector<double> y0 )
{
  double s = 0;
  int M = y.size();
  
  for( int i = 0 ; i < M ; i++ ) s += pow( y[i] - y0[i] , 2 );

  return sqrt( s / M );
}
