#include <iostream>

//enum EAlign{ ALIGN = 8 };

#define ALIGN 8

size_t ROUND_UP(size_t bytes){
    //std::cout << (bytes + EAlign::ALIGN ) << std::endl;
    //std::cout << ~(EAlign::ALIGN - 1) <<  " " << EAlign::ALIGN << std::endl;
    //return ((bytes + EAlign::ALIGN) & ~(EAlign::ALIGN - 1));
    return ((bytes + ALIGN) & ~(ALIGN - 1));
}


int main(){
    std::cout << ROUND_UP(31) << std::endl;
}