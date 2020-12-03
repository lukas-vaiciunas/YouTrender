#pragma once

#include <unordered_map>
#include "UIPool.h"
#include "Loader.h"
#include "IntroMovie.h"
#include "InputPanel.h"

class Driver
{
private:
	struct StateFunctions
	{
		virtual void updateOnTick(Driver &driver) = 0;
		virtual void updateOnMousePress(Driver &driver) = 0;
		virtual void updateOnMouseRelease(Driver &driver) = 0;
		virtual void updateOnMouseAxes(Driver &driver) = 0;
		virtual void updateOnKeyPress(Driver &driver, const sf::Event &ev) = 0;

		virtual void render(const Driver &driver, sf::RenderWindow &window) const = 0;
	};
	struct IntroFunctions : public StateFunctions
	{
		void updateOnTick(Driver &driver) override;
		void updateOnMousePress(Driver &driver) override;
		void updateOnMouseRelease(Driver &driver) override;
		void updateOnMouseAxes(Driver &driver) override;
		void updateOnKeyPress(Driver &driver, const sf::Event &ev) override;

		void render(const Driver &driver, sf::RenderWindow &window) const override;
	};
	struct MainFunctions : public StateFunctions
	{
		void updateOnTick(Driver &driver) override;
		void updateOnMousePress(Driver &driver) override;
		void updateOnMouseRelease(Driver &driver) override;
		void updateOnMouseAxes(Driver &driver) override;
		void updateOnKeyPress(Driver &driver, const sf::Event &ev) override;

		void render(const Driver &driver, sf::RenderWindow &window) const override;
	};

	enum class STATE
	{
		NONE,
		INTRO_MOVIE,
		MAIN
	};
	STATE state_;

	//INTRO_MOVIE
	IntroMovie *introMovie_;

	//MAIN
	Loader *loader_;
	UIPool *uiPool_;
	InputPanel *inputPanel_;

	std::unordered_map <STATE, StateFunctions *> stateFunc_;

	void switchState(STATE target);
public:
	Driver();
	~Driver();

	void updateOnTick();
	void updateOnMousePress();
	void updateOnMouseRelease();
	void updateOnMouseAxes();
	void updateOnKeyPress(const sf::Event &ev);

	void render(sf::RenderWindow &window) const;
};