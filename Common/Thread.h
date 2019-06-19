#ifndef THREAD_H
#define THREAD_H

#include <thread>

class Thread {
private:
    void runWithTry();
public:
	Thread();

	// Starts a thread and binds it to the function defined by
	// run
	void start();
	
	// Let the thread finish the task.
	void join();
	
	// This is the method that needs to be overrided to allow 
	// the thread to bind to it.
	virtual void run() = 0;
	
	// We need to use this so we use inherance
	virtual ~Thread();
	
	// We wont allow copy constructor
	Thread(const Thread&) = delete;
	
	// We wont allow assignation constructor
	Thread& operator=(const Thread&) = delete;
	
	// But we will allow move semantics
	Thread(Thread&& other);	
	Thread& operator=(Thread&& other);
	
private:
	std::thread thread;
};

#endif
