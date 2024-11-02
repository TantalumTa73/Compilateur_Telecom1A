#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

inline int verbose ;
inline string file_name;

#define v_cout if (verbose>=1) cout
#define vv_cout if (verbose>=2) cout

#define ERROR(msg) throw std::invalid_argument( msg )

#define SIZE_INT 8
#define SIZE_CHAR 1
#define SIZE_PTR 1

#define COMMENT "#"
#define GLOBAL "__root__"
#define MAIN "main"

#define PRINT_INT "print_int"
#define PRINT_CHAR "print_char"
#define PRINTF "printf"
#define SCAN_INT "scan_int"

#define TEMPLATE "FinalProjectCpp/template.s"