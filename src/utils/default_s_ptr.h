#include <utility>

#include "../typedefs.h"

template<typename T, typename R=T>
class default_s_ptr{
public:
    default_s_ptr(): ptr(new R){};
    default_s_ptr(T * in): ptr(in){
        //ptr = in;
    }
    default_s_ptr(const T & in): ptr(new T(in)) {}
    default_s_ptr(T && in): ptr(new T(move(in))) {}
    default_s_ptr(const default_s_ptr<T> & other){
        --*refs;
        if (!*refs){
            delete ptr;
            delete refs;
        }
        ptr = other.ptr;
        refs = other.refs;
        ++*refs;
    }
    default_s_ptr & operator = (const default_s_ptr<T> & other){
        auto tmp = other;
        std::swap(ptr, tmp.ptr);
        std::swap(refs, tmp.refs);
        return *this;
    }
    default_s_ptr (default_s_ptr<T> && other){
        std::swap(ptr, other.ptr);
        std::swap(refs, other.refs);
    }
    default_s_ptr & operator = (default_s_ptr<T> && other){
        std::swap(ptr, other.ptr);
        std::swap(refs, other.refs);
        return *this;
    }
    ~default_s_ptr(){
        --(*refs);
        if (!*refs){
            delete ptr;
            delete refs;
        }
    }
    T & operator * () const{
        return *ptr;
    }
    T * operator -> () const{
        return ptr;
    }
    bool operator == (const default_s_ptr<T> & other) const {
        return **this == *other;
    }
    bool operator < (const default_s_ptr<T> & other) const {
        return **this < *other;
    }
    usize get_refs(){
        return *refs;
    }
    T * get_ptr(){
        return ptr;
    }
    default_s_ptr copy(){
        T * out = new T(*ptr);
        return out;
    }
private:
    T * ptr = new T();
    usize * refs = new usize(1);
};