CC = gcc
CPP = g++
FLAGS = -Wall -Werror -Wextra
CPPFLAGS = -std=c++17 -lstdc++

CLANG_FILES = **/**/*.h **/**/*.cc **/**/**/*.cpp **/**/**/*.cc **/**/**/*.h tests/*.cc
SOURCE_TETRIS = brick_game/tetris/functions/*.cc gui/cli/tetris/*.cc
HEADERS_TETRIS = brick_game/tetris/*.h gui/cli/tetris/*.h
SOURCE_TEST = brick_game/tetris/functions/*.cc tests/*.cc

CONSOLE_MENU_EXEC = console_menu

OS = $(shell uname)
ifeq ($(OS), Linux)
	CHECK_FLAGS = -lgtest -lsubunit
else
	CHECK_FLAGS = -lgtest
endif

all: console_menu

# CONSOLE
console_menu: uninstall
	$(CC) $(FLAGS) -lncurses $(CPPFLAGS) $(SOURCE_TETRIS) gui/cli/console_menu.cc -o $(CONSOLE_MENU_EXEC)
	./$(CONSOLE_MENU_EXEC)

# DESKTOP
install: uninstall
	cmake -B gui/desktop/build "gui/desktop/Menu" && make -C gui/desktop/build Menu
	cp -R gui/desktop/build/Menu.app ~/Desktop

# OTHER
test: uninstall
	@$(CPP) $(FLAGS) $(CPPFLAGS) $(SOURCE_TEST) -o test $(CHECK_FLAGS)
	@./test

gcov_report: uninstall
	@$(CPP) $(FLAGS) --coverage $(CPPFLAGS) $(SOURCE_TEST) -o test $(CHECK_FLAGS)
	./test
	@lcov --ignore-errors inconsistent -t "test" -o test.info -c -d .
	@lcov --remove test.info '/usr/*' -o test.info
	@genhtml -o report test.info
	@open ./report/index.html
	@rm -rf *.gcno *.gcda *.info test

dist: uninstall install
	@mkdir archiv
	@cp -r $(SOURCE_TETRIS) $(HEADERS_TETRIS) archiv
	@tar -cf tetris.tar archiv
	@rm -rf archiv

dvi:
	open ../README_RUS.md

install_brew:
	@git clone https://github.com/Homebrew/brew ~/goinfre/homebrew
	@cd ~
	@eval "$(goinfre/homebrew/bin/brew shellenv)"
	@brew update --force --quiet
	@chmod -R go-w "$(brew --prefix)/share/zsh"

install_lcov:
	@cd ~
	@brew install lcov

style_check:
	clang-format --style=Google -n $(CLANG_FILES)

clang:
	@clang-format --style=Google -i $(CLANG_FILES)
	
valgrind:
	docker build -t tetris .
	docker run --name stock tetris

clear:
	docker rm stock
	docker rmi tetris

uninstall: clean

clean:
	@rm -rf $(CONSOLE_MENU_EXEC) gui/desktop/build ~/Desktop/Menu_QT.app *.o *.a tetris.tar
	@rm -rf *.gcno *.gcda *.info test report
