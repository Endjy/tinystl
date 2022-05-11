#include "../src/alloc.h"

namespace TinySTL{
    //init
    char *alloc::start_free = 0;
    char *alloc::end_free = 0;
    size_t alloc::heap_size = 0;

    alloc::obj *alloc::free_list[alloc::ENFreeLists::NFREELISTS] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    void *alloc::allocate(size_t bytes){
        // if larger than max bytes allowed, then use malloc directly
        if(bytes > EMaxBytes::MAXBYTES){
            return malloc(bytes);
        }

        size_t index = FREELIST_INDEX(bytes);
        obj *list = free_list[index];
        //still have space in free list
        if(list){
            free_list[index] = list -> next;
            return list;
        }
        // list does not have enough space, refill by the memory pool
        else{
            return refill(ROUND_UP(bytes));
        }   
    }

    void alloc::deallocate(void *ptr, size_t bytes){
        //if allocated by malloc, then just free it
        if(bytes > EMaxBytes::MAXBYTES){
            free(ptr);
        }
        else{
            size_t index = FREELIST_INDEX(bytes);
            obj *node = static_cast<obj *>(ptr);
            node->next = free_list[index];
            free_list[index] = node;
        }
    }

    void *alloc::reallocate(void *ptr, size_t old_sz, size_t new_sz){
        deallocate(ptr, old_sz);
        ptr = allocate(new_sz);

        return ptr;
    }

    //return a obj size of bytes, sometimes it all node to free lists
    //bytes are assumed adjusted 
    void *alloc::refill(size_t bytes){
        size_t nobjs = ENObjs::NOBJS; //20

        char *chunk = chunk_alloc(bytes, nobjs);
        obj **my_free_list = 0;
        obj *result = 0;
        obj *current_obj = 0, *next_obj = 0;
        
        //only 1 is allocated
        if(nobjs == 1){
            return chunk;
        }
        //more than 1
        else{
            my_free_list = free_list + FREELIST_INDEX(bytes);
            result = (obj *)(chunk);
            //find the currunt next
            *my_free_list = next_obj = (obj *)(chunk + bytes);
            //add rest space to free list
            for(int i = 1; ; ++i){
                current_obj = next_obj;
                next_obj = (obj*)((char *) next_obj + bytes);
                if(nobjs - 1 == i){
                    //reach the end
                    current_obj->next = 0;
                    break;
                }
                else{
                    current_obj->next = next_obj;
                }
            }
            return result;
        }
    }

    char *alloc::chunk_alloc(size_t bytes, size_t& nobjs){
        char *result = 0;
        size_t total_bytes = bytes * nobjs;
        size_t bytes_left = end_free - start_free;

        // have enough left
        if(bytes_left >= total_bytes){
            result = start_free;
            start_free = start_free + total_bytes;
            return result;
        }
        //memory left can not satisfy all the need
        // can give space for 1 or more than 1 blocks
        else if (bytes_left >= bytes){
            nobjs = bytes_left / bytes;
            total_bytes = nobjs * bytes;
            result = start_free;
            start_free += total_bytes;
            return result;
        }
        // memory left is smaller than 1 block
        else{
            //get 2times of total bytes
            size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
            //have some space left
            if(bytes_left > 0){
                obj **my_free_list = free_list + FREELIST_INDEX(bytes_left);
                ((obj *)start_free)->next = *my_free_list;
                *my_free_list = (obj *)start_free; 
            }
            start_free = (char *)malloc(bytes_to_get);
            //failed the malloc
            if(!start_free){
                obj **my_free_list = 0;
                obj *p = 0;
                //traverse to find any space
                for(int i = bytes; i <= EMaxBytes::MAXBYTES; i += EAlign::ALIGN){
                    my_free_list = free_list + FREELIST_INDEX(i);
                    p = *my_free_list;
                    if(p != 0){
                        *my_free_list = p -> next;
                        start_free = (char *)p;
                        end_free = start_free + 1;
                        return chunk_alloc(bytes, nobjs);
                    }
                }
                end_free = 0;
            }
            heap_size += bytes_to_get;
            end_free = start_free + bytes_to_get;
            return chunk_alloc(bytes,nobjs);
        }
    }


}