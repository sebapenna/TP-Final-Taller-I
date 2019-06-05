#ifndef ErrorListen_h
#define ErrorListen_h
#include <iostream>
#include <exception>

class ErrorListen : public std::exception{
	public:
	virtual const char* what() const  noexcept override;
};
#endif
