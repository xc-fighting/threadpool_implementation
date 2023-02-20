#include "share_pointer.h"

/*template<class T>
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

}; */

template<class T>
SharedPtr<T>::SharedPtr(T* ptr) {
	this->ptr_ = ptr;
	this->ref_count_ = new int(1);
	this->mutex_ = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(this->mutex_, NULL);
}

template<class T>
SharedPtr<T>::~SharedPtr() {
	
}

template<class T>
T& SharedPtr<T>::operator=(const SharedPtr<T>& other) {

}

template<class T>
T* SharedPtr<T>::Get() {
	return this->ptr_;
}

template<class T>
T* SharedPtr<T>::operator->() {
	return this->ptr_;
}

template<class T>
T& SharedPtr<T>::operator*() {
	return *(this->ptr_);
}
