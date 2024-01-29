#define _GNU_SOURCE
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

struct s_zone {
	struct s_block *s_block;
	size_t used_bytes;
	// struct s_zone *next;
};

struct s_zone *g_tiny_zone = NULL;
struct s_zone *g_small_zone = NULL;
struct s_zone *g_large_zone = NULL;

struct s_block {
	void *ptr;
	size_t size;
	struct s_block *next;
};

struct s_block *get_block(void *ptr) {
	struct s_block *block = g_root;
	while (block != NULL) {
		if (block->ptr == ptr) {
			return block;
		}
		block = block->next;
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

void *ft_malloc(size_t size) {
	size_t page_size = getpagesize();
	size_t tiny_zone_size = page_size;
	size_t small_zone_size = page_size * 10;
	size_t large_zone_size = page_size * 100;
	size_t tiny_alloc_size = (tiny_zone_size / 100) + (tiny_zone_size % 100);
	size_t small_alloc_size = (small_zone_size / 100) + (small_zone_size % 100);
	size_t large_alloc_size = (large_zone_size / 100) + (large_zone_size % 100);
	size_t word_size = sizeof(void *);

	if (size <= tiny_alloc_size) {
		// tiny
		if (g_tiny_zone == NULL) {
			if ((g_tiny_zone = mmap(NULL, tiny_zone_size + sizeof(struct s_zone), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) != MAP_FAILED) {
				g_tiny_zone->s_block = NULL;
				g_tiny_zone->used_bytes = 0;
			}
		}
		if (g_tiny_zone != NULL) {
			size_t aligned_size = size + (word_size - (size % word_size));
			if ()

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

int main() {
	//print getpagesize
	printf("getpagesize: %d\n", getpagesize());
	char *str = ft_malloc(10);
	if (str) {
		for (int i = 0; i < 10; i++) {
			printf("%d ", str[i]);
		}
		sprintf(str, "Hello");
		printf("%s\n", str);
		ft_free(str);
	}
	// struct rlimit rlim;
	// getrlimit(RLIMIT_AS, &rlim);
	// printf("rlim_cur: %lu\n", rlim.rlim_cur);
	
	return 0;
}