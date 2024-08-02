CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g
SOURCE= $(wildcard s21_*.c)
OBJ= $(patsubst %.c, %.o, ${SOURCE})
LFLAGS= -lcheck -lm -lpthread 

ifeq ($(shell uname -s), Linux)
	LFLAGS += -lrt -lsubunit
endif

all: clean install

install: 
	rm -rf build
	mkdir build 
	cd build && qmake ../../front/Calculator.pro -o qt_makefile && make -sf qt_makefile
ifeq ($(shell uname -s), Linux)
	mv build/Calculator ../../
endif 
ifeq ($(shell uname -s), Darwin)
	mv build/Calculator.app ../../
endif

uninstall: 
	rm -rf build
	
build:
	$(CC) $(CFLAGS) $(wildcard s21_*.c) 

dvi: 	
	rm -rf html
	doxygen dvi_config
	open ./html/index.html

s21_calculate.o: 
	$(CC) $(CFLAGS) -c ${SOURCE}

s21_calculate.a: s21_calculate.o
	ar rcs s21_calculate.a ${OBJ}
	ranlib s21_calculate.a
	rm *.o

test: s21_calculate.a 
	$(CC) $(CFLAGS) unit_test.c s21_calculate.a -o unit_test $^ ${LFLAGS}
	./unit_test

gcov_report: clean ${SOURCE}
	$(CC) --coverage ${SOURCE} unit_test.c -o unit_test ${LFLAGS}
	./unit_test
	lcov -t "unit_test" -o unit_test.info -c -d .
	genhtml -o report unit_test.info
	open report/index.html 

leaks:
	cppcheck enable=all missingIncludeSystem *.c

style:
	clang-format -style=Google -i *.c *.h

clean:
	rm -rf *.o *.gc* test unit_test.info test_html/
	rm -rf s21_calculate.a
	rm -rf report
	rm -rf a.out unit_test
	rm -rf a.out unit_test.dSYM
	rm -rf html
	rm -rf build
	rm -rf ../../*.app


rebuild: 
	make clean
	make all