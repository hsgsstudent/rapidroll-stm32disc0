# Rapid Roll - Project Summary

## Features Implemented

### 1. Hardware Integration & Input Handling
- **Pin Mapping:** Configured GPIO pins for directional control (UP=PC15, DOWN=PC4, LEFT=PC14, RIGHT=PC8) with pull-down resistors.
- **Hardware Conflict Resolution:** Resolved a critical conflict where PC3 was being used as a button, which was actually the SDRAM Clock Enable (SDCKE0). Moved inputs to safe pins.
- **Input Polling:** Integrated hardware button state into the TouchGFX `Model::tick()` loop.

### 2. Game Mechanics
- **Gravity & Movement:** Implemented ball gravity where the ball falls faster than the screen scrolls (`gameSpeed + 3`).
- **Platform Scrolling:** Added upward scrolling logic for platforms and spikes based on the `gameSpeed` configured in the Level screen.
- **Horizontal Control:** Smooth ball movement between the brick walls using hardware button inputs.

### 3. Life & State Management
- **Life System:** Game starts with 2 lives, managed in the `Model`.
- **Life Loss Logic:** When the ball falls off the bottom edge:
  - Life count decrements.
  - UI updates dynamically (e.g., "x 1").
  - A 1-second (60 ticks) respawn delay is applied before the ball reappears.
- **Game Over:** When lives reach 0, a "Game Over" graphic appears, and all game movement/input is paused.
- **Game Reset:** Lives and game state are automatically reset to defaults whenever entering the Main Screen from the menu.

### 4. UI & Rendering
- **Score Screen Fixes:** Corrected rendering issues where scores were invisible due to zero-width text areas and missing font ranges for numeric wildcards.
- **Dynamic Wildcards:** Configured `texts.xml` and view logic to properly handle dynamic numeric updates for scores and lives.

## Files Modified

- `Core/Inc/main.h`: Updated GPIO pin definitions.
- `Core/Src/main.c`: Cleaned up hardware initialization logic.
- `TouchGFX/assets/texts/texts.xml`: Added numeric ranges to typography.
- `TouchGFX/gui/include/gui/model/Model.hpp` & `src/model/Model.cpp`: Implemented state persistence (lives, scores, speed).
- `TouchGFX/gui/include/gui/mainscreen_screen/MainScreenView.hpp` & `src/mainscreen_screen/MainScreenView.cpp`: Implemented game loop, gravity, and life-loss logic.
- `TouchGFX/gui/include/gui/mainscreen_screen/MainScreenPresenter.hpp` & `src/mainscreen_screen/MainScreenPresenter.cpp`: Wired model state to the view.
- `TouchGFX/gui/src/scorescreen_screen/ScoreScreenView.cpp`: Fixed dynamic score rendering.
