#include "../tetris.h"

bool checkColissionHorizontal(GameInfo_t *game_info) {
  bool res = false;
  for (int i = 0; i < 4; ++i) {
    if (game_info->direction == -1 &&
        game_info->figure[i].cols == getMinCol(*game_info) &&
        game_info->field[game_info->figure[i].rows]
                        [game_info->figure[i].cols - 1] == 3) {
      res = true;
    } else if (game_info->direction == 1 &&
               game_info->figure[i].cols == getMaxCol(*game_info) &&
               game_info->field[game_info->figure[i].rows]
                               [game_info->figure[i].cols + 1] == 3) {
      res = true;
    }
    if (game_info->figure[i].cols + game_info->direction == 0 ||
        game_info->figure[i].cols + game_info->direction == 11) {
      game_info->direction = 0;
    }
  }
  return res;
}

bool checkColissionBottom(GameInfo_t *game_info) {
  bool res = false;

  for (int i = 0; i < 4; i++) {
    if ((!checkSelf(*game_info, game_info->figure[i].rows + 1,
                    game_info->figure[i].cols) &&
         game_info->field[game_info->figure[i].rows + 1]
                         [game_info->figure[i].cols] == 3) ||
        game_info->figure[i].rows == 20) {
      res = true;
      game_info->shift_down = 0;
      game_info->shift_horizontal = 0;
    }
  }

  return res;
}

bool checkColissionRotate(GameInfo_t *game_info, Figure_t type) {
  mashing(&game_info->field, *game_info);

  Coord_t tmp[4];
  copyFigure(&tmp, game_info->figure);

  rotateFigure(game_info, &tmp, type);

  for (int i = 0; i < 4; ++i) {
    if (game_info->field[tmp[i].rows][tmp[i].cols] == 3 || tmp[i].rows > 20 ||
        tmp[i].cols <= 0 || tmp[i].cols >= 11) {
      return true;
    }
  }

  copyFigureInField(game_info);

  return false;
}

bool checkGameOver(const GameInfo_t game_info) {
  for (int i = 0; i < 4; ++i) {
    if (game_info.field[game_info.figure[i].rows][game_info.figure[i].cols] ==
        3) {
      return true;
    }
  }
  return false;
}

bool checkSelf(const GameInfo_t game_info, int rows, int cols) {
  for (int i = 0; i < 4; ++i) {
    if (game_info.figure[i].rows == rows && game_info.figure[i].cols == cols) {
      return true;
    }
  }
  return false;
}