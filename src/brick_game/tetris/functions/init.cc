#include "../tetris.h"

void initField(GameInfo_t *game_info) {
  for (int rows = 0; rows < 22; ++rows) {
    for (int cols = 0; cols < 12; ++cols) {
      if (rows == 0 || rows == 21)
        game_info->field[rows][cols] = 1;
      else if (cols == 0 || cols == 11)
        game_info->field[rows][cols] = 2;
      else
        game_info->field[rows][cols] = 0;
    }
  }
}

void initFigure(Coord_t (*figure)[4], const Figure_t figure_type) {
  switch (figure_type) {
    case I:
      (*figure)[0] = (Coord_t){1, 4};
      (*figure)[1] = (Coord_t){1, 5};
      (*figure)[2] = (Coord_t){1, 6};
      (*figure)[3] = (Coord_t){1, 7};
      break;
    case J:
      (*figure)[0] = (Coord_t){1, 5};
      (*figure)[1] = (Coord_t){2, 5};
      (*figure)[2] = (Coord_t){2, 6};
      (*figure)[3] = (Coord_t){2, 7};
      break;
    case L:
      (*figure)[0] = (Coord_t){1, 7};
      (*figure)[1] = (Coord_t){2, 5};
      (*figure)[2] = (Coord_t){2, 6};
      (*figure)[3] = (Coord_t){2, 7};
      break;
    case O:
      (*figure)[0] = (Coord_t){1, 5};
      (*figure)[1] = (Coord_t){1, 6};
      (*figure)[2] = (Coord_t){2, 5};
      (*figure)[3] = (Coord_t){2, 6};
      break;
    case S:
      (*figure)[0] = (Coord_t){2, 5};
      (*figure)[1] = (Coord_t){2, 6};
      (*figure)[2] = (Coord_t){1, 6};
      (*figure)[3] = (Coord_t){1, 7};
      break;
    case T:
      (*figure)[0] = (Coord_t){2, 5};
      (*figure)[1] = (Coord_t){2, 6};
      (*figure)[2] = (Coord_t){1, 6};
      (*figure)[3] = (Coord_t){2, 7};
      break;
    case Z:
      (*figure)[0] = (Coord_t){1, 5};
      (*figure)[1] = (Coord_t){1, 6};
      (*figure)[2] = (Coord_t){2, 6};
      (*figure)[3] = (Coord_t){2, 7};
      break;
  }
}