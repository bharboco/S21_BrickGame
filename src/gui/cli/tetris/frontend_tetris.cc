#include "frontend_tetris.h"

void drawField(const GameInfo_t game_info, const UserAction_t user_action) {
  clear();
  for (int rows = 0; rows < HEIGHT; ++rows) {
    for (int cols = 0; cols < WIDTH; ++cols) {
      if (game_info.field[rows][cols] == 1) {
        if (cols % 2 == 1) printw("%c", 'X');
        if (cols % 2 == 0) printw("%c", 'X');
      } else if (game_info.field[rows][cols] == 2)
        printw("%c", '|');
      else if (game_info.field[rows][cols] == 3)
        printw("%c", '#');
      else
        printw("%c", ' ');
    }
    printw("%c", '\n');
  }

  drawBoard(game_info, user_action);

  mvaddch(21, 11, 'X');

  refresh();
}

void drawNext(const GameInfo_t game_info) {
  mvaddch(4, WIDTH + 1, ' ');
  printw("NEXT:");
  for (int rows = 0; rows < 4; ++rows) {
    for (int cols = 0; cols < 4; ++cols) {
      if (game_info.next[rows][cols] == 3) {
        printw("%c", '#');
      } else {
        printw("%c", ' ');
      }
    }
    mvaddch(rows + 5, WIDTH + 1, ' ');
  }
}

void drawBoard(const GameInfo_t game_info, const UserAction_t user_action) {
  mvaddch(0, WIDTH + 1, ' ');
  printw("RECORD: %d", game_info.high_score);
  mvaddch(1, WIDTH + 1, ' ');
  printw("SCORE: %d", game_info.score);
  mvaddch(2, WIDTH + 1, ' ');
  printw("LEVEL: %d", game_info.level);

  drawNext(game_info);

  mvaddch(9, WIDTH + 1, ' ');
  printw("CONTROL:");
  mvaddch(10, WIDTH + 1, ' ');
  printw("BOOST: 'B'");
  mvaddch(11, WIDTH + 1, ' ');
  printw("ROTATE: SPACE");
  mvaddch(12, WIDTH + 1, ' ');
  if (!game_info.pause)
    printw("PAUSE: 'P'");
  else
    printw("UNPAUSE: 'P'");

  if (user_action != Terminate) {
    mvaddch(13, WIDTH + 1, ' ');
    printw("QUIT: 'Q'");
  }

  if (user_action == Terminate) {
    mvaddch(15, WIDTH + 1, ' ');
    printw("GAME OVER");
    mvaddch(16, WIDTH + 1, ' ');
    printw("NEW GAME: 'S'");
    mvaddch(17, WIDTH + 1, ' ');
    printw("QUIT: 'Q'");
  }
}

int gameLoop() {
  GameInfo_t game_info;
  UserAction_t user_action = Start;
  Figure_t random = randomGenerate();
  Figure_t random_next = randomGenerate();
  start(&game_info, random, random_next, "brick_game/tetris/record.txt");
  drawField(game_info, user_action);
  while (user_action != Terminate) {
    int count = 0;
    for (int i = 0, n = 20; i < n && user_action != Terminate; ++i) {
      game_info.direction = 0;
      int key = getch();
      userInput(&user_action, key);
      updateCurrentState(&game_info, &user_action, &count, &n, &random,
                         &random_next, "brick_game/tetris/record.txt");
      drawField(game_info, user_action);
      usleep(game_info.speed);
      ++count;
    }

    drawField(game_info, user_action);
  }
  if (user_action == Terminate) return 1;

  return 0;
}

void consoleTetris() {
  initscr();
  nodelay(stdscr, true);
  keypad(stdscr, true);
  bool game_over = false;
  printw("START GAME: 'S'\n");
  printw("QUIT: 'Q'\n");
  while (!game_over) {
    int key = getch();
    if (key == 's')
      gameLoop();
    else if (key == 'q')
      game_over = true;
  }
  endwin();
}