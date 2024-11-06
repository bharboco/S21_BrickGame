#ifndef _CONSOLE_VIEW_H_
#define _CONSOLE_VIEW_H_

#include <ncurses.h>

#include "../../../brick_game/snake/Controller.h"

namespace s21 {
class View {
 private:
  static void render(Controller &controller) {
    clear();
    mvprintw(15, 20, "LVL: %d", controller.getLvl());
    mvprintw(16, 20, "Max score: %d", controller.getMaxScore());
    mvprintw(17, 20, "Current score: %d", controller.getScore());
    mvprintw(18, 20, "Pause press 'p'");
    mvprintw(19, 20, "Quit press 'q'");

    if (controller.getStatusGame()) {
      mvprintw(21, 20, "Game Over !!! 0_o");
      mvprintw(22, 20, "New game press 's'");
    }
    if ((controller.getScore() == 196)) {
      mvprintw(23, 20, "Game WIN !!! ^_^");
    }

    for (int y = 0; y < 22; ++y) {
      for (int x = 0; x < 12; ++x) {
        if (y == 0 || y == 21 || x == 0 || x == 11) {
          mvaddch(y, x, '#');
        } else if (x == controller.getFood().x && y == controller.getFood().y) {
          mvaddch(y, x, '*');
        } else {
          bool isbody = false;
          for (const auto &cord : controller.getBody()) {
            if (cord.x == x && cord.y == y) {
              isbody = true;
              break;
            }
          }
          mvaddch(y, x, isbody ? 'O' : ' ');
        }
      }
    }
    refresh();
  }

  static void userInput(Controller &controller) {
    int vr = getch();
    switch (vr) {
      case KEY_LEFT:
        controller.changeDirection('a');
        break;
      case KEY_RIGHT:
        controller.changeDirection('d');
        break;
      case 'q':
        controller.setStatusGame();
        break;
      case 'p':
        controller.setPause();
        break;
    }
  }

  static void play() {
    Controller controller;
    while (!controller.getStatusGame() && controller.getScore() != 196) {
      userInput(controller);
      if (!controller.getPause()) {
        controller.moveSnake("brick_game/snake/record.txt");
        if (controller.getCheckCollision()) {
          controller.setStatusGame();
          if (controller.getStatusGame()) break;
        }
      }
      render(controller);
      usleep(controller.getSpeed());
    }
    render_final(controller);
  }

  static void render_final(Controller &controller) {
    if (controller.getStatusGame()) {
      mvprintw(21, 20, "Game Over !!! 0_o");
      mvprintw(22, 20, "New game press 's'");
    }
  }

 public:
  static WINDOW *initializeWindow() {
    WINDOW *win = initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(win, true);
    noecho();
    return win;
  }

  static void consoleSnake() {
    initializeWindow();
    clear();
    printw("New game press 's'\n");
    printw("Quit press 'q'");
    while (1) {
      int vg = getch();
      if (vg == 's') {
        play();
      } else if (vg == 'q') {
        break;
      }
    }
    endwin();
  }
};

}  // namespace s21
#endif