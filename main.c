#define _GNU_SOURCE
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

struct s_block {
	void *ptr;
	size_t size;
	struct s_block *root;
	struct s_block *next;
};

struct s_block *g_root = NULL;

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
	void *ptr;

	if ((ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) != MAP_FAILED) {
		struct s_block *block = NULL;
		if ((block = mmap(NULL, sizeof(struct s_block), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) != MAP_FAILED) {
			block->ptr = ptr;
			block->size = size;
			if (g_root != NULL) {
				block->root = g_root;
				block->next = NULL;
				get_last_block()->next = block;
			}
			else {
				block->root = block;
				block->next = NULL;
				g_root = block;
			}
			return ptr;
		}
		else {
			munmap(ptr, size);
		}
	}
	return NULL;
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
	char *str = ft_malloc(0);
	if (str) {
		for (int i = 0; i < 10; i++) {
			printf("%d ", str[i]);
		}
		sprintf(str, "Hello");
		printf("%s\n", str);
		ft_free(str);
	}
	return 0;
}