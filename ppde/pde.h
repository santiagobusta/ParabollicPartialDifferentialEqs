// pde.h
// created: 5 11 2020
// last modified: 5 11 2020

namespace pde{
  
  namespace metrics{
    
    double mse( double * , double *);
    double rmse( double * , double *);
    int count( double * ); // returns length of array;
    bool equal_size( double * , double * );
    bool copy( double * , double * );
    
  };
  
  class ParabollicPDE{ // Dt( u ) - alpha2 * Dx2( u ) = 0
    
  public:
    
    ParabollicPDE( double * , double *, double alpha_in = 1.0 ); // receives ( dependent variable array )
    void setu( double * ); // set dependent variable ( must be of length N )
    void seth( double ); // set time step size
    void step( double h0 = 0. ); // make a step in time
    void bigstep( double t , double h0 = 0. ); // solve for a determined t from actual values of u
      
  private:
    
    int N = 1; // length of arrays
    double h = 1.0; // time step
    double alpha2; // equation parameter
    double* x; // independent variable array
    double* u; // dependent variable array
    bool err = true; // true if array lengths differ 
    
  };
  
}
