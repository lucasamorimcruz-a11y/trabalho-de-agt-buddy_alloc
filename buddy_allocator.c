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
void *buddy_split(size_t size, int index);
void *buddy_merge(void *ptr);
void *buddy_alloc(size_t size);
void *buddy_calloc(size_t number_of_elements, size_t size);
void *buddy_realloc(void *ptr, size_t size);
void *buddy_free(void *ptr);

/*Testes do código*/
int main()
{
    int *ptr = buddy_alloc(sizeof(int));
    *ptr = 10;
    printf("%i", *ptr);
    int *second_ptr = (int *)buddy_calloc(5, sizeof(int));
    for (int *i = second_ptr; i < second_ptr + 4; i++)
    {
        printf("%i", *i);
    }
    for (int i = 0; i < 4; i++)
    {
        second_ptr[i] += 10;
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
    while (i < NUMBER_OF_SIZES - 1 && ((1 << (MIN_SIZE + i)) < size))
    {
        i++;
    }
    return i;
}
void *find_free_block()
{
}
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
    for (int i = 0; i < NUMBER_OF_SIZES; i++)
    {
        free_lists[i] = NULL;
    }
    buddy_block *initial_block = (buddy_block *)heap_start;
    initial_block->size = heap_size;
    initial_block->is_free = true;
    initial_block->next = NULL;
    initial_block->prev = NULL;
    free_lists[NUMBER_OF_SIZES - 1] = initial_block;
    return initial_block;
}

// tenho que transformar isso em recursão -> oque tenho que fazer?
/*fazer a função split com o index, e se o size de new_block da free_list[i] não for igual size, eu recursivamente divido o bloco e chamo a função split(size, index-1).*/
void *buddy_split(size_t size, int index, int count) // passo max_size como index e count como 0
{
    if (size == 0)
    {
        return NULL;
    }
    if (index < 0)
    {
        perror("Não é possível alocar memória");
        return NULL;
    }
    buddy_block *initial_block = free_lists[index];
    free_lists[index] = initial_block->next;

    if (initial_block->size == size)
    {
        return initial_block;
    }
    size_t half_of_the_size = size / 2;
    buddy_block *buddy = free_lists[index - 1];
    return buddy_split(size, index - 1, count + 1);
}

void *buddy_merge(void *ptr)
{
    if (ptr == NULL)
    {
        perror("Erro ao localizar o bloco de memória");
        return;
    }
    buddy_block *buddy = buddy_adress_calculation();
    if (!buddy->is_free)
    {
        perror("Não é possível mergir.");
        return 1;
    }

    return;
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
    int index = search_for_list_index(size);
    buddy_block *new_block;
    if (new_block->size == *)
    {
        buddy_block *=
    }
}
void *buddy_calloc(size_t number_of_elements, size_t size)
{
    if (number_of_elements == 0)
    {
        return NULL;
    }
    if (!is_power_of_2(size))
    {
        size = round_up_to_power_of_2(size);
    }
    search_for_list_index(size);
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
    if (ptr_to_location == NULL)
    {
        return NULL;
    }
    memmove(ptr_to_location, ptr, size);
}
void *buddy_free(void *ptr)
{
    return buddy_merge(ptr);
}
