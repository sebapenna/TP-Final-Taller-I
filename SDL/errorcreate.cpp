#include <iostream>
#include "errorcreate.h"

const char* ErrorCreate::what() const noexcept{
	return "Error while creating a socket\n";
}
