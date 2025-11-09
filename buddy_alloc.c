#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#define MIN_SIZE 6  // 2⁶ = 64 bytes -- metadados tem 32, logo não pode ser 32(size_t = 8, bool 8, mb 8)
#define MAX_SIZE 20 // 2²⁰ = 1MB
#define NUM_OF_SIZES (MAX_SIZE - MIN_SIZE + 1)
#define HEAP_SIZE NUM_OF_SIZES

typedef struct memory_block
{
    size_t size;
    bool is_free;
    struct memory_block *prev;
    struct memory_block *next;
} memory_block;
typedef struct memory_block memory_block;

bool is_power_of_2(size_t number);
bool check_if_block_free(memory_block *block);
size_t round_up_to_power_of_2(size_t size);
int search_for_list_index(size_t size);

void *buddy_split(memory_block *block, size_t target);
void *buddy_merge(memory_block *buddy);

void *my_buddy_malloc(size_t size);
void *my_buddy_calloc(size_t new_memory_blocks, size_t size);
void *my_buddy_realloc(void *ptr_of_mem_to_be_realloc, size_t size);
void *my_buddy_free(void *ptr);
void *heap_initializer();

memory_block *free_lists[NUM_OF_SIZES];
void *heap_start = NULL;
size_t heap_size = (1 << MAX_SIZE);

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
bool check_if_block_free(memory_block *block)
{
    return block->is_free;
}
int search_for_list_index(size_t size)
{
    size_t s = (1 << MIN_SIZE);
    int index = 0;
    while (s < size)
    {
        s <<= 1;
        index++;
    }
    return index;
}
void *buddy_split(memory_block *block, size_t target)
{
}
void *buddy_merge(memory_block *buddy)
{
    // xor pra encontrar o buddy do buddy somente quando ele estiver disponível
}

void *my_buddy_malloc(size_t size)
{
    if (heap_start == NULL)
    {
        heap_initializer();
    }
    if (!is_power_of_2(size))
    {
        size = round_up_to_power_of_2(size);
    }
    void *ptr = heap_initializer(size);
    int i = search_for_list_index(size);

}
void *my_buddy_calloc(size_t new_memory_blocks, size_t size)
{
}
void *my_buddy_realloc(void *ptr_of_mem_to_be_realloc, size_t size)
{
}
void *my_buddy_free(void *ptr)
{
    if (ptr == NULL)
    {
        perror("Erro - Não tem o que liberar");
        return;
    }
}
void *heap_initializer()
{
    if (heap_start != NULL)
        return;
    heap_start = mmap(
        NULL, // quando NULL, o kernel vai escolher o endereço page aligned
        HEAP_SIZE,
        PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS,
        -1,
        0);
    if (heap_start == MAP_FAILED)
    {
        perror("Erro ao alocar memória.");
        exit(1);
    }
    for (int i = 0; i < NUM_OF_SIZES; i++)
    {
        free_lists[i] == NULL;
    }

    memory_block *initial_block = (memory_block *)heap_start;
    initial_block->size = heap_size;
    initial_block->is_free = true;
    initial_block->prev = NULL;
    initial_block->next = NULL;

    free_lists[NUM_OF_SIZES - 1] = initial_block;

    return heap_start;
}
int main()
{
}
