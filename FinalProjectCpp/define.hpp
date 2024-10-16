#pragma once
#include <iostream>

using namespace std;

inline int verbose ;

#define v_cout if (verbose>=1) cout

#define ERROR(msg) throw std::invalid_argument( msg )

