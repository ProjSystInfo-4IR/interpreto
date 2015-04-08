#include <stdarg.h>
#include <stdio.h>
#include "logger.h"
static int logger_level = LOGGER_SILENT;

int logger_set_level(int mode) {
	if (mode < 0 || 1 < mode) {
		printf("logger_set_mode : argument invalid\n");
		return -1;
	}
	logger_level = mode;
	return 0;
}

int logger_error(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	return 0;
}

int logger_info(const char* fmt, ...) {
	if (logger_level != LOGGER_VERBOSE) {
		return 0;
	}
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	return 0;
}
/*
int main() {
	char* a = "ASD";
	logger_error("I got %s %d\n", a, 5);
	logger_info("I got %s %d\n", a, 123);
	logger_set_level(LOGGER_VERBOSE);
	logger_error("I got %s %d\n", a, 5);
	logger_info("I got %s %d\n", a, 123);
	return 0;
}*/
