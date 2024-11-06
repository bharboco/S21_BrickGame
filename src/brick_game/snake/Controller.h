#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <memory>

#include "Snake.h"

namespace s21 {
class Controller {
 private:
  std::unique_ptr<s21::Snake> snake;

 public:
  Controller() : snake(new s21::Snake()) {}  //{ snake = new s21::Snake(); }

  int getMaxScore() { return snake->getMaxScore(); }

  int getScore() { return snake->getScore(); }

  std::vector<s21::Snake::Coordinate>& getBody() { return snake->getBody(); }

  s21::Snake::Coordinate& getFood() { return snake->getFood(); }

  s21::Snake::Direction& getDirection() { return snake->getDirection(); }

  void changeDirection(char key) { return snake->setChangeDirection(key); }

  bool getStatusGame() { return snake->getStatusGame(); }

  void setStatusGame() { snake->setStatusGame(); }

  bool getCheckCollision() { return snake->getCheckCollision(); }

  void moveSnake(std::string path) { snake->moveSnake(path); }

  int getLvl() { return snake->getLvl(); }

  int getSpeed() { return snake->getSpeed(); }

  bool getPause() { return snake->getPause(); }

  void setPause() { snake->setPause(); }
};

}  // namespace s21
#endif