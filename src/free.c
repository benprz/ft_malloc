#include "malloc.h"

void ft_free(void *ptr) {
	// struct s_block *block = get_block(ptr);
	// if (block != NULL) {
	// 	munmap(block->ptr, block->size);
	// 	if (block->root == block) {
	// 		g_root = block->next;
	// 	}
	// 	else {
	// 		struct s_block *tmp = block->root;
	// 		while (tmp->next != block) {
	// 			tmp = tmp->next;
	// 		}
	// 		tmp->next = block->next;
	// 	}
	// 	munmap(block, sizeof(struct s_block));
	// }
}