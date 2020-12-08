#include "Driver.h"
#include "Mouse.h"
#include "Constants.h"

int main(void)
{
	sf::RenderWindow window(
		sf::VideoMode(Global::SCREEN_WIDTH, Global::SCREEN_HEIGHT),
		"YouTrender",
		sf::Style::Titlebar | sf::Style::Close);

	window.setFramerateLimit(Global::FPS_CAP);
	
	Driver driver;

	while (window.isOpen())
	{
		sf::Event ev;

		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (ev.type == sf::Event::MouseButtonPressed)
			{
				Mouse::getInstance()->updatePresses(ev);
				driver.updateOnMousePress();
			}
			else if (ev.type == sf::Event::MouseButtonReleased)
			{
				Mouse::getInstance()->updateReleases(ev);
				driver.updateOnMouseRelease();
			}	
			else if (ev.type == sf::Event::MouseEntered ||
				ev.type == sf::Event::MouseMoved)
			{
				Mouse::getInstance()->updateAxes(window);
				driver.updateOnMouseAxes();
			}
			else if (ev.type == sf::Event::KeyPressed)
				driver.updateOnKeyPress(ev);
		}

		driver.updateOnTick();

		window.clear(sf::Color(202, 223, 235, 255));
		driver.render(window);
		window.display();
	}

	return 0;
}