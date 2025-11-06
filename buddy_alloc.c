#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <syscall.h>
#include <sys/mman.h>
#define MIN_SIZE 6  // 2⁶ = 64 bytes -- metadados tem 32, logo não pode ser 32(size_t = 8, bool 8, mb 8)
#define MAX_SIZE 32 // 2³² = 4GB
#define NUM_OF_SIZES (MAX_SIZE - MIN_SIZE + 1)
#define HEAP_SIZE NUM_OF_SIZES 
typedef struct memory_block
{
    size_t size;
    bool is_free;
    memory_block *prev;
    memory_block *next;
} memory_block;
typedef struct memory_block memory_block;
static memory_block[NUM_OF_SIZES];

void *heap_initializer(size_t heap_size)
{
    void *start_of_heap = mmap(
        NULL, // quando NULL, o kernel vai escolher o endereço page aligned. alinhamento de memória e paging são conceitop
        heap_size,
        PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS,
        -1,
        0
    );
    return start_of_heap;
}

bool is_power_of_2(size_t number)
{
    return number && ((number & (number - 1)) == 0);
}
size_t round_up_to_power_of_2(size_t size)
{
    size_t i = 1;
    while (i < size)
    {
        i *= 2;
    }
    return i;
}

void *split(memory_block *block, size_t target)
{
    while (block->size >= target)
    {
    }
}
void *merge()
{
}
bool check_if_block_free(memory_block *block)
{
    return block->is_free;
}

void *my_buddy_malloc(size_t size)
{
    if (!is_power_of_2(size))
    {
        size = round_up_to_power_of_2(size);
    }
}
void *my_buddy_free()
{
}
void *my_buddy_realloc()
{
}
void *my_buddy_calloc()
{
}
void *gc_collect()
{
}

int main()
{
}