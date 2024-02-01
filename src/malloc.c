#include "../inc/malloc.h"

struct s_malloc g_malloc = {
	.tiny = NULL,
	.small = NULL,
};

void print_rlimits()
{
	struct rlimit limit;

	//print all limits with nice printing
	getrlimit(RLIMIT_AS, &limit);
	printf("RLIMIT_AS: limit.rlim_cur: %zu\n", limit.rlim_cur);
	printf("RLIMIT_AS: limit.rlim_max: %zu\n\n", limit.rlim_max);

	getrlimit(RLIMIT_CORE, &limit);
	printf("RLIMIT_CORE: limit.rlim_cur: %zu\n", limit.rlim_cur);
	printf("RLIMIT_CORE: limit.rlim_max: %zu\n\n", limit.rlim_max);

	getrlimit(RLIMIT_CPU, &limit);
	printf("RLIMIT_CPU: limit.rlim_cur: %zu\n", limit.rlim_cur);
	printf("RLIMIT_CPU: limit.rlim_max: %zu\n\n", limit.rlim_max);

	getrlimit(RLIMIT_DATA, &limit);
	printf("RLIMIT_DATA: limit.rlim_cur: %zu\n", limit.rlim_cur);
	printf("RLIMIT_DATA: limit.rlim_max: %zu\n\n", limit.rlim_max);

	getrlimit(RLIMIT_FSIZE, &limit);
	printf("RLIMIT_FSIZE: limit.rlim_cur: %zu\n", limit.rlim_cur);
	printf("RLIMIT_FSIZE: limit.rlim_max: %zu\n\n", limit.rlim_max);

	getrlimit(RLIMIT_LOCKS, &limit);
	printf("RLIMIT_LOCKS: limit.rlim_cur: %zu\n", limit.rlim_cur);
	printf("RLIMIT_LOCKS: limit.rlim_max: %zu\n\n", limit.rlim_max);

	getrlimit(RLIMIT_MEMLOCK, &limit);
	printf("RLIMIT_MEMLOCK: limit.rlim_cur: %zu\n", limit.rlim_cur);
	printf("RLIMIT_MEMLOCK: limit.rlim_max: %zu\n\n", limit.rlim_max);

	getrlimit(RLIMIT_MSGQUEUE, &limit);
	printf("RLIMIT_MSGQUEUE: limit.rlim_cur: %zu\n", limit.rlim_cur);
	printf("RLIMIT_MSGQUEUE: limit.rlim_max: %zu\n\n", limit.rlim_max);

	getrlimit(RLIMIT_NICE, &limit);
	printf("RLIMIT_NICE: limit.rlim_cur: %zu\n", limit.rlim_cur);
	printf("RLIMIT_NICE: limit.rlim_max: %zu\n\n", limit.rlim_max);

	getrlimit(RLIMIT_NOFILE, &limit);
	printf("RLIMIT_NOFILE: limit.rlim_cur: %zu\n", limit.rlim_cur);
	printf("RLIMIT_NOFILE: limit.rlim_max: %zu\n\n", limit.rlim_max);

	getrlimit(RLIMIT_NPROC, &limit);
	printf("RLIMIT_NPROC: limit.rlim_cur: %zu\n", limit.rlim_cur);
	printf("RLIMIT_NPROC: limit.rlim_max: %zu\n\n", limit.rlim_max);

	getrlimit(RLIMIT_RSS, &limit);
	printf("RLIMIT_RSS: limit.rlim_cur: %zu\n", limit.rlim_cur);
	printf("RLIMIT_RSS: limit.rlim_max: %zu\n\n", limit.rlim_max);

	getrlimit(RLIMIT_RTPRIO, &limit);
	printf("RLIMIT_RTPRIO: limit.rlim_cur: %zu\n", limit.rlim_cur);
	printf("RLIMIT_RTPRIO: limit.rlim_max: %zu\n\n", limit.rlim_max);

	getrlimit(RLIMIT_RTTIME, &limit);
	printf("RLIMIT_RTTIME: limit.rlim_cur: %zu\n", limit.rlim_cur);
	printf("RLIMIT_RTTIME: limit.rlim_max: %zu\n\n", limit.rlim_max);

	getrlimit(RLIMIT_SIGPENDING, &limit);
	printf("RLIMIT_SIGPENDING: limit.rlim_cur: %zu\n", limit.rlim_cur);
	printf("RLIMIT_SIGPENDING: limit.rlim_max: %zu\n\n", limit.rlim_max);

	getrlimit(RLIMIT_STACK, &limit);
	printf("RLIMIT_STACK: limit.rlim_cur: %zu\n", limit.rlim_cur);
	printf("RLIMIT_STACK: limit.rlim_max: %zu\n\n", limit.rlim_max);
}

void init_malloc() {
	print_rlimits();
}

void *ft_malloc(size_t size)
{
	printf("%d\n", EXEC_PAGESIZE);
	// if (!g_malloc.is_struct_init) {
	// 	init_malloc();
	// }

	return NULL;
}


int main()
{
	ft_malloc(10);
	return 0;
}
