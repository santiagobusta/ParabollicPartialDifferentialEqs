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
	vector<double> u0(100);
	string archivo1 = "data/punto1fdm.txt";
	string archivo2 = "data/punto1bdm.txt";
	string archivo3 = "data/punto1cn.txt";

	int i;

	for( i = 0 ; i < 100 ; i++ )
		{
			u0[i] = sin((0.5*M_PI*i*2.0)/99);
		}

	ParabollicPDE punto1( u0 , 0.0 , 2.0 , 1.0 );

	punto1.fdm( 0.1 , 100 , zero , zero , archivo1 );
	punto1.bdm( 0.1 , 100 , zero , zero , archivo2 );
	punto1.cn( 0.1 , 100 , zero , zero , archivo3 );

	// a partir de aqui se halla el rmse de las soluciones
	
	ifstream datos;
	ofstream rmsedatos;
	string linea;
	vector<double> y(100);
	vector<double> y0(100);
	int posdel;
	double t = 0.;

	datos.open( archivo1.c_str() );
	rmsedatos.open( "data/rmsefdm.txt" );

	  if( datos.fail() || rmsedatos.fail() )
	  {
	    cout << "Error al abrir archivos" << endl;
	  }
	else
	  {
	    while( getline(datos , linea )  ) // esto recorre los datos en el tiempo
	      {
		
		i = 0;

		// asignamos la y calculada por los metodos
		while( (posdel = linea.find('\t')) != string::npos )
		  {
		    y[i] = stod( linea.substr( 0 , posdel ) );
		    linea.erase( 0 , posdel + 1 );
		    i++;
		  }

		// asignamos la y exacta
		for( i = 0 ; i < 100 ; i++ ) y0[i] = uexact( i * 20./100. , t );

		t += 0.1/100.;

		rmsedatos << rmse( y , y0 ) << endl;
		
	      }
	  }

	datos.close();
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
  return exp(-1 * M_PI * M_PI * t ) * sin( M_PI * x );
}

double rmse( vector<double> y , vector<double> y0 )
{
  double s = 0;
  int M = y.size();
  
  for( int i = 0 ; i < M ; i++ ) s += pow( y[i] - y0[i] , 2 );

  return sqrt( s / M );
}
