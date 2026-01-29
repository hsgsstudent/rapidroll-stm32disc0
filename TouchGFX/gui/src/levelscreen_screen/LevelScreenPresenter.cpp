#include <gui/levelscreen_screen/LevelScreenPresenter.hpp>
#include <gui/levelscreen_screen/LevelScreenView.hpp>

LevelScreenPresenter::LevelScreenPresenter(LevelScreenView &v) : view(v) {}

void LevelScreenPresenter::activate() {}

void LevelScreenPresenter::deactivate() {}

void LevelScreenPresenter::setGameSpeed(int speed) {
  model->setGameSpeed(speed);
}
