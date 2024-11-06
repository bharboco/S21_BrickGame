#ifndef _FRONTEND_TETRIS_H_
#define _FRONTEND_TETRIS_H_

#include <ncurses.h>

#include "../../../brick_game/tetris/tetris.h"

#define WIDTH 12
#define HEIGHT 22

void drawField(const GameInfo_t game_info, const UserAction_t user_action);
void drawNext(const GameInfo_t game_info);
void drawBoard(const GameInfo_t game_info, const UserAction_t user_action);
int gameLoop();
void consoleTetris();

#endif  // _FRONTEND_TETRIS_H_