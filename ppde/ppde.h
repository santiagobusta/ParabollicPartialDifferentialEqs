// methods.h
// created: 5 11 2020
// last modified: 5 11 2020

namespace ppde{

  namespace methods{

    class ForwardDiff();
    class BackwardDiff();
    class CrankNicolson();

  }

  namespace metrics{

    double mse( double * , double *);
    double rmse( double * , double *);

  }

}
