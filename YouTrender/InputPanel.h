#pragma once

#include <unordered_set>
#include <vector>
#include <queue>
#include "ListBox.h"
#include "Collideable.h"
#include "Listener.h"

class InputPanel :
	public Collideable,
	public Listener
{
private:
	struct ChoiceSet
	{
	private:
		std::unordered_set<size_t> locationChoices_;
		int independentChoice_;
		int dependentChoice_;
		int methodChoice_;
	public:
		ChoiceSet(
			const std::unordered_set<size_t> &locationChoices,
			int independentChoice,
			int dependentChoice,
			int methodChoice) :
				locationChoices_(locationChoices),
				independentChoice_(independentChoice),
				dependentChoice_(dependentChoice),
				methodChoice_(methodChoice)
		{}

		std::unordered_set<size_t> &locationChoices()
		{
			return locationChoices_;
		}
		const std::unordered_set<size_t> &locationChoices() const
		{
			return locationChoices_;
		}
		int independentChoice() const
		{
			return independentChoice_;
		}
		int dependentChoice() const
		{
			return dependentChoice_;
		}
		int methodChoice() const
		{
			return methodChoice_;
		}
	};

	std::queue<ChoiceSet> dataQ_;
	sf::Text title_;
	std::vector<sf::Text> listTitles_;
	std::vector<ListBox *> listBoxes_;
	ButtonPrimitiveTextual analyzeButton_;

	void onEvent(Event::EVENT ev) override;
	void loadData(ChoiceSet &choiceSet);
public:
	InputPanel
	(
		float x, float y,
		const std::string &titleStr,
		const std::vector<std::pair<std::string, std::vector<std::string>>> &options,
		const sf::Color &defaultColor, const sf::Color &selectedColor
	);

	~InputPanel();

	void updateOnMousePress();

	void render(sf::RenderWindow &window) const;
};