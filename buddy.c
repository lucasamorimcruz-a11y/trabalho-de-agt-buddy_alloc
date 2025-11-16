#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#define MIN_SIZE 5
#define MAX_SIZE 20
#define NUMBER_OF_LEVELS (MAX_SIZE - MIN_SIZE)
typedef struct buddy_block
{
    short int level;
    bool is_free;
    struct buddy_block *next;
    struct buddy_block *prev;
} buddy_block;

size_t heap_size = 1 << MAX_SIZE;
void *heap_start = NULL;
buddy_block *free_lists[NUMBER_OF_LEVELS];

void remove_from_list(buddy_block *block)
{
    int level = block->level;
    if (block->prev)
    {
        block->prev->next = block->next;
    }
    else
    {
        free_lists[level] = block->next;
    }
    if (block->next)
    {
        block->next->prev = block->prev;
    }
    block->next = NULL;
    block->prev = NULL;
}
void insert_into_list(buddy_block *block)
{
    int level = block->level;
    block->next = free_lists[level];
    block->prev = NULL;
    if (free_lists[level])
    {
        free_lists[level]->prev = block;
    }
    free_lists[level] = block;
}

short int size_to_level(size_t size)
{
    int level = 0;
    while ((1 << (level + MIN_SIZE)) <= (size + sizeof(buddy_block)) && level < NUMBER_OF_LEVELS)
    {
        level++;
    }
    if (level > NUMBER_OF_LEVELS)
    {
        return -1;
    }
    return level;
}
void *find_buddy(buddy_block *block)
{
    long long x = (1 << (block->level + MIN_SIZE));
    return (buddy_block *)((long long)block ^ x);
}
void *find_first_block(buddy_block *block)
{
    buddy_block *buddy = find_buddy(block);
    if (block > buddy)
    {
        return buddy;
    }
    return block;
}
void *skip_header(buddy_block *block)
{
    return (void *)(block + 1);
}
void *get_header(void *ptr)
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
    block->is_free = true;
    while (block->level < NUMBER_OF_LEVELS - 1)
    {
        buddy_block *buddy = find_buddy(block);
        if (block->level != buddy->level || !buddy->is_free)
        {
            break;
        }
        remove_from_list(buddy);
        block = find_first_block(block);
        block->level++;
    }
    insert_into_list(block);
    return block;
}

void heap_intialize()
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
        fprintf(stderr, "Erro na alocação");
        return;
    }
    for (int i = 0; i < NUMBER_OF_LEVELS; i++)
    {
        free_lists[i] = NULL;
    }
    buddy_block *first_block = (buddy_block *)heap_start;
    first_block->level = NUMBER_OF_LEVELS - 1;
    first_block->is_free = true;
    first_block->next = NULL;
    first_block->prev = NULL;
    free_lists[NUMBER_OF_LEVELS - 1] = first_block;
}
void *buddy_alloc(size_t size)
{
    if (heap_start == NULL)
    {
        heap_intialize();
    }
    if (size == 0)
    {
        return NULL;
    }
    int level = size_to_level(size);
    for (int i = level; i < NUMBER_OF_LEVELS; i++)
    {
        if (free_lists[i] != NULL)
        {
            buddy_block *block = free_lists[i];
            remove_from_list(block);
            while (block->level > level)
            {
                buddy_block *buddy = buddy_split(block);
                block->level--;
                buddy->level = block->level;
                buddy->is_free = true;
                buddy->next = NULL;
                buddy->prev = NULL;
                insert_into_list(buddy);
            }
            block->is_free = false;
            return skip_header(block);
        }
    }
    return NULL;
}
void buddy_free(void *ptr)
{
    if (ptr == NULL)
    {
        fprintf(stderr, "Erro na alocação");
        return;
    }
    buddy_block *block = get_header(ptr);
    buddy_merge(block);
}
int main()
{
    int *ptr = buddy_alloc(100);
    if (ptr == NULL)
    {
        fprintf(stderr, "Erro na alocação");
        return 1;
    }
    for (int i = 0; i < (100 / sizeof(int)); i++)
    {
        ptr[i] = 10 + i;
        printf("%i", ptr[i]);
    }
    buddy_free(ptr);
}