#include "../inc/malloc.h"

// struct s_block *get_block(void *ptr) {
// 	struct s_block *block;
// 	if (ptr >= g_malloc.small_zone + sizeof(struct s_zone) && ptr <= g_malloc.small_zone + sizeof(struct s_zone) + small_zone_size) {
// 		while (block != NULL) {
// 			if (block->begin == ptr) {
// 				return block;
// 			}
// 			block = block->next;
// 		}
// 	}
// 	else if (ptr >= g_medium_zone + sizeof(struct s_zone) && ptr <= g_medium_zone + sizeof(struct s_zone) + medium_zone_size) {
// 		while (block != NULL) {
// 			if (block->begin == ptr) {
// 				return block;
// 			}
// 			block = block->next;
// 		}
// 	}
// 	return NULL;
// }

// struct s_block *get_last_block() {
// 	struct s_block *block = g_root;
// 	while (block->next != NULL) {
// 		block = block->next;
// 	}
// 	return block;
// }

void init_malloc() {
	struct rlimit limit;
	getrlimit(RLIMIT_AS, &limit);

	g_malloc.is_struct_init = true;
	g_malloc.small_zone = NULL;
	g_malloc.medium_zone = NULL;
	g_malloc.page_size = getpagesize();
	g_malloc.word_size = sizeof(void*);
	g_malloc.small_zone_size = limit.rlim_cur / 100;
	g_malloc.medium_zone_size = limit.rlim_cur / 100 * 10;
	g_malloc.small_alloc_size = g_malloc.small_zone_size / 100;
	g_malloc.medium_alloc_size = g_malloc.medium_zone_size / 100;
}

void *ft_malloc(size_t size)
{
	if (!g_malloc.is_struct_init) {
		init_malloc();
	}
	//print data
	printf("page_size: %zu\n", g_malloc.page_size);
	printf("word_size: %zu\n", g_malloc.word_size);
	printf("small_zone_size: %zu\n", g_malloc.small_zone_size);
	printf("medium_zone_size: %zu\n", g_malloc.medium_zone_size);
	printf("small_alloc_size: %zu\n", g_malloc.small_alloc_size);
	printf("medium_alloc_size: %zu\n", g_malloc.medium_alloc_size);

	// if (size <= small_alloc_size)
	// {
	// 	if (g_malloc.small_zone == NULL)
	// 	{
	// 		if ((g_malloc.small_zone = mmap(NULL, small_zone_size + sizeof(struct s_zone), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) != MAP_FAILED)
	// 		{
	// 			g_malloc.small_zone->s_block = NULL;
	// 			g_malloc.small_zone->used_bytes = 0;
	// 		}
	// 	}
	// 	if (g_malloc.small_zone != NULL)
	// 	{
	// 		size_t aligned_size = size + (word_size - (size % word_size));
	// 		printf("aligned_size: %zu\n", aligned_size);
	// 		if (g_malloc.small_zone->used_bytes + aligned_size <= small_zone_size)
	// 		{
	// 			struct s_block *block = NULL;
	// 			if ((block = mmap(NULL, sizeof(struct s_block), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) != MAP_FAILED)
	// 			{
	// 				if (g_malloc.small_zone->block == NULL) {
	// 					g_malloc.small_zone->block = block;
	// 					block->begin = g_malloc.small_zone + sizeof(struct s_zone);
	// 				}
	// 				else {
	// 					struct s_block *last_block = get_last_block();
	// 					block->begin = last_block->end;
	// 					last_block->next = block;
	// 				}
	// 				block->end = block->begin + aligned_size;
	// 				block->next = NULL;
	// 				g_malloc.small_zone->used_bytes += aligned_size;
	// 				return block->begin;
	// 			}
	// 		}
	// 	}
	// }
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


int main()
{
	ft_malloc(10);
	return 0;
}
