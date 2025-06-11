CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
LDFLAGS = -lm

.PHONY: all clean verify_format format test

all:	test

clean:
	rm -f *.o *.a *_test.exe array_test

verify_format:
	find . -type f -name "*.c" -o -name "*.h" -exec clang-format --style=LLVM --dry-run -Werror {} +

format:
	find . -type f -name "*.c" -o -name "*.h" -exec clang-format --style=LLVM -i {} +

test:
	@for test_file in $$(find . -maxdepth 1 -name "*_test.c"); do \
  		base=$$(basename "$$test_file" .c); \
  		main_file=$${base%%_test*}.c; \
  		echo "Building $$base from $$main_file and $$test_file"; \
  		if [ "$$base" = "linear_alloc_test" ]; then \
   		$(CC) $(CFLAGS) $$main_file $$test_file -o $$base $(LDFLAGS); \
  		else \
   		$(CC) $(CFLAGS) $$main_file $$test_file linear_alloc.c -o $$base $(LDFLAGS); \
  		fi; \
  		echo "Running $$base..."; \
  		./$$base || exit 1; \
	done
