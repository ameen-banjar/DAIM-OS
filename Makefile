CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Werror

.PHONY: check
check:
	$(CC) $(CFLAGS) -I. -fsyntax-only tests/header_compile.c
