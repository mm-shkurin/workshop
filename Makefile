CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
LDFLAGS = -lm

.PHONY: all clean verify_format format test

all: test

clean:
	rm -f *.o *.a *_test

verify_format:
	find . -type f -regex ".*\.[ch]" -exec clang-format --style=LLVM --dry-run -Werror {} +

format:
	find . -type f -regex ".*\.[ch]" -exec clang-format --style=LLVM -i {} +

test:
	@for test_file in $$(find . -maxdepth 1 -name "*_test.c"); do \
		base=$$(basename "$$test_file" .c); \
		main_file=$${base%%_test*}.c; \
		extra_files=""; \
		if [ "$$base" = "hashtable_test" ]; then \
			extra_files="pool_alloc.c"; \
		fi; \
		echo "Building $$base from $$main_file, $$test_file and $$extra_files"; \
		$(CC) $(CFLAGS) $$main_file $$test_file $$extra_files -o $$base $(LDFLAGS); \
		echo "Running $$base..."; \
		./$$base || exit 1; \
	done