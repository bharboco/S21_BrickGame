#include "../brick_game/tetris/tetris.h"
#include "gtest/gtest.h"

void compareFigure(GameInfo_t game_info, GameInfo_t res) {
  for (int i = 0; i < 4; ++i) {
    EXPECT_EQ(res.figure[i].rows, game_info.figure[i].rows);
    EXPECT_EQ(res.figure[i].cols, game_info.figure[i].cols);
  }
}

TEST(Input, Q) {
  UserAction_t user_action = Start;
  userInput(&user_action, 'q');

  UserAction_t res = Terminate;

  EXPECT_EQ(res, user_action);
}

TEST(Input, P) {
  UserAction_t user_action = Start;
  userInput(&user_action, 'p');

  UserAction_t res = Pause;

  EXPECT_EQ(res, user_action);
}

TEST(Input, Left) {
  UserAction_t user_action = Start;
  userInput(&user_action, 0404);

  UserAction_t res = Left;

  EXPECT_EQ(res, user_action);
}

TEST(Input, Right) {
  UserAction_t user_action = Start;
  userInput(&user_action, 0405);

  UserAction_t res = Right;

  EXPECT_EQ(res, user_action);
}

TEST(Input, Down) {
  UserAction_t user_action = Start;
  userInput(&user_action, 0402);

  UserAction_t res = Down;

  EXPECT_EQ(res, user_action);
}

TEST(Input, Space) {
  UserAction_t user_action = Start;
  userInput(&user_action, 32);

  UserAction_t res = Action;

  EXPECT_EQ(res, user_action);
}

TEST(Input, B) {
  UserAction_t user_action = Start;
  userInput(&user_action, 'b');

  UserAction_t res = Boost;

  EXPECT_EQ(res, user_action);
}

TEST(Input, Invalid) {
  UserAction_t user_action = Start;
  userInput(&user_action, 'c');

  UserAction_t res = Start;

  EXPECT_EQ(res, user_action);
}

TEST(Move, Down) {
  GameInfo_t game_info, res;
  UserAction_t user_action = Start;
  Figure_t random = Z;
  Figure_t random_next = L;
  int count = 19, n = 1;
  start(&game_info, random, random_next, "../brick_game/tetris/record.txt");
  start(&res, random, random_next, "../brick_game/tetris/record.txt");
  updateCurrentState(&game_info, &user_action, &count, &n, &random,
                     &random_next, "../brick_game/tetris/record.txt");

  moveFigureDown(&res);

  compareFigure(game_info, res);
}

TEST(Move, Left) {
  GameInfo_t game_info, res;
  UserAction_t user_action = Left;
  Figure_t random = I;
  Figure_t random_next = J;
  int count = 0, n = 0;
  start(&game_info, random, random_next, "../brick_game/tetris/record.txt");
  start(&res, random, random_next, "../brick_game/tetris/record.txt");
  updateCurrentState(&game_info, &user_action, &count, &n, &random,
                     &random_next, "../brick_game/tetris/record.txt");

  res.direction = -1;
  for (int i = 0; i < 4; ++i) res.figure[i].cols += res.direction;

  compareFigure(game_info, res);
}

TEST(Move, Right) {
  GameInfo_t game_info, res;
  UserAction_t user_action = Right;
  Figure_t random = O;
  Figure_t random_next = S;
  int count = 0, n = 0;
  start(&game_info, random, random_next, "../brick_game/tetris/record.txt");
  start(&res, random, random_next, "../brick_game/tetris/record.txt");
  updateCurrentState(&game_info, &user_action, &count, &n, &random,
                     &random_next, "../brick_game/tetris/record.txt");

  res.direction = 1;
  for (int i = 0; i < 4; ++i) res.figure[i].cols += res.direction;

  compareFigure(game_info, res);
}

TEST(Move, Rotate) {
  GameInfo_t game_info, res;
  UserAction_t user_action = Action;
  Figure_t random = T;
  Figure_t random_next = Z;
  int count = 0, n = 0;
  start(&game_info, random, random_next, "../brick_game/tetris/record.txt");
  start(&res, random, random_next, "../brick_game/tetris/record.txt");
  updateCurrentState(&game_info, &user_action, &count, &n, &random,
                     &random_next, "../brick_game/tetris/record.txt");

  rotateFigure(&res, &res.figure, random);

  compareFigure(game_info, res);
}

TEST(Move, RotateI) {
  GameInfo_t game_info, res;
  UserAction_t user_action = Action;
  Figure_t random = I;
  Figure_t random_next = Z;
  int count = 0, n = 0;
  start(&game_info, random, random_next, "../brick_game/tetris/record.txt");
  start(&res, random, random_next, "../brick_game/tetris/record.txt");
  updateCurrentState(&game_info, &user_action, &count, &n, &random,
                     &random_next, "../brick_game/tetris/record.txt");

  rotateFigure(&res, &res.figure, random);

  compareFigure(game_info, res);
}

TEST(Move, Pause) {
  GameInfo_t game_info, res;
  UserAction_t user_action = Pause;
  Figure_t random = I;
  Figure_t random_next = Z;
  int count = 0, n = 0;
  start(&game_info, random, random_next, "../brick_game/tetris/record.txt");
  start(&res, random, random_next, "../brick_game/tetris/record.txt");
  updateCurrentState(&game_info, &user_action, &count, &n, &random,
                     &random_next, "../brick_game/tetris/record.txt");

  compareFigure(game_info, res);
}

TEST(Check, DeleteLines) {
  GameInfo_t game_info;
  UserAction_t user_action = Start;
  Figure_t random = I;
  Figure_t random_next = Z;
  int count = 19, n = 1;
  start(&game_info, random, random_next, "../brick_game/tetris/record.txt");

  for (int i = 0; i < 3; ++i) game_info.figure[i].rows = 20;
  for (int cols = 1; cols < 11; ++cols)
    game_info.field[20][cols] = 3;  // 1 full line
  updateCurrentState(&game_info, &user_action, &count, &n, &random,
                     &random_next, "../brick_game/tetris/record.txt");

  for (int cols = 1; cols < 11; ++cols) {  // 2 full line
    game_info.field[19][cols] = 3;
    game_info.field[20][cols] = 3;
  }
  updateCurrentState(&game_info, &user_action, &count, &n, &random,
                     &random_next, "../brick_game/tetris/record.txt");

  for (int cols = 1; cols < 11; ++cols) {  // 3 full line
    game_info.field[18][cols] = 3;
    game_info.field[19][cols] = 3;
    game_info.field[20][cols] = 3;
  }
  updateCurrentState(&game_info, &user_action, &count, &n, &random,
                     &random_next, "../brick_game/tetris/record.txt");

  for (int cols = 1; cols < 11; ++cols) {  // 4 full line
    game_info.field[17][cols] = 3;
    game_info.field[18][cols] = 3;
    game_info.field[19][cols] = 3;
    game_info.field[20][cols] = 3;
  }
  updateCurrentState(&game_info, &user_action, &count, &n, &random,
                     &random_next, "../brick_game/tetris/record.txt");

  for (int cols = 1; cols < 11; ++cols) EXPECT_EQ(game_info.field[20][cols], 0);
}