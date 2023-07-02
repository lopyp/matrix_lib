UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	LCOV= lcov
	GENHTML= genhtml 
	LFLAG= -lm -lrt -lpthread -lsubunit
endif
ifeq ($(UNAME), Darwin)
	PATH := $(PATH):${HOME}/homebrew/bin
	LCOV= $(shell PATH=$(PATH) which lcov)
	GENHTML= $(shell PATH=$(PATH) which genhtml) 
	LFLAG=
endif
CC=gcc
CFLAGS= -Wall -Wextra -Werror -pedantic 
CPPFLAGS = -lstdc++
DEBUG=
DEBUG:=
SOURCE:=$(shell find . -maxdepth 1 -name "s21_*.cc")
OBJECTS:=$(SOURCE:.cc=.o)
RESULT= s21_matrix_oop.a
TESTS= tests/*.cc

all: $(RESULT) test gcov_report

clean:
	rm -rf $(OBJECTS) $(RESULT) test report *.gc* *.out *.gch log.txt gcov* cov build

$(OBJECTS): %.o: %.cc
	$(CC) $(DEBUG) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ 

$(RESULT): $(OBJECTS)
	ar rc $@ $^
	ranlib $@
	rm -rf *.o *.gch

test:
	cmake -S . -B build
	cmake --build build
	./build/matr_test 

gcov_report:
	mkdir -p cov
	$(CC) $(DEBUG) $(CPPFLAGS) $(SOURCE) $(TESTS) -lgtest -o $@ --coverage $(LFLAG)
	./$@
	rm -rf *test*.gc*
	gcov -d . s21_*.cc 
	$(LCOV) -d . -o cov/$@.info -c
	$(GENHTML) -o cov/report cov/$@.info
	open cov/report/index.html
	mv *.gc* cov

leak_style: test
	leaks -atExit -- ./build/matr_test
	make clean
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n $(SOURCE) ./tests/*
	rm -rf .clang-format

valgrind: test
	valgrind --log-fd=1 --leak-check=full --log-file=log.txt -s ./test

main: $(OBJECTS)
	$(CC) $(CPPFLAGS) $(OBJECTS) main.cc -o $@ $(LFLAG) 
	leaks -atExit -- ./$@
