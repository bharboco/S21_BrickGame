#ifndef _TETRIS_H_
#define _TETRIS_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <string>

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Boost,
  Down,
  Action
} UserAction_t;

typedef enum {
  I,  // ----
  J,  // |___
  L,  // ___|
  O,  // #
  S,  // _|-
  T,  // _|_
  Z   // -|_
} Figure_t;

typedef struct {
  int rows;
  int cols;
} Coord_t;

typedef struct {
  int field[22][12];
  int next[4][4];
  Coord_t figure[4];
  Coord_t figure_next[4];
  int score;
  int high_score;
  int level;
  int speed;
  int previos_speed;
  int pause;
  int direction;
  int shift_down;
  int shift_horizontal;
} GameInfo_t;

void userInput(UserAction_t *user_action, const int key);

GameInfo_t updateCurrentState(GameInfo_t *game_info, UserAction_t *user_action,
                              int *count, int *n, Figure_t *random,
                              Figure_t *random_next, std::string path);
// FUNCTIONS
void initField(GameInfo_t *game_info);
void initFigure(Coord_t (*figure)[4], const Figure_t figure_type);
void initInput(const int key, UserAction_t *user_action);

void moveFigureDown(GameInfo_t *game_info);
void moveFigureHorizontal(GameInfo_t *game_info);
void mashing(int (*matrix)[22][12], const GameInfo_t game_info);
void mashingNext(int (*matrix)[4][4], const GameInfo_t game_info);
void rotateFigure(GameInfo_t *game_info, Coord_t (*figure)[4], Figure_t type);
void rotateFigureI(GameInfo_t *game_info, Coord_t (*tmp)[4]);

bool checkColissionBottom(GameInfo_t *game_info);
bool checkColissionHorizontal(GameInfo_t *game_info);
bool checkColissionRotate(GameInfo_t *game_info, Figure_t type);
bool checkGameOver(const GameInfo_t game_info);
bool checkSelf(const GameInfo_t game_info, int x, int y);

// TOOLS
void zeroingGameInfo(GameInfo_t *game_info, std::string path);
Figure_t randomGenerate();
int getMinCol(const GameInfo_t game_info);
int getMaxCol(const GameInfo_t game_info);
void deleteLines(GameInfo_t *game_info, std::string path);
void moveDeleteLines(GameInfo_t *game_info, const int count_full_line,
                     const int rows);
void changeScore(GameInfo_t *game_info, const int count_full_line);
void record(GameInfo_t *game_info, std::string path);
void copyFigureInField(GameInfo_t *game_info);
void copyFigureInNext(GameInfo_t *game_info);
void copyFigure(Coord_t (*figure)[4], const Coord_t current[4]);
void start(GameInfo_t *game_info, const Figure_t random,
           const Figure_t random_next, std::string path);

#endif  // _TETRIS_H_
