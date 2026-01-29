#include <gui/scorescreen_screen/ScoreScreenView.hpp>

ScoreScreenView::ScoreScreenView() {}

void ScoreScreenView::setupScreen() {
  ScoreScreenViewBase::setupScreen();
  Unicode::snprintf(BestScoreBuffer, BESTSCORE_SIZE, "%d", presenter->getBestScore());
  BestScore.resizeToCurrentText();
  BestScore.invalidate();
  Unicode::snprintf(LastScoreBuffer, LASTSCORE_SIZE, "%d", presenter->getLastScore());
  LastScore.resizeToCurrentText();
  LastScore.invalidate();
}

void ScoreScreenView::tearDownScreen() {
  ScoreScreenViewBase::tearDownScreen();
}
