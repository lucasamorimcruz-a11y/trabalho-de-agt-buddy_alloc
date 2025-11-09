#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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

bool is_power_of_2(size_t number);
size_t round_up_to_power_of_2(size_t size);
int search_for_list_index(size_t size, memory_block *block);
void *buddy_split(memory_block *block, size_t target);
void *buddy_merge(memory_block *buddy);
bool check_if_block_free(memory_block *block);
void *my_buddy_malloc(size_t size);
void *my_buddy_realloc(void *ptr_of_mem_to_be_realloc, size_t size);
void *my_buddy_calloc(size_t new_memory_blocks, size_t size);
void *my_buddy_free(memory_block *buddy_to_be_freed);
void *heap_initializer(size_t heap_size);

memory_block *free_lists[NUM_OF_SIZES];

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
int search_for_list_index(size_t size, memory_block *block)
{
    for (int i = 0; i < NUM_OF_SIZES; i++)
    {
        if (size == free_lists[i]->size)
        {
            return i;
        }
    }
    printf("Não foi possível encontrar espaço para o processo");
    return -1;
}
void *buddy_split(memory_block *block, size_t target)
{
    while (block->size >= target)
    {
        memory_block *buddy_block = (memory_block *)(char *)target + block->size;
        split(buddy_block, target);
    }
}
void *buddy_merge(memory_block *buddy)
{
    // xor pra encontrar o buddy do buddy somente quando ele estiver disponível
    if (buddy->is_free == true &&)
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
    int i = search_for_list_index(size);
}
void *my_buddy_realloc(void *ptr_of_mem_to_be_realloc, size_t size)
{
}
void *my_buddy_calloc(size_t new_memory_blocks, size_t size)
{
}
void *my_buddy_free(memory_block *buddy_to_be_freed)
{
    if (is_buddy_free())
    {
        buddy_merge();
    }
}
void *heap_initializer(size_t heap_size)
{
    void *start_of_heap = mmap(
        NULL, // quando NULL, o kernel vai escolher o endereço page aligned. alinhamento de memória e paging são conceitop
        heap_size,
        PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS,
        -1,
        0);
    return start_of_heap;
}
int main()
{
}
