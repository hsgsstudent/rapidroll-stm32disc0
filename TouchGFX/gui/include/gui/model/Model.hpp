#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model {
public:
  Model();

  void bind(ModelListener *listener) {
    modelListener = listener;
  }

  void tick();

  int getBestScore() {
    return bestScore;
  }
  void setBestScore(int score) {
    bestScore = score;
  }

  int getLastScore() {
    return lastScore;
  }
  void setLastScore(int score) {
    lastScore = score;
  }

  int getGameSpeed() {
    return gameSpeed;
  }
  void setGameSpeed(int speed) {
    gameSpeed = speed;
  }

  int getLives() {
    return lives;
  }
  void setLives(int l) {
    lives = l;
  }
  void decrementLives() {
    if (lives > 0)
      lives--;
  }
  void incrementLives() {
    if (lives < 10)
      lives++;
  }

  int getScore() {
    return score;
  }
  void setScore(int s) {
    score = s;
  }
  void incrementScore(int s) {
    score += s;
  }

  void saveCurrentScore() {
    lastScore = score;
    if (score > bestScore) {
      bestScore = score;
    }
  }

  void resetGame() {
    lives = 3;
    score = 0;
  }

protected:
  ModelListener *modelListener;

  int bestScore;
  int lastScore;
  int gameSpeed;
  int lives;
  int score;
};

#endif // MODEL_HPP