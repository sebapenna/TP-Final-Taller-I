#ifndef __COMMON_ERROR_CREATE_H
#define __COMMON_ERROR_CREATE_H
#include <iostream>
#include <exception>

class ErrorCreate : public std::exception{
public:
	virtual const char* what() const noexcept override;
};
#endif
