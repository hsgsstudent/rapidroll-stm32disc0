#ifndef LEVELSCREENVIEW_HPP
#define LEVELSCREENVIEW_HPP

#include <gui/levelscreen_screen/LevelScreenPresenter.hpp>
#include <gui_generated/levelscreen_screen/LevelScreenViewBase.hpp>

class LevelScreenView : public LevelScreenViewBase {
public:
  LevelScreenView();
  virtual ~LevelScreenView() {}
  virtual void setupScreen();
  virtual void tearDownScreen();

protected:
  touchgfx::Callback<LevelScreenView, const touchgfx::AbstractButton &> buttonCallback;
  void buttonCallbackHandler(const touchgfx::AbstractButton &src);
};

#endif // LEVELSCREENVIEW_HPP
