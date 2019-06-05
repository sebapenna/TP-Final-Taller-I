#include <iostream>
#include "errorbind.h"

const char* ErrorBind::what() const noexcept{
	return "Error while binding \n";
}
