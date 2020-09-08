#include "Constants.hpp"

void ERROR_CONDITION(bool err_bool, std::string* err_str, bool* boolToChange, std::string* strToChange) {
	if (err_bool) {
		strToChange = err_str;
		*boolToChange = true;
	}
}
