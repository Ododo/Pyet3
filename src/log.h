#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>
#include <errno.h>

#define LOG_ID "Pyet3"

#define LOG_INFO(fmt, ...) \
	printf("(" LOG_ID "/%s) " fmt "\n", __func__, ##__VA_ARGS__)

#define LOG_ERR(fmt, ...)  \
	do { \
		int err = errno; \
		fprintf(stderr, "(" LOG_ID "/%s) " fmt ": %m\n",  \
			__func__, ##__VA_ARGS__); \
		errno = err; \
	} while (0)

#ifdef PRINT_DEBUG
#define LOG_DEBUG LOG_INFO
#else
#define LOG_DEBUG(...)
#endif

#endif
