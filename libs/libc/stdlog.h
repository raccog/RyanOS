#pragma once

#include <stdio.h>

typedef enum {
	DEBUG = 0,
	INFO = 1,
	WARN = 2,
	ERROR = 3,
	CRITICAL = 4
} LogLevel;

void log_set_level(LogLevel level);
LogLevel log_get_level();

#define LOG_INFO(fmt, ...) \
	if (log_get_level() <= INFO) \
		printf("[INFO-%s/%s:%u] " fmt "\n", __LIBRARY__, __FILE__, __LINE__, __VA_ARGS__)
