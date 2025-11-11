#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/mman.h>
#define MIN_SIZE 6
#define MAX_SIZE 20
#define NUMBER_OF_SIZES (MAX_SIZE - MIN_SIZE + 1)

typedef struct buddy_block
{
    size_t size;
    bool is_free;
    struct buddy_block *next;
    struct buddy_block *prev;
} buddy_block;
size_t heap_size = (1 << MAX_SIZE);
buddy_block *free_lists[NUMBER_OF_SIZES];
void *heap_start = NULL;

bool is_power_of_2(size_t size);
size_t round_up_to_power_of_2(size_t size);
int search_for_list_index(size_t size);
void *buddy_adress_calculation(void *ptr, int k);

void *heap_initialize();
void *buddy_split(size_t size);
void *buddy_merge(void *ptr);
void *buddy_alloc(size_t size);
void *buddy_calloc(size_t number_of_elements, size_t size);
void *buddy_realloc(void *ptr, size_t size);
void *buddy_free(void *ptr);

/*Testes do código*/
int main()
{
    int *ptr = (int *)buddy_alloc(sizeof(int));
    *ptr = 10;
    printf("%i", *ptr);
    int *second_ptr = (int *)buddy_calloc(5, sizeof(int));
    for (int *i = second_ptr; i < second_ptr + 4; i++)
    {
        printf("%i", *i);
    }
    for (int i = 0; i < 4; i++)
    {
        second_ptr[i] = i + 10;
        printf("%i", second_ptr[i]);
    }
    buddy_realloc((int *)ptr, 3);
    buddy_free(ptr);
    buddy_free(second_ptr);
}
bool is_power_of_2(size_t size)
{
    return ((size & (size - 1)) == 0);
}
size_t round_up_to_power_of_2(size_t size)
{
    int i = 1;
    while (i < size)
    {
        i <<= 1;
    }
    return i;
}
int search_for_list_index(size_t size)
{
    int i = 0;
    while (i < NUMBER_OF_SIZES && ((1 << (MIN_SIZE + 1)) < size))
    {
        i++;
    }
    return i;
}
void *find_free_block();
void *heap_initialize()
{
    heap_start = mmap(
        NULL,
        heap_size,
        PROT_READ | PROT_WRITE,
        MAP_ANONYMOUS | MAP_PRIVATE,
        -1,
        0);
    if (heap_start == MAP_FAILED)
    {
        perror("Erro ao inicializar a heap (Sem memória suficiente).");
        return;
    }
    for (int i = 0; i < MAX_SIZE; i++)
    {
        free_lists[i] = NULL;
    }
    buddy_block *initial_block = buddy_block*heap_start;
    initial_block->size = heap_size;
    initial_block->is_free = true;
    initial_block->next = NULL;
    initial_block->prev = NULL;
    free_lists[search_for_list_index(heap_size)] = initial_block;

}
void *buddy_split(size_t size)
{
    int i = search_for_list_index(size);
    if (free_lists[i] != NULL)
    {
        buddy_block *new_block = free_lists[i];
        free_lists[i] = new_block->next;
        new_block->is_free = false;
    }
    
}
void *buddy_merge(void *ptr)
{
    if (ptr == NULL)
    {
        return;
    }
    
}
void *buddy_alloc(size_t size)
{
    if (heap_start == NULL)
    {
        heap_initialize();
    }
    if (!is_power_of_2(size))
    {
        size = round_up_to_power_of_2(size);
    }
    buddy_block *new_block;
    if (new_block->size)
    {
        buddy_block *=
    }
}
void *buddy_calloc(size_t number_of_elements, size_t size)
{
}
void *buddy_realloc(void *ptr, size_t size)
{
    if (ptr == NULL)
    {
        return buddy_alloc(size);
    }
    if (size == 0)
    {
        buddy_free(ptr);
        return NULL;
    }
    if (!is_power_of_2(size))
    {
        size = round_up_to_power_of_2(size);
    }
    void *ptr_to_location = buddy_alloc(size);
    memmove(ptr_to_location, ptr, 0 /*arrumar */);
}
void *buddy_free(void *ptr)
{
    buddy_merge(ptr);
}
