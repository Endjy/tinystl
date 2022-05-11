#include "../src/allocator.h"
#include "../src/alloc.h"

#include <time.h>
#include <list>
#include <iostream>

enum { NUMBERS = 10000000 };

void alloc_test() {
    // test of list
    // test of push_back
    std::list<int> list1; // std 默认分配器
    std::list<int, TinySTL::allocator<int>> list2;
    //std::list<int, TinySTL::alloc<int>> list3;
    clock_t start = clock();
    // srand(time(NULL));
    for(size_t i = 0; i < NUMBERS; ++i)
        list1.push_back(1);
    clock_t end = clock();
    std::cout << "Time to insert " << NUMBERS
         << " numbers in list with STL alloctor: "
         << end - start << std::endl;
    start = clock();
    for(size_t i = 0; i < NUMBERS; ++i)
        list2.push_back(1);
    end = clock();
    std::cout << "Time to insert " << NUMBERS
         << " numbers in list with mystl alloctor: "
         << end - start << std::endl;
    /*
    start = clock();
    for(size_t i = 0; i < NUMBERS; ++i)
        list3.push_back(1);
    end = clock();
    std::cout << "Time to insert " << NUMBERS
         << " numbers in list with mystl SGI alloc: "
         << end - start << std::endl;
    */
}

int main(){
    alloc_test();
}