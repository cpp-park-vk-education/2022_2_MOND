// Copyright 2022 mora

#ifndef INTERFACEDB_HTALLOCATOR_H
#define INTERFACEDB_HTALLOCATOR_H
#include <iostream>
#include <new>

template<class Tp>
struct NAlloc {
    typedef Tp value_type;

    NAlloc() = default;

    template<class T>
    NAlloc(const NAlloc<T> &) {}

    Tp *allocate(std::size_t n) {
        n *= sizeof(Tp);
        Tp *p = static_cast<Tp *>(::operator new(n));
        return p;
    }

    void deallocate(Tp *p, std::size_t n) {
        ::operator delete(p);
    }
};

template<class T, class U>
bool operator==(const NAlloc<T> &, const NAlloc<U> &) { return true; }

template<class T, class U>
bool operator!=(const NAlloc<T> &, const NAlloc<U> &) { return false; }
#endif //INTERFACEDB_HTALLOCATOR_H
