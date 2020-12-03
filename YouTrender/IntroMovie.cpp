#include "IntroMovie.h"
#include "Constants.h"
#include "FontData.h"

IntroMovie::IntroMovie(float showSecs, unsigned char deltaAlpha, const sf::Texture &imgTexture) :
	img_(imgTexture),
	skipText_("[Press Any Key to Skip]", FontData::getInstance()->getMainFont(), 20U),
	state_(STATE::SHOW),
	showTimer_(showSecs),
	alpha_(255),
	deltaAlpha_(deltaAlpha),
	done_(false)
{
	float cX = (Global::SCREEN_WIDTH - imgTexture.getSize().x) / 2.0f;
	float cY = (Global::SCREEN_HEIGHT - imgTexture.getSize().y) / 2.0f;

	img_.setPosition(cX, cY);

	skipText_.setOrigin(skipText_.getLocalBounds().width / 2.0f, 0.0f);
	skipText_.setPosition(Global::SCREEN_WIDTH / 2.0f, Global::SCREEN_HEIGHT * 5.0f / 6.0f);
	skipText_.setFillColor(sf::Color());
}

IntroMovie::IntroMovie(float showSecs, FADE_SPEED fadeSpeed, const sf::Texture &imgTexture) :
	IntroMovie(showSecs, static_cast<uint8_t>(fadeSpeed), imgTexture)
{}

void IntroMovie::updateOnTick()
{
	switch (state_)
	{
	case STATE::SHOW:
		if (showTimer_.tick())
			state_ = STATE::FADE;
		break;
	case STATE::FADE:
		if (alpha_ <= deltaAlpha_)
			done_ = true;
		else
		{
			alpha_ -= deltaAlpha_;
			img_.setColor(sf::Color(255, 255, 255, alpha_));
		}
		break;
	}
}

void IntroMovie::updateOnMousePress()
{
	done_ = true;
}

void IntroMovie::updateOnKeyPress()
{
	done_ = true;
}

void IntroMovie::render(sf::RenderWindow &window) const
{
	window.draw(img_);
	window.draw(skipText_);
}

bool IntroMovie::done() const
{
	return done_;
}