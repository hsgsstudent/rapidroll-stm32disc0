#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>
#include <stdint.h>

class ModelListener {
public:
  ModelListener() : model(0) {}

  virtual ~ModelListener() {}

  virtual void handleButtonInput(uint8_t keys) {}

  void bind(Model *m) {
    model = m;
  }

protected:
  Model *model;
};

#endif // MODELLISTENER_HPP
