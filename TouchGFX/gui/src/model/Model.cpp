#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#ifndef SIMULATOR
#include "main.h"
#endif

Model::Model() : modelListener(0), bestScore(0), lastScore(0), gameSpeed(2), lives(3), score(0) {}

void Model::tick() {
#ifndef SIMULATOR
  if (modelListener != 0) {
    modelListener->handleButtonInput(HAL_Get_Button_State());
  }
#endif
}