CC=gcc
CFLAGS=-Wall -Werror -Wextra -g -std=c11
RM=rm -rf
EXECUTABLE=matrix_test
UNAME = $(shell uname -s)
LIB = s21_matrix.a
TST_LIBS = -lcheck -lm -lpthread -fprofile-arcs

ifeq ($(UNAME),Darwin)
	CC+=-D MAC_OS
endif
ifeq ($(UNAME),Linux)
	CC+=-D LINUX_OS
	TST_LIBS = -lsubunit -lrt
endif

all: test

rebuild: fclean all

test: $(LIB)
	$(CC) $(CFLAGS) s21_matrix_test.c -L. $(LIB) $(TST_LIBS) -o ./$(EXECUTABLE)
	$(CC) $(CFLAGS) --coverage s21_matrix_test.c s21_matrix.c $(LIB) -L. $(LIB) $(TST_LIBS) -o ./$(EXECUTABLE)
	./$(EXECUTABLE)

$(EXECUTABLE): s21_matrix_test.o $(LIB)
	$(CC) $(CFLAGS) --coverage $(TST_LIBS) -o $(EXECUTABLE) s21_matrix_test.o -L./ $(LIB)

$(LIB): s21_matrix.o
	ar r $@ $<

%.o: %.c
	$(CC) -c $< -o $@

clean:
	$(RM) *.a *.o *.gcno *.gcda

fclean: clean
	$(RM) $(EXECUTABLE)

check:
	cppcheck *.c *.h

.PHONY: all rebuild test clean fclean gcov_report check