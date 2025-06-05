CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
LDFLAGS = -lm

.PHONY: all clean verify_format format test

all: test

clean:
	rm -f *.o *.a *_test.exe

verify_format:
	find . -type f -name "*.c" -o -name "*.h" -exec clang-format --style=LLVM --dry-run -Werror {} +

format:
	find . -type f -name "*.c" -o -name "*.h" -exec clang-format --style=LLVM -i {} +

test:
	@for test_file in $$(find . -maxdepth 1 -name "*_test.c"); do \
		base=$$(basename "$$test_file" .c); \
		main_file=$${base%%_test*}.c; \
		echo "Building $$base from $$main_file and $$test_file"; \
		$(CC) $(CFLAGS) $$main_file $$test_file -o $$base $(LDFLAGS); \
		echo "Running $$base..."; \
		./$$base || exit 1; \
	done