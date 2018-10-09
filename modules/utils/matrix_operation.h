// Copyright 2016 Arnaud Becheler    <Arnaud.Becheler@egce.cnrs-gif.fr>

/***********************************************************************                                                                         *
* This program is free software; you can redistribute it and/or modify *
* it under the terms of the GNU General Public License as published by *
* the Free Software Foundation; either version 2 of the License, or    *
* (at your option) any later version.                                  *
*                                                                      *
***************************************************************************/

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/banded.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <algorithm>

namespace quetzal {

namespace utils {

template<typename matrix_type>
matrix_type divide_terms_by_row_sum(matrix_type const& A) {
  using namespace boost::numeric::ublas;
  auto v = prod(scalar_vector<double>( A.size2(), 1.0), trans(A));
  vector<double> w ( v.size() );
  for(unsigned int i = 0; i < v.size(); ++i){
    double a = v (i);
    assert( a > 0);
    w(i) = 1.0 / a ;
  }
  banded_matrix<double> S( w.size(), w.size() );
  assert(S.size2() == A.size1());
  for(unsigned int i = 0; i < v.size(); ++i ){
    S(i,i) = w(i);
  }
  return prod(S, A);
}

}
}
