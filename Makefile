
SAN = -fsanitize=address
W = -Wall -Werror -Wextra
FLAGS = -std=c11 -g
CMPL = gcc

LIBS=-lcheck
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBS += -lsubunit -lm
endif

all: clean s21_string.a test gcov_report
	
check: 
	find . -name "*.c" -exec clang-format --style=Google -i {} \;
	find . -name "*.h" -exec clang-format --style=Google -i {} \;

clean:
	rm -f *.o *.a *.out *.gcda *.gcno *.info *.out

s21_decimal.o :
	${CMPL} ${FLAGS} -o s21_decimal.o s21_decimal.c

s21_helpers.o :
	${CMPL} ${FLAGS} -o s21_decimal.o s21_helpers.c	

s21_decimal.a : 
	ar r libs21_decimal.a s21_decimal.o s21_helpers.o
	ar r s21_decimal.a s21_decimal.o s21_helpers.o

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

test : clean check
	${CMPL} ${FLAGS} -o test s21_decimal.c s21_helpers.c s21_test.c ${LIBS}

	
test2 : clean check
	${CMPL} ${FLAGS} -o test2 s21_decimal.c s21_helpers.c test.c 