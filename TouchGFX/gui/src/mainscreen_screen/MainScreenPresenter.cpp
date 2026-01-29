#include <gui/mainscreen_screen/MainScreenPresenter.hpp>
#include <gui/mainscreen_screen/MainScreenView.hpp>

MainScreenPresenter::MainScreenPresenter(MainScreenView &v) : view(v) {}

void MainScreenPresenter::activate() {
  model->resetGame();
  model->setScore(0);
}

void MainScreenPresenter::deactivate() {}

void MainScreenPresenter::handleButtonInput(uint8_t keys) {
  view.updateBallPosition(keys);
}

int MainScreenPresenter::getGameSpeed() {
  return model->getGameSpeed();
}

int MainScreenPresenter::getLives() {
  return model->getLives();
}

void MainScreenPresenter::loseLife() {
  model->decrementLives();
}

void MainScreenPresenter::gainLife() {
  model->incrementLives();
}

int MainScreenPresenter::getScore() {
  return model->getScore();
}

void MainScreenPresenter::incrementScore(int s) {
  model->incrementScore(s);
}

void MainScreenPresenter::saveScore() {
  model->saveCurrentScore();
}
