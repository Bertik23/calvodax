#pragma once

#include <memory>

template<typename T>
class default_ptr{
public:
    default_ptr();
    default_ptr(T* ptr);
    default_ptr(const default_ptr<T> &);
    default_ptr<T> & operator = (const default_ptr<T> &);
    ~default_ptr();
    T & operator * ();
    T & operator * () const;
    T * operator -> ();
    T * operator -> () const;
protected:
    T * ptr;
};

template<typename T>
default_ptr<T>::default_ptr(): ptr(new T) {};

template<typename T>
default_ptr<T>::default_ptr(T* ptr): ptr(ptr) {};

template<typename T>
default_ptr<T>::default_ptr(const default_ptr<T> & p): ptr(p->clone()) {}

template<typename T>
default_ptr<T> & default_ptr<T>::operator =(const default_ptr<T> & p){
    delete ptr;
    ptr = p->clone();
}

template<typename T>
T & default_ptr<T>::operator * (){
    return *ptr;
}

template<typename T>
T * default_ptr<T>::operator -> (){
    return ptr;
}

template<typename T>
T & default_ptr<T>::operator * () const{
    return *ptr;
}

template<typename T>
T * default_ptr<T>::operator -> () const{
    return ptr;
}

template<typename T>
default_ptr<T>::~default_ptr(){delete ptr;}