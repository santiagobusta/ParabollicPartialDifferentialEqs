#include "parabollicPDE.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

//contructor recive ( vector con las condiciones iniciales de la funcion u (la longitud de este vector define el paso en la coordenada espacial), los limites de la coordenada espacial x0 y xf y el parametro alpha de la ecuacion diferencial )
ParabollicPDE::ParabollicPDE( vector<double> u0 , double xi , double xf , double alpha )
{
	//definicion de variables iniciales
	setalpha( alpha );
	setxi( xi );
	setxf( xf );
	setnx( u0 );
	setu0( u0 );
	setx();
}

//Funciones set
void ParabollicPDE::setalpha( double a )
{
	alpha = a;
}

void ParabollicPDE::setxi( double x )
{
	xi = x;
}

void ParabollicPDE::setxf( double x )
{
	xf = x;
}

void ParabollicPDE::setnx( vector<double> u )
{
	nx = u.size();
}

void ParabollicPDE::setu0( vector<double> u )
{
	u0 = u;
}

void ParabollicPDE::setx()
{
	x = u0;

	for( int i = 0 ; i < nx ; i++ )
	{
		x[i] = xi + i*(xf-xi)/(nx-1);
	}
}

void ParabollicPDE::setbdm( double c )
{
	a = u0;
	b = u0;

	a[0] = 1 + 2*c;
	b[0] = - c/a[0];

	for( int i = 1 ; i < nx ; i++ )
	{
		a[i] = 1 + 2*c + c*b[i - 1];
		b[i] = - c/a[i];
	}
}

void ParabollicPDE::setcn( double c )
{
	a = u0;
	b = u0;

	a[0] = 1 + c;
	b[0] = - c/(2*a[0]);

	for( int i = 1 ; i < nx ; i++ )
	{
		a[i] = 1 + c + (c*b[i - 1])/2;
		b[i] = - c/(2*a[i]);
	}
}

//Funciones get
vector<double> ParabollicPDE::getx()
{
	return x;
}

//Funciones para el metodo Forward Difference Method
void ParabollicPDE::fdm( double t , int nt , double (*ui)( double ) , double (*uf)( double ) , string archivo )
{
	//se definene estas funciones nuevamente por si se redefinio el vector u0 con la funcion setu0
	setnx( u0 );
	u = u0;

	//variables para facilitar el codigo
	double h = (xf-xi)/(nx-1);
	double k = t/(nt-1);
	double c = (alpha*alpha*k)/(h*h);

	//si se utiliza un archivo ya aexistente se sobre escriben los resultados
	ofstream archivo_sal;
	archivo_sal.open( archivo.c_str() );

	//comprobar la estabilidad de la solucion
	if (c > 0.5)
	{
		cout << "Los parametros escogidos no permiten un resultado estable utilizando este metodo, por favor modifique los parametros, se recomienda utilizar un numero de particiones temporales mayor o un tiempo finla menor\n";
	}

	//se aplican las condiciones de frontera ui(t) y uf(t) y se almacena la condicion inicial en el archivo
	u0[0] = ui( 0.0 );
	u0[nx-1] = uf( 0.0 );
	saveline( u0 , archivo );

	//ciclo para solucionar un paso temporal y almacenarlo en el vector u y para almacenar el vector u en el archivo
	for( int i = 0 ; i < nt ; i++ )
	{
		u[0] = ui( i*k );
		u[nx-1] = uf( i*k );

		stepfdm( t , nt );

		u[0] = ui( (i+1)*k );
		u[nx-1] = uf( (i+1)*k );

		saveline( u , archivo );
	}
}
//solucion del vector u para un paso temporal 
void ParabollicPDE::stepfdm( double t , int nt )
{
	double h = (xf-xi)/(nx-1);
	double k = t/(nt-1);
	double c = (alpha*alpha*k)/(h*h);

	for( int i = 1 ; i < nx - 1 ; i++ )
	{      
		u[i] = (1 - 2.0*c)*u[i] + c*(u[i+1] + u[i-1]);
	}
}

//Funciones para el metodo Backward-Difference Method
void ParabollicPDE::bdm( double t , int nt , double (*ui)( double ) , double (*uf)( double ) , string archivo )
{
	//se definene estas funciones nuevamente por si se redefinio el vector u0 con la funcion setu0
	setnx( u0 );
	u = u0;

	//variables para facilitar el codigo
	double h = (xf-xi)/(nx-1);
	double k = t/(nt-1);
	double c = (alpha*alpha*k)/(h*h);

	//set vectores necesarios para la solucion
	setbdm( c );

	//si se utiliza un archivo ya aexistente se sobre escriben los resultados
	ofstream archivo_sal;
	archivo_sal.open( archivo.c_str() );

	//se aplican las condiciones de frontera ui(t) y uf(t) y se almacena la condicion inicial en el archivo
	u0[0] = ui( 0.0 );
	u0[nx-1] = uf( 0.0 );
	saveline( u0 , archivo );

	//ciclo para solucionar un paso temporal y almacenarlo en el vector u y para almacenar el vector u en el archivo
	for( int i = 0 ; i < nt ; i++ )
	{
		u[0] = ui( i*k );
		u[nx-1] = uf( i*k );

		stepbdm( t , nt );

		u[0] = ui( (i+1)*k );
		u[nx-1] = uf( (i+1)*k );

		saveline( u , archivo );
	}
}
//solucion del vector u para un paso temporal 
void ParabollicPDE::stepbdm( double t , int nt )
{
	double h = (xf-xi)/(nx-1);
	double k = t/(nt-1);
	double c = (alpha*alpha*k)/(h*h);

	w = u0;
	w[0] = u[0]/a[0];

	for( int i = 1 ; i < nx - 1 ; i++ )
	{      
		w[i] = (u[i] + c*w[i-1])/a[i];
	}

	u[nx-2] = w[nx-2];

	for( int i = nx - 2 ; i > 0 ; i-- )
	{      
		u[i] = w[i] - b[i]*u[i+1];
	}
}

//Funciones para el metodo Crank-Nicolson
void ParabollicPDE::cn( double t , int nt , double (*ui)( double ) , double (*uf)( double ) , string archivo )
{
	//se definene las variables nuevamente por si se redefinio el vector u0 con la funcion setu0
	setnx( u0 );
	u = u0;

	//variables para facilitar el codigo
	double h = (xf-xi)/(nx-1);
	double k = t/(nt-1);
	double c = (alpha*alpha*k)/(h*h);

	//set vectores necesarios para la solucion
	setcn( c );

	//si se utiliza un archivo ya aexistente se sobre escriben los resultados
	ofstream archivo_sal;
	archivo_sal.open( archivo.c_str() );

	//se aplican las condiciones de frontera ui(t) y uf(t) y se almacena la condicion inicial en el archivo
	u0[0] = ui( 0.0 );
	u0[nx-1] = uf( 0.0 );
	saveline( u0 , archivo );

	//ciclo para solucionar un paso temporal y almacenarlo en el vector u y para almacenar el vector u en el archivo
	for( int i = 0 ; i < nt ; i++ )
	{
		u[0] = ui( i*k );
		u[nx-1] = uf( i*k );

		stepcn( t , nt );

		u[0] = ui( (i+1)*k );
		u[nx-1] = uf( (i+1)*k );

		saveline( u , archivo );
	}
}
//solucion del vector u para un paso temporal 
void ParabollicPDE::stepcn( double t , int nt )
{
	double h = (xf-xi)/(nx-1);
	double k = t/(nt-1);
	double c = (alpha*alpha*k)/(h*h);

	w = u0;
	w[0] = (( 1 - c )*u[0] +  0.5*c*u[1])/a[0];

	for( int i = 1 ; i < nx - 1 ; i++ )
	{      
		w[i] = (( 1 - c )*u[i] +  0.5*c*( u[i+1] + u[i+1] + w[i-1] ))/a[0];
	}

	u[nx-2] = w[nx-2];

	for( int i = nx - 2 ; i > 0 ; i-- )
	{      
		u[i] = w[i] - b[i]*u[i+1];
	}
}

//Funcion para guardar el vector en un archivo de texto
void ParabollicPDE::saveline( vector<double> u , string archivo )
{
	ofstream archivo_sal;

	archivo_sal.open( archivo.c_str() , ios_base::app );

	//prueva de creacion del archivo
	if (archivo_sal.fail())
	{
		cout << "No se pudo crear el archivo de salida " << archivo << " no se abrio con exito\n";
		exit(1);
	}

	//almacenar cada resultado del vector u en el archivo
	for( int i = 0 ; i < nx - 1 ; i++ )
	{      
		archivo_sal << fixed << setprecision(6) << u.at(i) << "\t";
	}

	archivo_sal << fixed << setprecision(6) << u.at(nx - 1) << "\n";
}
