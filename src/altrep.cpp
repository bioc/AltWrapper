#include "Rcpp.h"
#include "R_ext/Altrep.h"
#include "altrep.h"
#include "tools.h"
#include "altrep_macro.h"
#include "altrep_tools.h"

using namespace Rcpp;





R_altrep_class_t get_altrep_class(SEXP class_type) {
	const char* class_type_char = CHAR(Rf_asChar(class_type));
	if (std::strcmp(class_type_char, "raw") == 0) {
		DEBUG(Rprintf("Altrep type is raw\n"));
		return altrep_raw_class;
	}
	if (std::strcmp(class_type_char, "logical") == 0) {
		DEBUG(Rprintf("Altrep type is logical\n"));
		return altrep_logical_class;
	}
	if (std::strcmp(class_type_char, "integer")==0) {
		DEBUG(Rprintf("Altrep type is integer\n"));
		return altrep_integer_class;
	}
	if (std::strcmp(class_type_char, "real") == 0) {
		DEBUG(Rprintf("Altrep type is real\n"));
		return altrep_real_class;
	}

	errorHandle("The class type is not available\n");
	return altrep_real_class;
}


R_altrep_class_t get_altrep_internal_class(SEXP class_type) {
	const char* class_type_char = CHAR(Rf_asChar(class_type));
	if (std::strcmp(class_type_char, "raw") == 0) {
		DEBUG(Rprintf("Altrep type is raw\n"));
		return altrep_internal_raw_class;
	}
	if (std::strcmp(class_type_char, "logical") == 0) {
		DEBUG(Rprintf("Altrep type is logical\n"));
		return altrep_internal_logical_class;
	}
	if (std::strcmp(class_type_char, "integer") == 0) {
		DEBUG(Rprintf("Altrep type is integer\n"));
		return altrep_internal_integer_class;
	}
	if (std::strcmp(class_type_char, "real") == 0) {
		DEBUG(Rprintf("Altrep type is real\n"));
		return altrep_internal_real_class;
	}

	errorHandle("The class type is not available\n");
	return altrep_internal_real_class;
}


int get_class_type_size(SEXP class_type) {
	const char* class_type_char = CHAR(Rf_asChar(class_type));
	if (std::strcmp(class_type_char, "raw") == 0) {
		return 1;
	}
	if (std::strcmp(class_type_char, "logical") == 0) {
		return 4;
	}
	if (std::strcmp(class_type_char, "integer") == 0) {
		return 4;
	}
	if (std::strcmp(class_type_char, "real") == 0) {
		return 8;
	}
	errorHandle("The class type is not available\n");
	return 0;
}

