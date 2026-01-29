#include <cstring>
#include <gui/mainscreen_screen/MainScreenView.hpp>
#include <images/BitmapDatabase.hpp>

#define RANDOM_POWERUP_PERCENT 5

// Simple LCG for RNG
static uint32_t next_rng = 1;
static int my_rand() {
  next_rng = next_rng * 1103515245 + 12345;
  return (uint32_t)(next_rng / 65536) % 32768;
}

MainScreenView::MainScreenView()
    : respawnTimer(0), spikeChainCount(0), platformChainCount(0), pixelsFallen(0), lastAwardedFallPoints(0),
      lifeUpPlatformIdx(-1), speedUpPlatformIdx(-1), slowPlatformIdx(-1), shieldPlatformIdx(-1),
      scoreUpPlatformIdx(-1), speedEffectTimer(0), shieldTimer(0), scoreUpTimer(0), isBallFast(false),
      isBallSlow(false), isShieldActive(false), isScoreDoubled(false) {}

void MainScreenView::setupScreen() {
  MainScreenViewBase::setupScreen();

  // Zero out buffers to stop score from previous game to appear in current game
  memset(xBuffer, 0, sizeof(xBuffer));
  memset(ScoreBuffer, 0, sizeof(ScoreBuffer));

  // Initialize UI to fresh game state (3 lives, 0 score)
  Unicode::snprintf(xBuffer, X_SIZE, "%d", 3);
  x.resizeToCurrentText();
  x.invalidate();

  Unicode::snprintf(ScoreBuffer, SCORE_SIZE, "%d", 0);
  Score.resizeToCurrentText();
  Score.invalidate();

  GameOver.setVisible(false);
  GameOver.invalidate();

  // Hide placeholders
  Platform.setVisible(false);
  Spike.setVisible(false);
  Shield.setVisible(false);
  ScoreUp.setVisible(false);
  SpeedUp.setVisible(false);
  Slow.setVisible(false);
  BlackBall.setVisible(false);

  // Initialize power-ups
  lifePowerUp.setBitmap(touchgfx::Bitmap(BITMAP_HEARTICON_ID));
  lifePowerUp.setVisible(false);
  add(lifePowerUp);
  lifeUpPlatformIdx = -1;

  speedUpPowerUp.setBitmap(touchgfx::Bitmap(BITMAP_SPEEDUP_ID));
  speedUpPowerUp.setVisible(false);
  add(speedUpPowerUp);
  speedUpPlatformIdx = -1;

  slowPowerUp.setBitmap(touchgfx::Bitmap(BITMAP_SLOW_ID));
  slowPowerUp.setVisible(false);
  add(slowPowerUp);
  slowPlatformIdx = -1;

  shieldPowerUp.setBitmap(touchgfx::Bitmap(BITMAP_SHIELD_ID));
  shieldPowerUp.setVisible(false);
  add(shieldPowerUp);
  shieldPlatformIdx = -1;

  scoreUpPowerUp.setBitmap(touchgfx::Bitmap(BITMAP_SCOREUP_ID));
  scoreUpPowerUp.setVisible(false);
  add(scoreUpPowerUp);
  scoreUpPlatformIdx = -1;

  speedEffectTimer = 0;
  shieldTimer = 0;
  scoreUpTimer = 0;
  isBallFast = false;
  isBallSlow = false;
  isShieldActive = false;
  isScoreDoubled = false;
  Ball.setBitmap(touchgfx::Bitmap(BITMAP_BALL_ID));

  // Initialize platform pool
  int gameSpeed = presenter->getGameSpeed();
  int spacingY = 50 + gameSpeed * 10;
  int currentY = 320;

  for (int i = 0; i < NUM_PLATFORMS; i++) {
    platformPool[i].setBitmap(touchgfx::Bitmap(BITMAP_PLATFORM_ID));
    add(platformPool[i]);
    isSpike[i] = false;

    // Initial placement
    recyclePlatform(i, currentY);
    currentY -= spacingY;
  }

  // Spawn ball
  Ball.setVisible(true);
  Ball.moveTo(platformPool[0].getX() + (platformPool[0].getWidth() - Ball.getWidth()) / 2,
              platformPool[0].getY() - Ball.getHeight());
  Ball.invalidate();

  respawnTimer = 0;
  pixelsFallen = 0;
  lastAwardedFallPoints = 0;
}

void MainScreenView::recyclePlatform(int index, int lastY) {
  int gameSpeed = presenter->getGameSpeed();
  int spacingY = 50 + gameSpeed * 10;

  // RNG platform between 15 and 225 - 60 = 165
  int minX = 15;
  int maxX = 165;
  int posX = minX + (my_rand() % (maxX - minX + 1));

  // Determine next platform
  bool nextIsSpike = false;
  if (spikeChainCount >= 2) {
    nextIsSpike = false;
  } else if (platformChainCount >= 10) {
    nextIsSpike = true;
  } else {
    // Random 20% spike
    nextIsSpike = (my_rand() % 5 == 0);
  }

  if (nextIsSpike) {
    // is spike
    platformPool[index].setBitmap(touchgfx::Bitmap(BITMAP_SPIKE_ID));
    isSpike[index] = true;
    spikeChainCount++;
    platformChainCount = 0;

    // no powerup
    if (lifeUpPlatformIdx == index) {
      lifeUpPlatformIdx = -1;
      lifePowerUp.setVisible(false);
      lifePowerUp.invalidate();
    }
    if (speedUpPlatformIdx == index) {
      speedUpPlatformIdx = -1;
      speedUpPowerUp.setVisible(false);
      speedUpPowerUp.invalidate();
    }
    if (slowPlatformIdx == index) {
      slowPlatformIdx = -1;
      slowPowerUp.setVisible(false);
      slowPowerUp.invalidate();
    }
    if (shieldPlatformIdx == index) {
      shieldPlatformIdx = -1;
      shieldPowerUp.setVisible(false);
      shieldPowerUp.invalidate();
    }
    if (scoreUpPlatformIdx == index) {
      scoreUpPlatformIdx = -1;
      scoreUpPowerUp.setVisible(false);
      scoreUpPowerUp.invalidate();
    }
  } else {
    platformPool[index].setBitmap(touchgfx::Bitmap(BITMAP_PLATFORM_ID));
    isSpike[index] = false;
    platformChainCount++;
    spikeChainCount = 0;

    // clear powerups
    if (lifeUpPlatformIdx == index) {
      lifeUpPlatformIdx = -1;
      lifePowerUp.setVisible(false);
      lifePowerUp.invalidate();
    }
    if (speedUpPlatformIdx == index) {
      speedUpPlatformIdx = -1;
      speedUpPowerUp.setVisible(false);
      speedUpPowerUp.invalidate();
    }
    if (slowPlatformIdx == index) {
      slowPlatformIdx = -1;
      slowPowerUp.setVisible(false);
      slowPowerUp.invalidate();
    }
    if (shieldPlatformIdx == index) {
      shieldPlatformIdx = -1;
      shieldPowerUp.setVisible(false);
      shieldPowerUp.invalidate();
    }
    if (scoreUpPlatformIdx == index) {
      scoreUpPlatformIdx = -1;
      scoreUpPowerUp.setVisible(false);
      scoreUpPowerUp.invalidate();
    }

    // Random gen powerup
    if (my_rand() % 100 < RANDOM_POWERUP_PERCENT) {
      int type = my_rand() % 5; // 0=Life, 1=SpeedUp, 2=Slow, 3=Shield, 4=ScoreUp
      if (type == 0) {
        lifeUpPlatformIdx = index;
        lifePowerUp.setVisible(true);
        lifePowerUp.setXY(posX + (60 - lifePowerUp.getWidth()) / 2, lastY + spacingY - lifePowerUp.getHeight());
        lifePowerUp.invalidate();
      } else if (type == 1) {
        speedUpPlatformIdx = index;
        speedUpPowerUp.setVisible(true);
        speedUpPowerUp.setXY(posX + (60 - speedUpPowerUp.getWidth()) / 2,
                             lastY + spacingY - speedUpPowerUp.getHeight());
        speedUpPowerUp.invalidate();
      } else if (type == 2) {
        slowPlatformIdx = index;
        slowPowerUp.setVisible(true);
        slowPowerUp.setXY(posX + (60 - slowPowerUp.getWidth()) / 2, lastY + spacingY - slowPowerUp.getHeight());
        slowPowerUp.invalidate();
      } else if (type == 3) {
        shieldPlatformIdx = index;
        shieldPowerUp.setVisible(true);
        shieldPowerUp.setXY(posX + (60 - shieldPowerUp.getWidth()) / 2, lastY + spacingY - shieldPowerUp.getHeight());
        shieldPowerUp.invalidate();
      } else {
        scoreUpPlatformIdx = index;
        scoreUpPowerUp.setVisible(true);
        scoreUpPowerUp.setXY(posX + (60 - scoreUpPowerUp.getWidth()) / 2,
                             lastY + spacingY - scoreUpPowerUp.getHeight());
        scoreUpPowerUp.invalidate();
      }
    }
  }

  platformPool[index].setXY(posX, lastY + spacingY);
  platformPool[index].invalidate();
}

void MainScreenView::tearDownScreen() {
  MainScreenViewBase::tearDownScreen();
}

void MainScreenView::updateBallPosition(uint8_t keymask) {
  if (presenter->getLives() == 0) // dead
    return;
  if (respawnTimer > 0) // waiting for respawn
    return;

  const uint8_t MSK_LEFT = 0x04;
  const uint8_t MSK_RIGHT = 0x08;

  int ballSpeed = 4;
  if (isBallFast)
    ballSpeed = 6;
  if (isBallSlow)
    ballSpeed = 2;

  const int minX = 15;  // Right edge of LeftBrickWall
  const int maxX = 225; // Left edge of RightBrickWall

  int currentX = Ball.getX();
  int ballWidth = Ball.getWidth();

  if (keymask & MSK_LEFT) {
    currentX -= ballSpeed;
    if (currentX < minX) {
      currentX = minX;
    }
  }
  if (keymask & MSK_RIGHT) {
    currentX += ballSpeed;
    if (currentX + ballWidth > maxX) {
      currentX = maxX - ballWidth;
    }
  }

  if (currentX != Ball.getX()) {
    Ball.moveTo(currentX, Ball.getY());
  }
}

void MainScreenView::handleLifeLost() {
  if (isShieldActive) {
    // shield gone, no life lost
    isShieldActive = false;
    shieldTimer = 0;
    Ball.setBitmap(touchgfx::Bitmap(BITMAP_BALL_ID));
    Ball.invalidate();
  } else {
    presenter->loseLife();
  }

  pixelsFallen = 0;
  lastAwardedFallPoints = 0;

  // Update Life Counter Display
  memset(xBuffer, 0, sizeof(xBuffer));
  Unicode::snprintf(xBuffer, X_SIZE, "%d", presenter->getLives());
  x.resizeToCurrentText();
  x.invalidate();

  Ball.setVisible(false);
  Ball.invalidate();

  if (presenter->getLives() == 0) {
    presenter->saveScore();
    GameOver.setVisible(true);
    GameOver.invalidate();
  } else {
    // Start Respawn Delay
    respawnTimer = 60;
  }
}

void MainScreenView::handleTickEvent() {
  if (presenter->getLives() == 0)
    return;

  int gameSpeed = presenter->getGameSpeed();

  if (respawnTimer > 0) {
    respawnTimer--;
    if (respawnTimer == 0) {
      // Time to respawn: Find a platform that is NOT a spike and is in the lower half (200-300px)
      int bestIdx = -1;
      for (int i = 0; i < NUM_PLATFORMS; i++) {
        if (!isSpike[i]) {
          int py = platformPool[i].getY();
          if (py >= 200 && py <= 300) {
            bestIdx = i;
            break;
          }
        }
      }

      // Fallback: If no platform in ideal range, just take the first safe one
      if (bestIdx == -1) {
        for (int i = 0; i < NUM_PLATFORMS; i++) {
          if (!isSpike[i]) {
            bestIdx = i;
            break;
          }
        }
      }

      if (bestIdx != -1) {
        Ball.setVisible(true);
        Ball.moveTo(platformPool[bestIdx].getX() + (platformPool[bestIdx].getWidth() - Ball.getWidth()) / 2,
                    platformPool[bestIdx].getY() - Ball.getHeight());
        Ball.invalidate();
      }
    }
  } else {
    int gravity = gameSpeed + 1;
    int ballY = Ball.getY() + gravity;
    int maxBallY = 320 - Ball.getHeight();

    if (ballY > maxBallY) {
      handleLifeLost();
      return;
    } else {
      Ball.moveTo(Ball.getX(), ballY);
    }

    int ballX = Ball.getX();
    int ballY_now = Ball.getY();
    int ballW = Ball.getWidth();
    int ballH = Ball.getHeight();
    bool grounded = false;

    // HeadSpike = dead
    if (ballY_now <= 34) {
      handleLifeLost();
      return;
    }

    // LifeUp
    if (lifeUpPlatformIdx != -1 && lifePowerUp.isVisible()) {
      if (Ball.getRect().intersect(lifePowerUp.getRect())) {
        presenter->gainLife();

        // Update display
        memset(xBuffer, 0, sizeof(xBuffer));
        Unicode::snprintf(xBuffer, X_SIZE, "%d", presenter->getLives());
        x.resizeToCurrentText();
        x.invalidate();

        lifePowerUp.setVisible(false);
        lifePowerUp.invalidate();
        lifeUpPlatformIdx = -1;
      }
    }

    // SpeedUp
    if (speedUpPlatformIdx != -1 && speedUpPowerUp.isVisible()) {
      if (Ball.getRect().intersect(speedUpPowerUp.getRect())) {
        isBallFast = true;
        isBallSlow = false;
        speedEffectTimer = 600; // 10 seconds at 60fps

        speedUpPowerUp.setVisible(false);
        speedUpPowerUp.invalidate();
        speedUpPlatformIdx = -1;
      }
    }

    // Slow
    if (slowPlatformIdx != -1 && slowPowerUp.isVisible()) {
      if (Ball.getRect().intersect(slowPowerUp.getRect())) {
        isBallSlow = true;
        isBallFast = false;
        speedEffectTimer = 600; // 10 seconds at 60fps

        slowPowerUp.setVisible(false);
        slowPowerUp.invalidate();
        slowPlatformIdx = -1;
      }
    }

    // Shield
    if (shieldPlatformIdx != -1 && shieldPowerUp.isVisible()) {
      if (Ball.getRect().intersect(shieldPowerUp.getRect())) {
        isShieldActive = true;
        shieldTimer = 600; // 10 seconds
        Ball.setBitmap(touchgfx::Bitmap(BITMAP_BLACKBALL_ID));
        Ball.invalidate();

        shieldPowerUp.setVisible(false);
        shieldPowerUp.invalidate();
        shieldPlatformIdx = -1;
      }
    }

    // ScoreUp
    if (scoreUpPlatformIdx != -1 && scoreUpPowerUp.isVisible()) {
      if (Ball.getRect().intersect(scoreUpPowerUp.getRect())) {
        isScoreDoubled = true;
        scoreUpTimer = 600; // 10 seconds

        scoreUpPowerUp.setVisible(false);
        scoreUpPowerUp.invalidate();
        scoreUpPlatformIdx = -1;
      }
    }

    // Update timers
    if (speedEffectTimer > 0) {
      speedEffectTimer--;
      if (speedEffectTimer == 0) {
        isBallFast = false;
        isBallSlow = false;
      }
    }
    if (shieldTimer > 0) {
      shieldTimer--;
      if (shieldTimer == 0) {
        isShieldActive = false;
        Ball.setBitmap(touchgfx::Bitmap(BITMAP_BALL_ID));
        Ball.invalidate();
      }
    }
    if (scoreUpTimer > 0) {
      scoreUpTimer--;
      if (scoreUpTimer == 0) {
        isScoreDoubled = false;
      }
    }

    // Platform or Spike collision logic
    for (int i = 0; i < NUM_PLATFORMS; i++) {
      int pX = platformPool[i].getX();
      int pY = platformPool[i].getY();
      int pW = platformPool[i].getWidth();
      int pH = platformPool[i].getHeight();

      if ((ballX + ballW > pX) && (ballX < pX + pW)) {
        if ((ballY_now + ballH >= pY) && (ballY_now + ballH <= pY + gameSpeed + 5)) {
          if (isSpike[i]) {
            handleLifeLost();
            return;
          } else {
            // Landed on a platform
            Ball.moveTo(ballX, pY - ballH);
            grounded = true;
            break;
          }
        }
      }
    }

    // Scoring logic
    if (!grounded) {
      pixelsFallen += gravity;

      int platformsPassed = pixelsFallen / 40; // if many platforms = extra points
      int currentTargetPoints = (pixelsFallen / 4); // 1 platform = 10pts
      if (platformsPassed > 0) {
        currentTargetPoints += (platformsPassed - 1);
      }

      int incrementalPoints = currentTargetPoints - lastAwardedFallPoints;

      // Score multiplier!
      if (isScoreDoubled)
        incrementalPoints *= 2;

      if (incrementalPoints > 0) {
        presenter->incrementScore(incrementalPoints);
        lastAwardedFallPoints = currentTargetPoints;

        // Update Score Display
        memset(ScoreBuffer, 0, sizeof(ScoreBuffer));
        Unicode::snprintf(ScoreBuffer, SCORE_SIZE, "%d", presenter->getScore());
        Score.resizeToCurrentText();
        Score.invalidate();
      }
    } else {
      pixelsFallen = 0;
      lastAwardedFallPoints = 0;
    }
  }

  // scrolling, recycling
  int topLimit = 22; // Below HeadSpike/ScoreBar
  int lowestY = 0;

  // Find the current lowest platform Y to calculate spacing for recycled ones
  for (int i = 0; i < NUM_PLATFORMS; i++) {
    if (platformPool[i].getY() > lowestY) {
      lowestY = platformPool[i].getY();
    }
  }

  for (int i = 0; i < NUM_PLATFORMS; i++) {
    int newY = platformPool[i].getY() - gameSpeed;

    if (newY < topLimit) {
      recyclePlatform(i, lowestY);
    } else {
      platformPool[i].moveTo(platformPool[i].getX(), newY);

      // Move powerup if attached
      if (lifeUpPlatformIdx == i && lifePowerUp.isVisible()) {
        lifePowerUp.moveTo(lifePowerUp.getX(), lifePowerUp.getY() - gameSpeed);
        if (lifePowerUp.getY() < topLimit) {
          lifePowerUp.setVisible(false);
          lifePowerUp.invalidate();
          lifeUpPlatformIdx = -1;
        }
      }
      if (speedUpPlatformIdx == i && speedUpPowerUp.isVisible()) {
        speedUpPowerUp.moveTo(speedUpPowerUp.getX(), speedUpPowerUp.getY() - gameSpeed);
        if (speedUpPowerUp.getY() < topLimit) {
          speedUpPowerUp.setVisible(false);
          speedUpPowerUp.invalidate();
          speedUpPlatformIdx = -1;
        }
      }
      if (slowPlatformIdx == i && slowPowerUp.isVisible()) {
        slowPowerUp.moveTo(slowPowerUp.getX(), slowPowerUp.getY() - gameSpeed);
        if (slowPowerUp.getY() < topLimit) {
          slowPowerUp.setVisible(false);
          slowPowerUp.invalidate();
          slowPlatformIdx = -1;
        }
      }
      if (shieldPlatformIdx == i && shieldPowerUp.isVisible()) {
        shieldPowerUp.moveTo(shieldPowerUp.getX(), shieldPowerUp.getY() - gameSpeed);
        if (shieldPowerUp.getY() < topLimit) {
          shieldPowerUp.setVisible(false);
          shieldPowerUp.invalidate();
          shieldPlatformIdx = -1;
        }
      }
      if (scoreUpPlatformIdx == i && scoreUpPowerUp.isVisible()) {
        scoreUpPowerUp.moveTo(scoreUpPowerUp.getX(), scoreUpPowerUp.getY() - gameSpeed);
        if (scoreUpPowerUp.getY() < topLimit) {
          scoreUpPowerUp.setVisible(false);
          scoreUpPowerUp.invalidate();
          scoreUpPlatformIdx = -1;
        }
      }
    }
  }
}
