#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <syscall.h>
#include <sys/mman.h>
#define HEAP_MAX_SIZE

typedef struct memory_block
{
    size_t size;
    bool is_free;
    memory_block *prev;
    memory_block *next;
} memory_block;

void *heap_initializer(size_t heap_size)
{
    void *start_of_heap = mmap(
        NULL, // quando NULL, o kernel vai escolher o endereço page aligned. alinhamento de memória e paging são conceitop
        heap_size,

    );
    void *result = start_of_heap + heap_size;
}

bool is_power_of_2(size_t number)
{
    return (number & (number - 1) == 0);
}
size_t round_up_to_power_of_2(size_t size)
{
    size_t i = 0;
    while (i < size)
    {
        i *= 2;
    }
    return i;
}
void *split()
{
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