#include <gui/scorescreen_screen/ScoreScreenPresenter.hpp>
#include <gui/scorescreen_screen/ScoreScreenView.hpp>

ScoreScreenPresenter::ScoreScreenPresenter(ScoreScreenView &v) : view(v) {}

void ScoreScreenPresenter::activate() {}

void ScoreScreenPresenter::deactivate() {}

int ScoreScreenPresenter::getBestScore() {
  return model->getBestScore();
}

int ScoreScreenPresenter::getLastScore() {
  return model->getLastScore();
}
