#include <gui/levelscreen_screen/LevelScreenView.hpp>

#define GAME_SPEED_EASY 1
#define GAME_SPEED_MEDIUM 2
#define GAME_SPEED_HARD 3

LevelScreenView::LevelScreenView() : buttonCallback(this, &LevelScreenView::buttonCallbackHandler) {}

void LevelScreenView::setupScreen() {
  LevelScreenViewBase::setupScreen();
  EasyButton.setAction(buttonCallback);
  MediumButton.setAction(buttonCallback);
  HardButton.setAction(buttonCallback);
}

void LevelScreenView::tearDownScreen() {
  LevelScreenViewBase::tearDownScreen();
}

void LevelScreenView::buttonCallbackHandler(const touchgfx::AbstractButton &src) {
  if (&src == &EasyButton) {
    presenter->setGameSpeed(GAME_SPEED_EASY);
  } else if (&src == &MediumButton) {
    presenter->setGameSpeed(GAME_SPEED_MEDIUM);
  } else if (&src == &HardButton) {
    presenter->setGameSpeed(GAME_SPEED_HARD);
  }

  application().gotoHomeScreenScreenNoTransition();
}
