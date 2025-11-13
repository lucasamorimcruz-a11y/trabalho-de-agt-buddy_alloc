#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/mman.h>
#define MIN_SIZE 5
#define MAX_SIZE 20
#define NUMBER_OF_LEVELS (MAX_SIZE - MIN_SIZE + 1)

typedef struct buddy_block
{
    short int level;
    bool is_free;
    struct buddy_block *next;
    struct buddy_block *prev;
} buddy_block;
size_t heap_size = (1 << MAX_SIZE);
buddy_block *free_lists[NUMBER_OF_LEVELS];
void *heap_start = NULL;

short int size_to_level(size_t size);
void *find_buddy(buddy_block *block);
void *find_first_block(buddy_block *block);
void *skip_header(buddy_block *block);
void *get_header_again(void *ptr);
void *buddy_split(buddy_block *block);
void *buddy_merge(buddy_block *block);
void *insert_into_list(buddy_block *block);
void *remove_from_the_list(buddy_block *block);

void *heap_initialize();
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
short int size_to_level(size_t size)
{
    int level = 0;
    while (level < NUMBER_OF_LEVELS - 1 && ((1 << (MIN_SIZE + level)) < size + sizeof(buddy_block)))
    {
        level++;
    }
    return level;
}
void *find_buddy(buddy_block *block)
{
    long long x = 1 << (block->level + MIN_SIZE);
    return (buddy_block *)((long long)block ^ x);
}
void *find_first_block(buddy_block *block)
{
    buddy_block *buddy = find_buddy(block);
    if (block < buddy)
    {
        return block;
    }
    else
    {
        return buddy;
    }
}
void *skip_header(buddy_block *block)
{
    return (void *)(block + 1);
}
void *get_header_again(void *ptr)
{
    return ((buddy_block *)ptr - 1);
}
void *buddy_split(buddy_block *block)
{
    int x = 1 << ((block->level - 1) + MIN_SIZE);
    return (buddy_block *)((long long)block | x);
}
void *buddy_merge(buddy_block *block)
{
}
void *insert_into_list(buddy_block *block)
{
}
void *remove_from_the_list(buddy_block *block)
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
        NULL;
    }
    for (int i = 0; i < NUMBER_OF_LEVELS; i++)
    {
        free_lists[i] = NULL;
    }
    buddy_block *initial_block = (buddy_block *)heap_start;
    initial_block->level = NUMBER_OF_LEVELS - 1;
    initial_block->is_free = true;
    initial_block->next = NULL;
    initial_block->prev = NULL;
    free_lists[NUMBER_OF_LEVELS - 1] = initial_block;
    return initial_block;
}
void *buddy_alloc(size_t size)
{
    if (size == 0)
    {
        return NULL;
    }
    if (heap_start == NULL)
    {
        heap_initialize();
    }
    int level = size_to_level(size);

    buddy_block *block = NULL;
    for (int i = 0; i < NUMBER_OF_LEVELS; i++)
    {
        if (free_lists[i] != NULL)
        {
            block = free_lists[i];
            remove_from_the_list(block);
            while (block->level > level)
            {
                buddy_block *buddy = buddy_split(block);
                block->level -= 1;

                buddy->level = level;
                buddy->is_free = true;
                buddy->next = NULL;
                buddy->prev = NULL;
                insert_into_list(buddy);
            }
            block->is_free = false;
            return skip_header(block);
        }
    }
}
void *buddy_calloc(size_t number_of_elements, size_t size)
{
}
void *buddy_realloc(void *ptr, size_t size)
{
}
void *buddy_free(void *ptr)
{
}
