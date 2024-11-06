#include "../brick_game/snake/Controller.h"
#include "../brick_game/snake/Snake.h"
#include "gtest/gtest.h"

TEST(ChangeDirection, RIGHT) {
  s21::Controller snake;
  s21::Snake snake2;
  s21::Snake::Direction b;
  b = snake2.RIGHT;
  snake.changeDirection('d');
  EXPECT_EQ(snake.getDirection(), b);

  b = snake2.DOWN;
  snake.changeDirection('d');
  EXPECT_EQ(snake.getDirection(), b);

  b = snake2.LEFT;
  snake.changeDirection('d');
  EXPECT_EQ(snake.getDirection(), b);

  b = snake2.UP;
  snake.changeDirection('d');
  EXPECT_EQ(snake.getDirection(), b);
}

TEST(ChangeDirection, LEFT) {
  s21::Controller snake;
  s21::Snake snake2;
  s21::Snake::Direction b;
  b = snake2.LEFT;
  snake.changeDirection('a');
  EXPECT_EQ(snake.getDirection(), b);

  b = snake2.DOWN;
  snake.changeDirection('a');
  EXPECT_EQ(snake.getDirection(), b);

  b = snake2.RIGHT;
  snake.changeDirection('a');
  EXPECT_EQ(snake.getDirection(), b);

  b = snake2.UP;
  snake.changeDirection('a');
  EXPECT_EQ(snake.getDirection(), b);
}

TEST(Eatfood, one) {
  s21::Controller snake;

  snake.getBody().back().x = 1, snake.getBody().back().y = 1;
  snake.getFood().x = 1, snake.getFood().y = 0;
  snake.moveSnake("s");
  EXPECT_EQ(snake.getScore(), 1);
  EXPECT_EQ(snake.getLvl(), 1);

  snake.getFood().x = 1, snake.getFood().y = -1;
  snake.moveSnake("s");
  EXPECT_EQ(snake.getScore(), 2);
  EXPECT_EQ(snake.getLvl(), 1);

  snake.getFood().x = 1, snake.getFood().y = -2;
  snake.moveSnake("s");
  EXPECT_EQ(snake.getScore(), 3);
  EXPECT_EQ(snake.getLvl(), 1);

  snake.getFood().x = 1, snake.getFood().y = -3;
  snake.moveSnake("s");
  EXPECT_EQ(snake.getScore(), 4);
  EXPECT_EQ(snake.getLvl(), 1);

  snake.getFood().x = 1, snake.getFood().y = -4;
  snake.moveSnake("s");
  EXPECT_EQ(snake.getScore(), 5);
  EXPECT_EQ(snake.getLvl(), 2);
}

TEST(Move, move) {
  s21::Controller snake;
  snake.getBody().back().x = 5, snake.getBody().back().y = 10;
  snake.moveSnake("s");
  EXPECT_EQ(snake.getBody().back().y, 9);

  snake.changeDirection('d');
  snake.moveSnake("s");
  EXPECT_EQ(snake.getBody().back().x, 6);

  snake.changeDirection('d');
  snake.moveSnake("s");
  EXPECT_EQ(snake.getBody().back().y, 10);

  snake.changeDirection('d');
  snake.moveSnake("s");
  EXPECT_EQ(snake.getBody().back().x, 5);
}

TEST(CheckCollision, one) {
  s21::Controller snake;
  snake.getBody().back().x = 0, snake.getBody().back().y = 0;
  EXPECT_EQ(snake.getCheckCollision(), true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}