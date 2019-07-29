//This file is for ALTREP internal use.
#include <Rcpp.h>
#include "R_ext/Altrep.h"
using namespace Rcpp;
//Dispacher altrep class
extern R_altrep_class_t altrep_raw_class;
extern R_altrep_class_t altrep_logical_class;
extern R_altrep_class_t altrep_integer_class;
extern R_altrep_class_t altrep_real_class;
//Internal altrep class
//A wrapper for the pointer type
extern R_altrep_class_t altrep_internal_raw_class;
extern R_altrep_class_t altrep_internal_logical_class;
extern R_altrep_class_t altrep_internal_integer_class;
extern R_altrep_class_t altrep_internal_real_class;

//Call a function with arguments
SEXP make_call(SEXP fun);
SEXP make_call(SEXP fun,SEXP x1);
SEXP make_call(SEXP fun, SEXP x1, SEXP x2);
SEXP make_call(SEXP fun, SEXP x1, SEXP x2, SEXP x3);
SEXP make_call(SEXP fun, SEXP x1, SEXP x2, SEXP x3, SEXP x4);
SEXP make_call(SEXP fun, SEXP x1, SEXP x2, SEXP x3, SEXP x4, SEXP x5);


/*
Get the symbol:
inspect,
length,
dataptr,dataptrOrNull,
get_element,subset,
duplicate,coerce,
serialize,unserialize,
region,

class_type
*/
SEXP get_alt_symbol(const char* name);
