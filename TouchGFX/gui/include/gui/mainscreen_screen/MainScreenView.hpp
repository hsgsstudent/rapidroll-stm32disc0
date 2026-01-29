#ifndef MAINSCREENVIEW_HPP
#define MAINSCREENVIEW_HPP

#include <gui/mainscreen_screen/MainScreenPresenter.hpp>
#include <gui_generated/mainscreen_screen/MainScreenViewBase.hpp>

class MainScreenView : public MainScreenViewBase {
public:
  MainScreenView();
  virtual ~MainScreenView() {}
  virtual void setupScreen();
  virtual void tearDownScreen();
  virtual void handleTickEvent();

  void updateBallPosition(uint8_t keys);

protected:
  static const int NUM_PLATFORMS = 5;
  touchgfx::Image platformPool[NUM_PLATFORMS];
  bool isSpike[NUM_PLATFORMS];

  touchgfx::Image lifePowerUp;
  int lifeUpPlatformIdx; // Index of platform it's attached to, -1 if none

  touchgfx::Image speedUpPowerUp;
  int speedUpPlatformIdx;

  touchgfx::Image slowPowerUp;
  int slowPlatformIdx;

  touchgfx::Image shieldPowerUp;
  int shieldPlatformIdx;

  touchgfx::Image scoreUpPowerUp;
  int scoreUpPlatformIdx;

  int respawnTimer;
  int speedEffectTimer; // Ticks remaining for speed effect
  int shieldTimer; // Ticks remaining for shield
  int scoreUpTimer; // Ticks remaining for double score

  bool isBallFast;
  bool isBallSlow;
  bool isShieldActive;
  bool isScoreDoubled;

  int spikeChainCount;
  int platformChainCount;
  int pixelsFallen;
  int lastAwardedFallPoints;

  void recyclePlatform(int index, int lastY);
  void handleLifeLost();
};

#endif // MAINSCREENVIEW_HPP
