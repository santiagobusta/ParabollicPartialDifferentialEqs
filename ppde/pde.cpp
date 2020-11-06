// pde.cpp
// created: 5 11 2020
// last modified: 5 11 2020

#include"pde.h"
#include<iostream>

int pde::metrics::count( double* x ){

  return int( sizeof( x ) / sizeof( x [0] ) );

}

bool pde::metrics::equal_size( double* arr1 , double* arr2 ){

  int N1, N2;

  N1 = pde::metrics::count( arr1 );
  N2 = pde::metrics::count( arr2 );

  return (N1 == N2);

}

bool pde::metrics::copy( double* arr1 , double* arr2 ){ // must be of the same length

  bool err = not pde::metrics::equal_size( arr1 , arr2 );
  
  if( not err ){
    
    int N = pde::metrics::count( arr1 );
    
    for( int i = 0 ; i < N ; i++ ){
      
      arr1[i] = arr2[i];

      return not err;
      
    }
  }
  
  else{
    
    std::cout << "Los arreglos difieren en tamaño\n";
    return err;
    
  }
  
}

pde::ParabollicPDE::ParabollicPDE( double x0 , double u0 , double alpha0 ){

  int Nx , Nu ;
  
  alpha = alpha0; // sets ParabollicPDE parameter
  
  Nx = pde::count( x0 );
  Nu = pde::count( u0 );

  err = not pde::metrics::equal_size( x0 , u0 );
  
  if( not err ){

    pde::metrics::copy( x , x0 );
    pde::metrics::copy( u , u0 );
    
  }
  
}

void pde::ParabollicPDE::setu( double * new_u ){

  if( N == pde::metrics::count( new_u ) ){
    
    pde::metrics::copy( u , new_u );

  }

}

void pde::ParabollicPDE::seth( double h0 ){

  h = h0;
  
}

void pde::ParabollicPDE::step( double h0 ){

  // Si h0=0 usar h como stepsize
  // Si no, usar h0 como stepsize
  // Aqui iria el metodo
  
  2+2;
  
}

void pde::ParabollicPDE::bigstep( double t , double h0){

  // Si h0=0 usar h como stepsize
  // Si no, usar h0 como stepsize
  
  int n = int( t / h );

  for( int i = 0 ; i < n ; i++ ){
    
    pde::ParabollicPDE::step( h0 );

  }

}
