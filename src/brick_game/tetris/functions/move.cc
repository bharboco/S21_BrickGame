#include "../tetris.h"

void moveFigureHorizontal(GameInfo_t *game_info) {
  mashing(&game_info->field, *game_info);
  for (int i = 0; i < 4; ++i) {
    game_info->figure[i].cols += game_info->direction;
  }

  copyFigureInField(game_info);
}

void moveFigureDown(GameInfo_t *game_info) {
  mashing(&game_info->field, *game_info);

  for (int i = 0; i < 4; ++i) {
    game_info->figure[i].rows++;
  }
  game_info->shift_down++;

  copyFigureInField(game_info);
}

void mashing(int (*matrix)[22][12], const GameInfo_t game_info) {
  for (int i = 0; i < 4; ++i) {
    (*matrix)[game_info.figure[i].rows][game_info.figure[i].cols] = 0;
  }
}

void mashingNext(int (*matrix)[4][4], const GameInfo_t game_info) {
  for (int i = 0; i < 4; ++i) {
    (*matrix)[game_info.figure_next[i].rows][game_info.figure_next[i].cols] = 0;
  }
}

void rotateFigure(GameInfo_t *game_info, Coord_t (*figure)[4], Figure_t type) {
  if (type != O) {
    Coord_t tmp[4] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
    if (type != I) {
      for (int i = 0; i < 4; ++i) {
        if ((*figure)[i].cols - 5 + (-game_info->shift_horizontal) == 0 ||
            (*figure)[i].cols - 5 + (-game_info->shift_horizontal) == 2) {
          tmp[i].cols = 2 - (*figure)[i].rows + 5 -
                        (-game_info->shift_horizontal) +
                        (1 + game_info->shift_down);
          tmp[i].rows = (*figure)[i].cols + (1 + game_info->shift_down) - 5 +
                        (-game_info->shift_horizontal);
        } else if ((*figure)[i].rows - 1 - game_info->shift_down == 0 ||
                   (*figure)[i].rows - 1 - game_info->shift_down == 2) {
          tmp[i].rows = (*figure)[i].cols + (1 + game_info->shift_down) - 5 +
                        (-game_info->shift_horizontal);
          tmp[i].cols = 2 - (*figure)[i].rows + (1 + game_info->shift_down) +
                        5 - (-game_info->shift_horizontal);
        } else {
          tmp[i].cols = (*figure)[i].cols;
          tmp[i].rows = (*figure)[i].rows;
        }
      }
    } else
      rotateFigureI(game_info, &tmp);

    copyFigure(figure, tmp);
  }
}

void rotateFigureI(GameInfo_t *game_info, Coord_t (*tmp)[4]) {
  for (int i = 0; i < 4; ++i) {
    if (game_info->figure[i].cols - 4 + (-game_info->shift_horizontal) == 0 ||
        game_info->figure[i].cols - 4 + (-game_info->shift_horizontal) == 1 ||
        game_info->figure[i].cols - 4 + (-game_info->shift_horizontal) == 3 ||
        game_info->figure[i].cols - 4 + (-game_info->shift_horizontal) == 4) {
      (*tmp)[i].cols = 2 - game_info->figure[i].rows + 5 -
                       (-game_info->shift_horizontal) +
                       (1 + game_info->shift_down);
      (*tmp)[i].rows = game_info->figure[i].cols + (1 + game_info->shift_down) -
                       5 + (-game_info->shift_horizontal);
    } else if (game_info->figure[i].rows - game_info->shift_down == 0 ||
               game_info->figure[i].rows - game_info->shift_down == 1 ||
               game_info->figure[i].rows - game_info->shift_down == 3 ||
               game_info->figure[i].rows - game_info->shift_down == 4) {
      (*tmp)[i].rows = game_info->figure[i].cols + (1 + game_info->shift_down) -
                       5 + (-game_info->shift_horizontal);
      (*tmp)[i].cols = 2 - game_info->figure[i].rows +
                       (1 + game_info->shift_down) + 5 -
                       (-game_info->shift_horizontal);
    } else {
      (*tmp)[i].cols = game_info->figure[i].cols;
      (*tmp)[i].rows = game_info->figure[i].rows;
    }
  }
}

void userInput(UserAction_t *user_action, int key) {
  if (key == 'p' || key == 'P')
    *user_action = Pause;
  else if (key == 'q' || key == 'Q')
    *user_action = Terminate;
  else if (key == 0404)
    *user_action = Left;
  else if (key == 0405)
    *user_action = Right;
  else if (key == 0402)
    *user_action = Down;
  else if (key == 32)
    *user_action = Action;
  else if (key == 'b' || key == 'B')
    *user_action = Boost;
  else
    *user_action = Start;
}

GameInfo_t updateCurrentState(GameInfo_t *game_info, UserAction_t *user_action,
                              int *count, int *n, Figure_t *random,
                              Figure_t *random_next, std::string path) {
  if (*user_action == Pause) {
    game_info->pause = !game_info->pause, *user_action = Start;
  } else if (!game_info->pause) {
    if (*user_action == Left)
      game_info->direction = -1, game_info->shift_horizontal--,
      *user_action = Start;
    if (*user_action == Right)
      game_info->direction = 1, game_info->shift_horizontal++,
      *user_action = Start;
    if (game_info->shift_horizontal < -4) game_info->shift_horizontal = -4;
    if (game_info->shift_horizontal > 3) game_info->shift_horizontal = 3;

    if (!checkColissionHorizontal(game_info)) moveFigureHorizontal(game_info);

    if (*user_action == Action && !checkColissionRotate(game_info, *random)) {
      mashing(&game_info->field, *game_info);
      rotateFigure(game_info, &game_info->figure, *random);
      *user_action = Start;
    }
    if (*user_action == Boost) *n = 1, *user_action = Start;
    if (*user_action == Down)
      game_info->previos_speed = game_info->speed, game_info->speed = 5,
      *user_action = Start;
  }
  copyFigureInField(game_info);
  if (*count == 19 || *n == 1) {
    if (!checkColissionBottom(game_info) && !game_info->pause)
      moveFigureDown(game_info);
    else if (!game_info->pause) {
      if (game_info->speed == 5) game_info->speed = game_info->previos_speed;
      deleteLines(game_info, path);
      *random = *random_next;
      copyFigure(&game_info->figure, game_info->figure_next);
      *random_next = randomGenerate();
      mashingNext(&game_info->next, *game_info);
      initFigure(&game_info->figure_next, *random_next);
      copyFigureInNext(game_info);
      *user_action = checkGameOver(*game_info) == 1 ? Terminate : Start;
    }
  }
  return *game_info;
}