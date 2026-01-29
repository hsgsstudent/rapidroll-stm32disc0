#ifndef SCORESCREENVIEW_HPP
#define SCORESCREENVIEW_HPP

#include <gui/scorescreen_screen/ScoreScreenPresenter.hpp>
#include <gui_generated/scorescreen_screen/ScoreScreenViewBase.hpp>

class ScoreScreenView : public ScoreScreenViewBase {
public:
  ScoreScreenView();
  virtual ~ScoreScreenView() {}
  virtual void setupScreen();
  virtual void tearDownScreen();

protected:
};

#endif // SCORESCREENVIEW_HPP
