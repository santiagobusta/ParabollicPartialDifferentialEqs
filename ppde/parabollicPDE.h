#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// ecuaciones diferenciales parciales de la forma Dt(u) - alpha^2 * Dx2(u) = 0
class ParabollicPDE
{    
	public:

	//contructor
	ParabollicPDE( vector<double> , double , double , double );

	// funciones set
	void setalpha( double );
	void setxi( double );
	void setxf( double );
	void setu0( vector<double> );

	// funciones get
	vector<double> getx();

	// funciones metodo Forward Difference Method
	void fdm( double , int , double (*)( double ) , double (*)( double ) , string );

	// funciones metodo Backward-Difference Method
	void bdm( double , int , double (*)( double ) , double (*)( double ) , string );

	// funciones metodo Crank-Nicolson
	void cn( double , int , double (*)( double ) , double (*)( double ) , string );
      
	private:

	// parametros
	double alpha = 1.0;
	double xi = 0.0;
	double xf = 1.0;
	int nx = 1;
	vector<double> x;
	vector<double> u;
	vector<double> u0;
	vector<double> w;
	vector<double> a;
	vector<double> b;

	// funciones set privadas
	void setx();
	void setbdm( double );
	void setcn( double );
	void setnx( vector<double> );

	// funciones privadas metodo Forward Difference Method
	void stepfdm( double , int );

	// funciones privadas metodo Backward-Difference Method
	void stepbdm( double , int );

	// funciones privadas metodo Crank-Nicolson
	void stepcn( double , int );

	// funciones provadas generales
	void saveline( vector<double> , string );    
};
 

