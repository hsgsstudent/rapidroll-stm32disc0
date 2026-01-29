#ifndef SCORESCREENPRESENTER_HPP
#define SCORESCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ScoreScreenView;

class ScoreScreenPresenter : public touchgfx::Presenter, public ModelListener {
public:
  ScoreScreenPresenter(ScoreScreenView &v);

  /**
   * The activate function is called automatically when this screen is "switched in"
   * (ie. made active). Initialization logic can be placed here.
   */
  virtual void activate();

  /**
   * The deactivate function is called automatically when this screen is "switched out"
   * (ie. made inactive). Teardown functionality can be placed here.
   */
  virtual void deactivate();

  virtual ~ScoreScreenPresenter() {}

  int getBestScore();
  int getLastScore();

private:
  ScoreScreenPresenter();

  ScoreScreenView &view;
};

#endif // SCORESCREENPRESENTER_HPP
