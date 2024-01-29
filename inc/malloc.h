#ifndef MALLOC_H
#define MALLOC_H
#pragma once

#define _GNU_SOURCE
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <stdbool.h>
#include <unistd.h>

#include <stdio.h>

#include "libft.h"

struct s_zone
{
	struct s_block *block;
	size_t used_bytes;
	// struct s_zone *next;
};

struct s_block
{
	void *begin;
	void *end; // (begin + size)
	struct s_block *next;
};

struct s_malloc
{
	bool is_struct_init;

	// sizes
	size_t page_size;
	size_t word_size;
	size_t small_zone_size;
	size_t medium_zone_size;
	size_t small_alloc_size;
	size_t medium_alloc_size;

	struct s_zone *small_zone;
	struct s_zone *medium_zone;


};

struct s_malloc g_malloc;

#endif