CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17

SRCS = ./s21_model/s21_model.cc

OBJS = $(SRCS:.cpp=.o)

TARGET = calculator

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test:
	$(CXX) $(CXXFLAGS) -lcheck -lm -lpthread -lgtest -lgtest_main tests.cpp $(SRCS) -o test
	./test

gcov_report:
	$(CXX) $(CXXFLAGS) -fprofile-arcs -ftest-coverage $(SRCS) tests.cpp -pthread -lcheck -pthread -lm -o test
	./test
	lcov -t "test_html" -o unit_test.info -c -d . --rc lcov_branch_coverage=1
	genhtml -o test_html unit_test.info
	open test_html/index.html

clean:
	rm -rf *.gc* *.o test unit_test.info test_html/ test

dvi:
	doxygen NewDoxyfile
	open html/index.html

uninstall: clean
	rm -Rf build

install:
	[ -d build ] || mkdir -p build
	cd build && qmake ../calc
	make -C ./build/

dist: uninstall
	cd ../ && tar -cf calc.tar src

run: install
	build/calc.app/Contents/MacOS/./calc

style:
	clang-format -n *.cpp *.h --style=Google
