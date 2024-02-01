#ifndef MALLOC_H
#define MALLOC_H
#pragma once

#define _GNU_SOURCE
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <stdbool.h>
#include <unistd.h>
#include <asm-generic/param.h> // EXEC_PAGESIZE

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

// zone aka arena -> regions -> blocks

struct s_malloc
{
	struct s_zone *tiny;
	struct s_zone *small;
};

extern struct s_malloc g_malloc;

#endif