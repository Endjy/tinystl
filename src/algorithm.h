#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

//memset
#include <cstring>

#include "allocator.h"
//#include "Functional.h"
#include "iterator.h"
#include "type_traits.h"
#include "utility.h"

namespace TinySTL{
    template<class ForwardIterator, class T>
    void fill(ForwardIterator first, ForwardIterator last, const T& value){
        for(; first != last, ++first)
            *first = value;
    }

    inline void fill(char *first, char *last, const char& value)
	{
		memset(first, static_cast<unsigned char>(value), last - first);
	}

    inline void fill(wchar_t *first, wchar_t *last, const wchar_t& value)
	{
		memset(first, static_cast<unsigned char>(value), (last - first) * sizeof(wchar_t));
	}
    //fill n
    //O(n)
    template<class OutputIterator, class Size, class T>
	OutputIterator fill_n(OutputIterator first, Size n, const T& value)
	{
		for (; n > 0; --n, ++first)
			*first = value;
		return first;
	}

    template<class Size>
	char *fill_n(char *first, Size n, const char& value)
	{
		memset(first, static_cast<unsigned char>(value), n);
		return first + n;
	}

    template<class Size>
	wchar_t *fill_n(wchar_t *first, Size n, const wchar_t& value)
	{
		memset(first, static_cast<unsigned char>(value), n * sizeof(wchar_t));
		return first + n;
	}
}

#endif