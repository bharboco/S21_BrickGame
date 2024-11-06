#include "../tetris.h"

void zeroingGameInfo(GameInfo_t *game_info, std::string path) {
  game_info->score = 0;
  game_info->high_score = 0;
  record(game_info, path);
  game_info->level = 0;
  game_info->speed = 25000;
  game_info->pause = 0;
  game_info->direction = 0;
  game_info->shift_down = 0;
  game_info->shift_horizontal = 0;
}

int getMinCol(const GameInfo_t game_info) {
  int res = 15;
  for (int i = 0; i < 4; ++i) {
    if (game_info.figure[i].cols < res) {
      res = game_info.figure[i].cols;
    }
  }
  return res;
}

int getMaxCol(const GameInfo_t game_info) {
  int res = 0;
  for (int i = 0; i < 4; ++i) {
    if (game_info.figure[i].cols > res) {
      res = game_info.figure[i].cols;
    }
  }
  return res;
}

void deleteLines(GameInfo_t *game_info, std::string path) {
  int count_full_line = 0, not_full_line = 0;
  for (int rows = 20; rows > 0; --rows) {
    for (int cols = 1; cols < 11; ++cols) {
      if (game_info->field[rows][cols] == 0) {
        not_full_line = 1;
        break;
      }
    }
    if (!not_full_line) {  // full
      count_full_line++;
    } else {
      not_full_line = 0;
      if (count_full_line > 0) {
        moveDeleteLines(game_info, count_full_line, rows);
        changeScore(game_info, count_full_line);
        record(game_info, path);
        count_full_line = 0;
      }
    }
  }
}

void moveDeleteLines(GameInfo_t *game_info, const int count_full_line,
                     const int rows) {
  for (int i = 0; i < count_full_line; ++i) {
    for (int cols = 1; cols < 11; ++cols) {
      game_info->field[rows + i + 1][cols] = 0;
    }
  }

  for (int i = rows; i > 0; --i) {
    for (int cols = 1; cols < 11; ++cols) {
      game_info->field[i + count_full_line][cols] = game_info->field[i][cols];
    }
  }
}

void changeScore(GameInfo_t *game_info, const int count_full_line) {
  if (count_full_line == 1)
    game_info->score += 100;
  else if (count_full_line == 2)
    game_info->score += 300;
  else if (count_full_line == 3)
    game_info->score += 700;
  else if (count_full_line == 4)
    game_info->score += 1500;
  if (game_info->score >= 600 && game_info->level < 10) {
    game_info->level = game_info->score / 600;
    game_info->speed -= 2000;
    game_info->previos_speed = game_info->speed;
  }
}

Figure_t randomGenerate() {
  int random = (rand() % (6 - 0 + 1)) + 0;
  Figure_t res = O;

  if (random == 0)
    res = I;
  else if (random == 1)
    res = J;
  else if (random == 2)
    res = L;
  else if (random == 3)
    res = O;
  else if (random == 4)
    res = S;
  else if (random == 5)
    res = T;
  else if (random == 6)
    res = Z;

  return res;
}

void record(GameInfo_t *game_info, std::string path) {
  std::ifstream inf(path);
  inf >> game_info->high_score;
  if (game_info->score >= game_info->high_score) {
    game_info->high_score = game_info->score;
    std::ofstream outf(path);
    outf << game_info->high_score;
  }
}

void copyFigureInField(GameInfo_t *game_info) {
  for (int i = 0; i < 4; ++i) {
    game_info->field[game_info->figure[i].rows][game_info->figure[i].cols] = 3;
  }
  for (int cols = 0; cols < 12; ++cols) {
    game_info->field[0][cols] = 1;
  }
}

void copyFigureInNext(GameInfo_t *game_info) {
  for (int i = 0; i < 4; ++i) {
    game_info
        ->next[game_info->figure_next[i].rows][game_info->figure_next[i].cols] =
        3;
  }
}

void copyFigure(Coord_t (*figure)[4], const Coord_t current[4]) {
  for (int i = 0; i < 4; ++i) {
    (*figure)[i].cols = current[i].cols;
    (*figure)[i].rows = current[i].rows;
  }
}

void start(GameInfo_t *game_info, const Figure_t random,
           const Figure_t random_next, std::string path) {
  zeroingGameInfo(game_info, path);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      game_info->next[i][j] = 0;
    }
  }

  initField(game_info);
  initFigure(&game_info->figure, random);
  initFigure(&game_info->figure_next, random_next);
  copyFigureInField(game_info);
  copyFigureInNext(game_info);
}
