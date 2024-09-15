CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -g
V_COMMAND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt
L_COMMAND = leaks -atExit --

PATH_TO_TESTS = test/
COV_REPORT = report/
DOCUMENTATION = doxygen/
OBJ_DIR = obj/
COV_OBJ_DIR = obj/cov
TEST_OBJ_DIR = obj/test
PATH_TO_FUNCTIONS = functions/templates/
PATH_TO_INCLUDE = functions/include/

EXEC = s21_containers.a
EXEC_T = unit_tests

SRC_T = $(wildcard $(PATH_TO_TESTS)*.cpp)
OBJ_T = $(SRC_T:%.cpp=%.o)

OS := $(shell uname -s)

all: test

test: $(OBJ_DIR) $(TEST_OBJ_DIR) $(OBJ_T) $(SRC_T) path
	@#echo $(SRC_T)
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(OBJ_T) -o $(PATH_TO_TESTS)$(EXEC_T) -lgtest -lgtest_main -pthread
else
	$(CC) $(CFLAGS) $(OBJ_T) -o $(PATH_TO_TESTS)$(EXEC_T) -lgtest -lgtest_main -lpthread
	OPEN_CM=open

endif

	$(PATH_TO_TESTS)./$(EXEC_T)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $(addprefix $(OBJ_DIR), $@)

path:
	$(eval OBJ_T = $(addprefix $(TEST_OBJ_DIR)/, $(notdir $(OBJ_T))))

format-check:
	@echo $(SRC_T)
	@echo $(OBJ_T)
	@cp ../materials/linters/.clang-format ./
	@clang-format -n *.h $(PATH_TO_INCLUDE)*.h $(PATH_TO_FUNCTIONS)*.tpp $(PATH_TO_TESTS)*.cpp $(PATH_TO_TESTS)*.h
	@rm .clang-format

format:
	@cp ../materials/linters/.clang-format ./
	@clang-format -i *.h $(PATH_TO_TESTS)*.cpp $(PATH_TO_INCLUDE)*.h $(PATH_TO_FUNCTIONS)*.tpp $(PATH_TO_TESTS)*.h
	@rm .clang-format

cppcheck:
	@cppcheck --enable=all --suppress=missingIncludeSystem $(PATH_TO_FUNCTIONS)*.tpp $(PATH_TO_INCLUDE)*.h $(PATH_TO_TESTS)*.cpp

valgrind: test
	$(V_COMMAND) ./$(PATH_TO_TESTS)$(EXEC_T)

leaks: test
	$(L_COMMAND) ./$(PATH_TO_TESTS)$(EXEC_T)

coverage_flag:
	$(eval CFLAGS += --coverage -fprofile-arcs -ftest-coverage)

sanitize: sanitize_flag test
	./$(PATH_TO_TESTS)$(EXEC_T)

sanitize_flag:
	$(eval CFLAGS += -fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector)

gcov_report: coverage_flag test
#	gcov -b -l -p -c obj/test/*.gcno
#	cp obj/test/*.gcno test/
#	cp obj/test/*.gcda test/
#	gcov -b -l -p -c test/*.cpp
#	gcovr  -o coverage_report.html --html-details
#	open coverage_report.html
	@gcov --no-output $(SRC_T)
	@lcov --no-external --capture --directory . --output-file coverage.info
	@genhtml coverage.info -o report

#	@firefox report/index.html

doc:
	@doxygen
	@firefox $(DOCUMENTATION)html/index.html

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(COV_OBJ_DIR):
	@mkdir -p $(COV_OBJ_DIR)

$(TEST_OBJ_DIR):
	@mkdir -p $(TEST_OBJ_DIR)

clean:
	@rm -rf $(PATH_TO_FUNCTIONS)*.o $(EXEC) $(PATH_TO_TESTS)*.o $(PATH_TO_TESTS)./$(EXEC_T)
	@rm -rf $(PATH_TO_FUNCTIONS)*.gcno && rm -rf $(PATH_TO_FUNCTIONS)*.gcda
	@rm -rf $(PATH_TO_FUNCTIONS)*.info && rm -rf $(PATH_TO_FUNCTIONS)*.gcov
	@rm -rf $(PATH_TO_TESTS)*.gcda $(PATH_TO_TESTS)*.gcno
	@rm -rf $(PATH_TO_TESTS)*.gcda $(PATH_TO_TESTS)*.gcno
	@rm -rf RESULT_VALGRIND.txt gcov_*
	@rm -rf $(COV_REPORT)
	@rm -rf $(DOCUMENTATION)
	@rm -rf $(OBJ_DIR)
	@rm -rf *.gcov *.html *.css
	@rm -rf coverage.info
