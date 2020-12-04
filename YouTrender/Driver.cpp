#include "Driver.h"
#include "Widget.h"
#include "RandColorVisual.h"
#include "TextureData.h"
#include "EventQueue.h"
#include "Log.h"
#include "Constants.h"

Driver::Driver() :
	state_(STATE::NONE),
	introMovie_(nullptr),
	loader_(nullptr),
	uiPool_(nullptr),
	inputPanel_(nullptr)
{
	stateFunc_.emplace(STATE::INTRO_MOVIE, new IntroFunctions());
	stateFunc_.emplace(STATE::MAIN, new MainFunctions());

	this->switchState(STATE::INTRO_MOVIE);
}

Driver::~Driver()
{
	delete introMovie_;
	introMovie_ = nullptr;

	delete loader_;
	loader_ = nullptr;
	
	delete uiPool_;
	uiPool_ = nullptr;

	delete inputPanel_;
	inputPanel_ = nullptr;

	for (auto it = stateFunc_.begin(); it != stateFunc_.end(); it++)
	{
		delete it->second;
		it->second = nullptr;
	}

	stateFunc_.clear();
}

void Driver::switchState(STATE target)
{
	switch (state_)
	{
	case STATE::NONE:
		break;
	case STATE::INTRO_MOVIE:
		delete introMovie_;
		introMovie_ = nullptr;
		break;
	case STATE::MAIN:
		delete loader_;
		loader_ = nullptr;

		delete uiPool_;
		uiPool_ = nullptr;

		delete inputPanel_;
		inputPanel_ = nullptr;
		break;
	}

	state_ = target;

	switch (state_)
	{
	case STATE::NONE:
		break;
	case STATE::INTRO_MOVIE:
		introMovie_ = new IntroMovie(1.0f, 4, TextureData::getInstance()->getTexture(2));
		break;
	case STATE::MAIN:
		loader_ = new Loader();
		uiPool_ = new UIPool();
		inputPanel_ = new InputPanel(
			Global::SCREEN_WIDTH / 16.0f,
			Global::SCREEN_HEIGHT / 16.0f,
			"Data Analysis Setup",
			{
			std::make_pair<std::string, std::vector<std::string>>(
				"Location(s)",
				{
					"US",
					"CA",
					"DE",
					"FR",
					"GB",
					"IN",
					"JP",
					"KR",
					"MX",
					"RU"
				}),
			std::make_pair<std::string, std::vector<std::string>>(
				"Independent Variable",
				{
					"Category"
				}),
			std::make_pair<std::string, std::vector<std::string>>(
				"Dependent Variable",
				{
					"Views",
					"Likes",
					"Dislikes",
					"Comments"
				}),
			std::make_pair<std::string, std::vector<std::string>>(
				"Analysis Method",
				{
					"Hash Table",
					"BST"
				})
			},
			sf::Color(255, 0, 0, 255),
			sf::Color(0, 255, 0, 255));
		break;
	}
}

void Driver::updateOnTick()
{
	stateFunc_[state_]->updateOnTick(*this);
}

void Driver::updateOnMousePress()
{
	stateFunc_[state_]->updateOnMousePress(*this);
}

void Driver::updateOnMouseRelease()
{
	stateFunc_[state_]->updateOnMouseRelease(*this);
}

void Driver::updateOnMouseAxes()
{
	stateFunc_[state_]->updateOnMouseAxes(*this);
}

void Driver::updateOnKeyPress(const sf::Event &ev)
{
	stateFunc_[state_]->updateOnKeyPress(*this, ev);
}

void Driver::render(sf::RenderWindow &window) const
{
	stateFunc_.at(state_)->render(*this, window);
}

//-----------------------------------------------------------------------//
//                               INTRO                                   //
//-----------------------------------------------------------------------//

void Driver::IntroFunctions::updateOnTick(Driver &driver)
{
	driver.introMovie_->updateOnTick();

	if (driver.introMovie_->done())
		driver.switchState(STATE::MAIN);
}

void Driver::IntroFunctions::updateOnMousePress(Driver &driver)
{
	driver.introMovie_->updateOnMousePress();
}

void Driver::IntroFunctions::updateOnMouseRelease(Driver &driver)
{

}

void Driver::IntroFunctions::updateOnMouseAxes(Driver &driver)
{

}

void Driver::IntroFunctions::updateOnKeyPress(Driver &driver, const sf::Event &ev)
{
	driver.introMovie_->updateOnKeyPress();
}

void Driver::IntroFunctions::render(const Driver &driver, sf::RenderWindow &window) const
{
	driver.introMovie_->render(window);
}

//-----------------------------------------------------------------------//
//                                MAIN                                   //
//-----------------------------------------------------------------------//

void Driver::MainFunctions::updateOnTick(Driver &driver)
{
	driver.uiPool_->updateCleanup();
	EventQueue::getInstance()->dispatch();
	//driver.inputPanel_->updateOnTick();
}

void Driver::MainFunctions::updateOnMousePress(Driver &driver)
{
	driver.uiPool_->updateOnMousePress();
	driver.inputPanel_->updateOnMousePress();
}

void Driver::MainFunctions::updateOnMouseRelease(Driver &driver)
{
	driver.uiPool_->updateOnMouseRelease();
}

void Driver::MainFunctions::updateOnMouseAxes(Driver &driver)
{
	driver.uiPool_->updateOnMouseAxes();
}

void Driver::MainFunctions::updateOnKeyPress(Driver &driver, const sf::Event &ev)
{
	if (ev.key.code == sf::Keyboard::Key::N)
		driver.uiPool_->add(new Widget(Global::SCREEN_WIDTH / 2.0f, Global::SCREEN_HEIGHT / 2.0f,
			"RandColorVisual Test",
			new RandColorVisual(Global::SCREEN_WIDTH / 4, Global::SCREEN_HEIGHT / 4)));
}

void Driver::MainFunctions::render(const Driver &driver, sf::RenderWindow &window) const
{
	driver.inputPanel_->render(window);
	Log::getInstance()->render(window);
	driver.uiPool_->render(window);
}