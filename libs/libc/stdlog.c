#include "stdlog.h"

static LogLevel log_level = DEBUG;

void log_set_level(LogLevel level) {
	log_level = level;
}

LogLevel log_get_level() {
	return log_level;
}

