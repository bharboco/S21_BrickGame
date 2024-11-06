#include "snake/Console_view.h"
#include "tetris/frontend_tetris.h"

int main() {
  s21::View::initializeWindow();
  while (1) {
    clear();
    printw(
        "MENU:\nPress '1' to play Snake\nPress '2' to play Tetris\nPress '3' "
        "to Exit\n");
    int choice = getch();
    if (choice == '1')
      s21::View::consoleSnake();
    else if (choice == '2') {
      clear();
      consoleTetris();
    } else if (choice == '3') {
      break;
    }
  }
  endwin();
}