
SAN = -fsanitize=address
W = -Wall -Werror -Wextra
FLAGS = -std=c11 -g ${W}
CMPL = gcc

LIBS=-lcheck
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBS += -lsubunit -lm
endif

all: clean s21_string.a test gcov_report
	
check: 
	find . -type f \( -name "*.c" -o -name "*.h" \) -exec clang-format -i {} +

clean:
	rm -f *.o *.a *.out *.gcda *.gcno *.info *.out


s21_string.a : s21_string.o s21_sprintf.o s21_citoa.o s21_sscanf.o
	ar r libs21_string.a s21_string.o s21_sprintf.o s21_citoa.o s21_sscanf.o
	ar r s21_string.a s21_string.o s21_sprintf.o s21_citoa.o s21_sscanf.o

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

test : clean lint-fix lint-errors test_string test_sprintf test_sscanf 
	./test_sprintf.out
	./test_sscanf.out
	./test_string.out

