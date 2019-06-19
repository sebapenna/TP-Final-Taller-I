#include <iostream>
#include "Thread.h"
#include "exceptions.h"

Thread::Thread() {}

Thread::~Thread() {
}

void Thread::start() {
	thread = std::thread(&Thread::runWithTry, this);
}

void Thread::join() {
	thread.join();
}

Thread::Thread(Thread&& other) {
	this->thread = std::move(other.thread);
}

Thread& Thread::operator=(Thread&& other) {
	this->thread = std::move(other.thread);
	return *this;
}

void Thread::runWithTry() {
    try {
        this->run();
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }  catch(...) {
        std::cout << UnknownException().what();
    }
}
