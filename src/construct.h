#ifndef _CONSTRUCT_H
#define _CONSTRUCT_H

#include <new>

#include "type_traits.h"

namespace TinySTL{
    template<class T1, class T2>
    inline void construct(T1 *ptr1, const T2& value){
        new(ptr1) T1(value);
    }

    template<class T>
    inline void destory(T *ptr){
        ptr->~T();
    }

    template<class ForwardIterator>
    inline void _destory(ForwardIterator first, ForwardIterator last, _true_type){}

    template<class ForwardIterator>
    inline void _destory(ForwardIterator first, ForwardIterator last, _false_type){
        for(; first != last; ++first)
            destory(&*first);
    }

    template<class ForwardIterator>
    inline void destory(ForwardIterator first, ForwardIterator last){
        typedef typename _type_traits<ForwardIterator>::is_POD_type is_POD_type;
        _destory(first, last, is_POD_type());
    }

}


#endif