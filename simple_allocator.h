//
// Created by Swagger on 2021/7/30.
//

#ifndef STLLEARN_SIMPLE_ALLOCATOR_H
#define STLLEARN_SIMPLE_ALLOCATOR_H

#include <new>          // for placement new
#include <cstddef>      // for ptrdiff_t size_t
#include <cstdlib>      // for exit()
#include <climits>      // for UINT_MAX
#include <iostream>     // for cerr


namespace MyAllocator{

template<typename T>
inline T* _allocate(ptrdiff_t size, T*){
    /* 申请空间 */
    T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
    if ( tmp == 0 ){
        std::cerr << "out of memory" << std::endl;
        exit(1);
    }
    return tmp;
}

template<typename T>
inline void _deallocate(T* buffer){
    ::operator delete(buffer);
}


template<typename T1, typename T2>
inline void _construct(T1* p, const T2& value){
    /* 在p的地址上生成T1，但是传进入了一个引用T2? */
    new(p) T1(value);
}

template<typename T>
inline void _destroy(T *p){
    p->~T();
}


template<typename T>
class allocator{
public:
    typedef T           value_type; // 数据类型
    typedef T*          pointer; // 数据类型指针
    typedef const T*    const_pointer; // 数据类型const指针
    typedef T&          reference; // 数据类型引用
    typedef const T&    const_reference; // 数据类型const引用
    typedef size_t      size_type; // 类型长度，总长度！
    typedef ptrdiff_t   difference_type; // ?


    /**
     * 申请内存
     **/
    pointer allocate(size_type n, const void* hint=0){
        return _allocate(n, (pointer)0);
    }


    /**
     * 释放内存
     **/
    void deallocate(pointer p, size_type n){
        _deallocate(p);
    }


    /**
     *  调用构造函数
     **/
    void construct(pointer p, const T& value){
        _construct(p, value);
    }


    /**
     *  析构函数
     **/
    void destroy(pointer p){
        _destroy(p);
    }

    pointer address(reference x){
        return (pointer)&x;
    }

    const_pointer const_address(const_reference x){
        return (const_pointer)&x;
    }

    size_type max_size() const {
        return size_type(UINT_MAX / sizeof(T));
    }

};

} // end of namespace MyAllocator







#endif //STLLEARN_SIMPLE_ALLOCATOR_H
