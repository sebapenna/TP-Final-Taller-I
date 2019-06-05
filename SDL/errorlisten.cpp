#include <iostream>
#include "errorlisten.h"

const char* ErrorListen::what() const noexcept{
	return "Error while listening\n";
}
