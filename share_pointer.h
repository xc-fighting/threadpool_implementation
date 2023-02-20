#ifndef _SHARE_PTR_
#define _SHARE_PTR_

#include <iostream>
#include <pthread.h>

template<class T>
class SharedPtr {
public:
	// constructor with template type pointer
	SharedPtr(T* ptr);
	// destructor
	~SharedPtr();
	// copy constructor with other pointer
	SharedPtr(const SharedPtr<T>& other);
    // define the operator
    SharedPtr<T>& operator=(const SharedPtr<T>& other);
    // define the * operator
    T& operator*();
    // define the -> operator
    T* operator->();
    // can also use the Get to fetch pointer
    T* Get();
    // get number of reference
    int UseCount();
private:
	void AddRefCount();
	void Release();

	T* ptr_
	pthread_mutex_t* mutex_;
	int* ref_count_;

};



#endif