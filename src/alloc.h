#ifndef _ALLOC_H_
#define _ALLOC_H_

#include <cstdlib>

namespace TinySTL{

    //空间配置器 以字节为单位分配
    //内部使用
    class alloc{
    private:
        enum EAlign{ ALIGN = 8 }; //small block的上调边界
        enum EMaxBytes{ MAXBYTES = 128 }; // 小型区块的上限，超过直接用malloc分配
        enum ENFreeLists{ NFREELISTS = (EMaxBytes::MAXBYTES / EAlign::ALIGN)};//free lists 个数
        enum ENObjs{ NOBJS = 20 }; //，每次增加的节点数
    private:
        // free list node
        union obj{
            union obj *next;
            char data[1];
        };

        static obj *free_list[ENFreeLists::NFREELISTS];//free list
    private:
        //begin & end of memory pool
        static char *start_free;
        static char *end_free;
        //heap size
        static size_t heap_size;
    private:
        // see ../other/round_up.cpp
        // round up to a multiple of 8 
        static size_t ROUND_UP(size_t bytes){
            return ((bytes + EAlign::ALIGN - 1) & ~(EAlign::ALIGN - 1));
        }

        // choose the number of block, start from n;
        static size_t FREELIST_INDEX(size_t bytes){
            return ((bytes + EAlign::ALIGN - 1) / EAlign::ALIGN - 1);
        }

        //return a obj size of n, add block size of n to free list?
        static void *refill(size_t n);
        //alloc a chunk of memory capacity of nobjs number of blocks with size of size
        //if failed to allow that much, the number nobjs may be lowered
        static char *chunk_alloc(size_t size, size_t& nobjs);
    public:
        static void *allocate(size_t bytes);
        static void deallocate(void  *ptr, size_t bytes);
        static void *reallocate(void *ptr, size_t old_sz, size_t new_sz);
    };
}
#endif