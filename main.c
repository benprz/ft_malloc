#define _GNU_SOURCE
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

#include "libft.h"

struct s_zone
{
	struct s_block *block;
	size_t used_bytes;
	// struct s_zone *next;
};

struct s_allocations
{
	bool is_struct_init;
	struct s_zone *small_zone;
	struct s_zone *medium_zone;
	size_t page_size;
	size_t word_size;
	size_t small_zone_size;
	size_t medium_zone_size;
	size_t small_alloc_size;
	size_t medium_alloc_size;
};

struct s_allocations g_allocations;

struct s_block
{
	void *begin;
	void *end; // (begin + size)
	struct s_block *next;
};

struct s_block *get_block(void *ptr) {
	struct s_block *block;
	if (ptr >= g_allocations.small_zone + sizeof(struct s_zone) && ptr <= g_allocations.small_zone + sizeof(struct s_zone) + small_zone_size) {
		while (block != NULL) {
			if (block->begin == ptr) {
				return block;
			}
			block = block->next;
		}
	}
	else if (ptr >= g_medium_zone + sizeof(struct s_zone) && ptr <= g_medium_zone + sizeof(struct s_zone) + medium_zone_size) {
		while (block != NULL) {
			if (block->begin == ptr) {
				return block;
			}
			block = block->next;
		}
	}
	return NULL;
}

struct s_block *get_last_block() {
	struct s_block *block = g_root;
	while (block->next != NULL) {
		block = block->next;
	}
	return block;
}

void init_malloc() {
	g_allocations.is_struct_init = true;
	g_allocations.small_zone = NULL;
	g_allocations.medium_zone = NULL;
	g_allocations.page_size = getpagesize();
	g_allocations.word_size = sizeof(void*);
	g_allocations.small_zone_size = limit.rlim_cur / 100;
	g_allocations.medium_zone_size = limit.rlim_cur / 100 * 10;
	g_allocations.small_alloc_size = g_allocations.small_zone_size / 100;
	g_allocations.medium_alloc_size = g_allocations.medium_zone_size / 100;
}

void *ft_malloc(size_t size)
{
	if (!g_allocations.is_struct_init) {
		init_malloc();
	}
	//print data
	printf("page_size: %zu\n", page_size);
	printf("word_size: %zu\n", word_size);
	printf("small_zone_size: %zu\n", small_zone_size);
	printf("medium_zone_size: %zu\n", medium_zone_size);
	printf("small_alloc_size: %zu\n", small_alloc_size);
	printf("medium_alloc_size: %zu\n", medium_alloc_size);

	if (size <= small_alloc_size)
	{
		if (g_allocations.small_zone == NULL)
		{
			if ((g_allocations.small_zone = mmap(NULL, small_zone_size + sizeof(struct s_zone), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) != MAP_FAILED)
			{
				g_allocations.small_zone->s_block = NULL;
				g_allocations.small_zone->used_bytes = 0;
			}
		}
		if (g_allocations.small_zone != NULL)
		{
			size_t aligned_size = size + (word_size - (size % word_size));
			printf("aligned_size: %zu\n", aligned_size);
			if (g_allocations.small_zone->used_bytes + aligned_size <= small_zone_size)
			{
				struct s_block *block = NULL;
				if ((block = mmap(NULL, sizeof(struct s_block), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) != MAP_FAILED)
				{
					if (g_allocations.small_zone->block == NULL) {
						g_allocations.small_zone->block = block;
						block->begin = g_allocations.small_zone + sizeof(struct s_zone);
					}
					else {
						struct s_block *last_block = get_last_block();
						block->begin = last_block->end;
						last_block->next = block;
					}
					block->end = block->begin + aligned_size;
					block->next = NULL;
					g_allocations.small_zone->used_bytes += aligned_size;
					return block->begin;
				}
			}
		}
	}
	return NULL;
	// void *ptr;

	// if ((ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) != MAP_FAILED) {
	// 	struct s_block *block = NULL;
	// 	if ((block = mmap(NULL, sizeof(struct s_block), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) != MAP_FAILED) {
	// 		block->ptr = ptr;
	// 		block->size = size;
	// 		if (g_root != NULL) {
	// 			block->root = g_root;
	// 			block->next = NULL;
	// 			get_last_block()->next = block;
	// 		}
	// 		else {
	// 			block->root = block;
	// 			block->next = NULL;
	// 			g_root = block;
	// 		}
	// 		return ptr;
	// 	}
	// 	else {
	// 		munmap(ptr, size);
	// 	}
	// }
	// return NULL;
}

void ft_free(void *ptr) {
	struct s_block *block = get_block(ptr);
	if (block != NULL) {
		munmap(block->ptr, block->size);
		if (block->root == block) {
			g_root = block->next;
		}
		else {
			struct s_block *tmp = block->root;
			while (tmp->next != block) {
				tmp = tmp->next;
			}
			tmp->next = block->next;
		}
		munmap(block, sizeof(struct s_block));
	}
}

int main()
{
	// char *str = ft_malloc(38);
	free((void*)0x7f7f7f7f7f7f);
	// if (str) {
	// 	for (int i = 0; i < 10; i++) {
	// 		printf("%d ", str[i]);
	// 	}
	// 	sprintf(str, "Hello");
	// 	printf("%s\n", str);
	// 	ft_free(str);
	// }
	return 0;
}