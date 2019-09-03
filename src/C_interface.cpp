#include <Rcpp.h>
#include "altrep.h"
#include "tools.h"
#include <string>
using namespace Rcpp;






// [[Rcpp::export]]
bool C_ALTREP(SEXP x) {
	return ALTREP(x);
}
// [[Rcpp::export]]
SEXP C_get_alt_data1(SEXP x) {
	return R_altrep_data1(x);
}
// [[Rcpp::export]]
SEXP C_get_alt_data2(SEXP x) {
	return R_altrep_data2(x);
}
// [[Rcpp::export]]
void C_set_alt_data1(SEXP x,SEXP value) {
	R_set_altrep_data1(x, value);
}
// [[Rcpp::export]]
void C_set_alt_data2(SEXP x, SEXP value) {
	R_set_altrep_data2(x, value);
}



// [[Rcpp::export]]
SEXP C_duplicate_object(SEXP x, SEXP shallow) {
	if (as<bool>(shallow)) {
		return Rf_shallow_duplicate(x);
	}
	else {
		return Rf_duplicate(x);
	}
}


void C_attachAttr(SEXP x, SEXP R_tag, SEXP R_attr) {
	const char* tag = R_CHAR(Rf_asChar(R_tag));
	Rf_setAttrib(x, Rf_install(tag), R_attr);
}


// [[Rcpp::export]]
SEXP C_create_altrep(SEXP class_symbol_name, SEXP x,SEXP class_type,SEXP state, SEXP attrName, SEXP attributes) {
	R_altrep_class_t altrep_class = get_altrep_class(class_type);
	SEXP res = PROTECT(R_new_altrep(altrep_class, x, state));
	for (int i = 0; i < LENGTH(attrName); i++) {
		C_attachAttr(res, STRING_ELT(attrName, i), VECTOR_ELT(attributes, i));
	}
	UNPROTECT(1);
	//SET_NAMED(res, 0);
	return res;
}




static void ptr_finalizer(SEXP extPtr) {
	DEBUG(Rprintf("Finalizing data pointer\n"));
	void* ptr = R_ExternalPtrAddr(extPtr);
	free(ptr);
}
// [[Rcpp::export]]
SEXP C_create_internal_altrep(SEXP class_type, R_xlen_t length) {
	R_altrep_class_t altrep_internal_class = get_altrep_internal_class(class_type);
	void* ptr = malloc(get_class_type_size(class_type) * length);
	SEXP x = PROTECT(R_MakeExternalPtr(ptr,R_NilValue,R_NilValue));
	R_RegisterCFinalizer(x, ptr_finalizer);

	SEXP res=R_new_altrep(altrep_internal_class, x, wrap(length));

	UNPROTECT(1);
	return res;
}

// [[Rcpp::export]]
int C_getName(SEXP x) {
	return NAMED(x);
}
// [[Rcpp::export]]
SEXP C_duplicate(SEXP x, bool shallow) {
	if (shallow) {
		return Rf_shallow_duplicate(x);
	}
	else {
		return Rf_duplicate(x);
	}
}

// [[Rcpp::export]]
void C_initial_package(SEXP altrep_class_space,SEXP altrep_symbol_space) {
	ALTREP_REGISTRY_ENVIRONMENT = altrep_class_space;
	ALTREP_SYMBOL_LIST = altrep_symbol_space;
}






//
//// [[Rcpp::export]]
//SEXP C_performace_test1(SEXP a,R_xlen_t n) {
//	SEXP x;
//	for (int i = 0; i < n; i++) {
//		x=VECTOR_ELT(a, 10);
//	}
//	return x;
//}
//
//
//// [[Rcpp::export]]
//SEXP C_performace_test2(SEXP env, SEXP sym, R_xlen_t n) {
//	SEXP x;
//	for (int i = 0; i < n; i++) {
//		x = Rf_findVarInFrame(env, sym);
//	}
//	return x;
//}
//
//// [[Rcpp::export]]
//SEXP C_test1(SEXP f, SEXP x) {
//	SEXP call =PROTECT(Rf_lang2(f, x));
//	SEXP val = R_forceAndCall(call, 1, R_GlobalEnv);
//	UNPROTECT(1);
//	return val;
//}
//
//// [[Rcpp::export]]
//SEXP C_test2(SEXP expr, SEXP env) {
//	SEXP val = Rf_eval(expr, env);
//	return val;
//}
//
//// [[Rcpp::export]]
//SEXP C_test3(SEXP f,SEXP x) {
//	Function fun(f);
//	return fun(x);
//}
//// [[Rcpp::export]]
//void C_test4(SEXP x) {
//	SET_INTEGER_ELT(x,0,100);
//}
//// [[Rcpp::export]]
//void C_test5(SEXP x) {
//	ALTINTEGER_SET_ELT(x, 0, 100);
//}
//
//
//// [[Rcpp::export]]
//double C_test6(SEXP x) {
//	return REAL_ELT(x, 3);
//}
//
