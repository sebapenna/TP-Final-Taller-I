#ifndef ErrorBind_h
#define ErrorBind_h
#include <iostream>
#include <exception>

class ErrorBind : public std::exception{
	public:
	virtual const char* what() const noexcept override;
};
#endif
