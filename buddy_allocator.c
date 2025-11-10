#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/mman.h>
#define MIN_SIZE 6
#define MAX_SIZE 20
#define NUMBER_OF_SIZES (MAX_SIZE - MIN_SIZE + 1)

/*Globais e structs*/
typedef struct buddy_block
{
    size_t size;
    bool is_free;
    struct buddy_block *next;
    struct buddy_block *prev;
} buddy_block;
size_t heap_size = (1 << MAX_SIZE);
buddy_block *free_lists[NUMBER_OF_SIZES];

/*Funções auxiliares que serão utilizadas ao longo do código.*/
bool is_power_of_2(size_t size);
size_t round_up_to_power_of_2(size_t size);
int search_for_list_index(size_t size);
/*Funções principais do alocador
buddy_split é fundamental pro algoritmo de alocação e buddy_merge é fundamental pro algortimo de liberação.
*/
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
/*Implementação das funções auxiliares*/
bool is_power_of_2(size_t size)
{
    return ((size & (size - 1)) == 0); // exemplo de como funciona: 8 -> 1000. 7 -> 0111. 0111 & 1000 -> 0000 -> 0, logo, verdadeiro
}
size_t round_up_to_power_of_2(size_t size)
{
    int i = 1;
    while (i < size)
    {
        i *= 2;
    }
    return i;
}
int search_for_list_index(size_t size)
{
    while ()
}
/*Implementação das funções principais*/
void *heap_initialize()
{
    void *new_heap = (1 < MAX_SIZE);
}