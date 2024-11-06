#ifndef _SNAKE_
#define _SNAKE_

#include <unistd.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

namespace s21 {
class Snake {
 public:
  struct Coordinate {
    int x, y;
    bool operator==(Coordinate other) {
      return x == other.x && y == other.y ? 1 : 0;
    }
  };

  enum Direction { UP, DOWN, LEFT, RIGHT };

 private:
  std::vector<Coordinate> body_;
  int length_ = 0;
  Coordinate food_;
  Direction direction_;
  bool gameStatus_ = true;
  bool pause_ = false;
  int points_ = 0;
  int record_ = 0;
  int speed_ = 500000;
  int lvl_ = 1;

  void generateFood() {
    do {
      food_.x = rand() % 10 + 1;
      food_.y = rand() % 20 + 1;
    } while (checkingAppleGeneration(food_));
  }

  bool checkingAppleGeneration(Coordinate food) {
    for (auto itr = body_.begin(); itr != body_.end(); ++itr) {
      if (food == *itr) return true;
    }
    return false;
  }

  void moveVector(Coordinate* head) {
    if (direction_ == UP) {
      head->y--;
    } else if (direction_ == DOWN) {
      head->y++;
    } else if (direction_ == LEFT) {
      head->x--;
    } else if (direction_ == RIGHT) {
      head->x++;
    }
  }

  void move(std::string path) {
    Coordinate head = body_.back();
    moveVector(&head);

    body_.push_back(head);
    body_.erase(body_.begin());
    if (head.x == food_.x && head.y == food_.y) {
      body_.insert(body_.begin(), body_.front());
      length_++;
      points_++;
      speedIncrease();
      generateFood();
    }
    saveRecord(path);
  };

  bool checkCollision() {
    Coordinate head = body_.back();
    if (head.x <= 0 || head.x >= 11 || head.y <= 0 || head.y >= 21) {
      return true;
    }
    for (auto itr = body_.begin(); itr != body_.end() - 1; ++itr) {
      if (head == *itr) {
        return true;
      }
    }
    return false;
  }

  void speedIncrease() {
    if (lvl_ <= 9) {
      if (points_ % 5 == 0) {
        speed_ = speed_ - 30000;
        lvl_++;
      }
    }
  }

  void saveRecord(std::string path) {
    std::ifstream inf(path);
    if (inf.is_open()) {
      inf >> record_;
      if (points_ > record_) {
        record_ = points_;
        std::ofstream outf(path);
        outf << record_;
      }
      inf.close();
    } else {
      std::cout << "Не удалось открыть файл для записи рекорда." << std::endl;
    }
  }

  void changeDirection(char key) {
    if (key == 'd') {
      if (direction_ == UP) {
        direction_ = RIGHT;
      } else if (direction_ == RIGHT) {
        direction_ = DOWN;
      } else if (direction_ == DOWN) {
        direction_ = LEFT;
      } else if (direction_ == LEFT) {
        direction_ = UP;
      }
    } else if (key == 'a') {
      if (direction_ == UP) {
        direction_ = LEFT;
      } else if (direction_ == LEFT) {
        direction_ = DOWN;
      } else if (direction_ == DOWN) {
        direction_ = RIGHT;
      } else if (direction_ == RIGHT) {
        direction_ = UP;
      }
    }
  }

 public:
  Snake() : length_(4), direction_(UP), gameStatus_(false) {
    srand(time(0));
    generateFood();
    for (int i = 0; i < length_; ++i) {
      body_.push_back({4 + i, 10});
    }
  };

  int getMaxScore() { return record_; }

  int getScore() { return points_; }

  std::vector<Coordinate>& getBody() { return body_; }

  Coordinate& getFood() { return food_; }

  Direction& getDirection() { return direction_; }

  bool getStatusGame() { return gameStatus_; }

  void setStatusGame() { gameStatus_ = !gameStatus_; }

  bool getCheckCollision() { return checkCollision(); }

  void moveSnake(std::string path) { move(path); }

  int getLvl() { return lvl_; }

  int getSpeed() { return speed_; }

  bool getPause() { return pause_; }

  void setPause() { pause_ = !pause_; }

  void setChangeDirection(char key) { return changeDirection(key); }
};
}  // namespace s21

#endif