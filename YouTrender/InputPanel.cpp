#include "InputPanel.h"
#include "FontData.h"
#include "Mouse.h"
#include "BarChart.h"
#include "Constants.h"
#include "DataMod.h"
#include "VideoData.h"
#include "Loader.h"
#include "UIPool.h"
#include "UI.h"
#include "Widget.h"
#include "ListBoxSingle.h"
#include "ListBoxMultiple.h"
#include "Timer.h"
#include "Log.h"
#include <iostream> //

InputPanel::InputPanel(
	float x, float y,
	const std::string &titleStr,
	const std::vector<std::pair<std::string, std::vector<std::string>>> &options,
	const std::vector<std::vector<unsigned int>> buttonTexIds,
	unsigned int analyzeButtonTexId) :
		Collideable(x, y, 0.0f, 0.0f),
		Listener({ Event::EVENT::LOAD }),
		title_(),
		analyzeButton_(0.0f, 0.0f, 72.0f, 32.0f, analyzeButtonTexId, analyzeButtonTexId + 1, "Analyze", 12U, sf::Color(255, 255, 255, 255), 0.5f)
{
	constexpr float gapX = 16.0f;
	constexpr float gapY = 32.0f;
	constexpr float textOffset = gapY / 2.0f;
	constexpr float buttonWidth = 72.0f;
	constexpr float locationButtonWidth = 49.0f;
	constexpr float buttonHeight = 32.0f;
	constexpr unsigned int textSize = 16U;

	float startX = x;
	float startY = y + gapY;
	float maxTextWidth = 0.0f;
	float maxListWidth = 0.0f;
	float totalHeight = 0.0f;

	for (size_t i = 0; i < options.size(); i++)
	{
		listTitles_.push_back(sf::Text(options[i].first, FontData::getInstance()->getMainFont(), textSize));

		listTitles_[i].setFillColor(sf::Color());

		float textWidth = listTitles_[i].getLocalBounds().width;

		if (maxTextWidth < textWidth)
			maxTextWidth = textWidth;

		listTitles_[i].setOrigin(std::floorf(textWidth), std::floorf(textSize / 2.0f));
		listTitles_[i].setPosition(x, std::floorf(startY + (buttonHeight + gapY) * i + textSize));
	}

	startX = x + maxTextWidth + gapX;

	for (auto it = listTitles_.begin(); it != listTitles_.end(); it++)
		it->setPosition(startX - gapX, it->getPosition().y);

	listBoxes_.push_back(new ListBoxMultiple(startX, startY, locationButtonWidth, buttonHeight, gapX, buttonTexIds[0], options[0].second, sf::Color(0, 0, 0, 255), 0.25f));
	float listBoxWidth = listBoxes_[0]->getAABB().width;
	if (maxListWidth < listBoxWidth)
		maxListWidth = listBoxWidth;

	for (size_t i = 1; i < options.size(); i++)
	{
		listBoxes_.push_back(new ListBoxSingle(startX, startY + (buttonHeight + gapY) * i, buttonWidth, buttonHeight, gapX, buttonTexIds[i], options[i].second, sf::Color(255, 255, 255, 255), 0.5f));

		listBoxWidth = listBoxes_[i]->getAABB().width;
		if (maxListWidth < listBoxWidth)
			maxListWidth = listBoxWidth;

		totalHeight += (buttonHeight + gapY);
	}

	title_ = sf::Text(titleStr, FontData::getInstance()->getMainFont(), textSize);
	title_.setOrigin(std::floorf(title_.getLocalBounds().width / 2.0f), 0.0f);
	title_.setFillColor(sf::Color());
	title_.setPosition(std::floorf(startX + maxListWidth / 2.0f), y);

	totalHeight = (buttonHeight + gapY) * (listBoxes_.size() + 1);

	analyzeButton_.setPosition(startX, y + totalHeight - buttonHeight);
	analyzeButton_.setSize(buttonWidth, buttonHeight);

	Collideable::setSize(maxListWidth + maxTextWidth + gapX, totalHeight);
}

InputPanel::~InputPanel()
{
	while (!listBoxes_.empty())
	{
		delete listBoxes_.back();
		listBoxes_.back() = nullptr;
		listBoxes_.pop_back();
	}
}

void InputPanel::onEvent(Event::EVENT ev)
{
	if (ev == Event::EVENT::LOAD)
	{
		if (!dataQ_.empty())
		{
			this->loadData(dataQ_.front());
			dataQ_.pop();

			if (dataQ_.empty())
				UIPool::removeOverlay();
		}
	}
}

void InputPanel::loadData(ChoiceSet &choiceSet)
{
	Timer timer;
	DataMod<unsigned int, unsigned int> dataMod;
	Loader loader;
	std::vector<std::pair<unsigned int, unsigned int>> rawData;
	std::vector<std::pair<std::string, unsigned int>> readyData;
	std::vector<std::string> dataInputs;
	unsigned int ranking = 5;
	std::string widgetTitle = "";

	VideoData::CATEGORY independent = VideoData::CATEGORY::CATEGORY_ID;
	VideoData::CATEGORY dependent = VideoData::CATEGORY::NUM_VIEWS;

	std::unordered_set<size_t> &locationChoices = choiceSet.locationChoices();

	while (!locationChoices.empty())
	{
		auto firstIt = choiceSet.locationChoices().cbegin();

		dataInputs.push_back(VideoData::locationIdMap().at(*firstIt));
		locationChoices.erase(firstIt);
	}

	switch (choiceSet.independentChoice())
	{
	case 0:
		independent = VideoData::CATEGORY::CATEGORY_ID;
		widgetTitle.append("Category");
		break;
	}

	widgetTitle.append(" vs ");

	switch (choiceSet.dependentChoice())
	{
	case 0:
		dependent = VideoData::CATEGORY::NUM_VIEWS;
		widgetTitle.append("Views");
		break;
	case 1:
		dependent = VideoData::CATEGORY::NUM_LIKES;
		widgetTitle.append("Likes");
		break;
	case 2:
		dependent = VideoData::CATEGORY::NUM_DISLIKES;
		widgetTitle.append("Dislikes");
		break;
	case 3:
		dependent = VideoData::CATEGORY::NUM_COMMENTS;
		widgetTitle.append("Comments");
		break;
	}

	switch (choiceSet.rankingChoice())
	{
	case 0:
		ranking = 5;
		break;
	case 1:
		ranking = 10;
		break;
	}

	widgetTitle.append(" in ");

	timer.start();

	switch (choiceSet.methodChoice())
	{
	case 0:
	{
		typedef std::unordered_map<unsigned int, unsigned int> DataType;

		DataType loadedData;
		std::string filePath = "";

		for (const std::string &location : dataInputs)
		{
			widgetTitle.append(location + ", ");
			filePath = "data/" + location + "videos.csv";
			loader.loadCountPairs<DataType>(
				loadedData, filePath.c_str(), independent, dependent);
		}

		widgetTitle.append("using Hash Table (Top " + std::to_string(ranking) + ")");

		rawData = dataMod.getLargest(loadedData, ranking);
		break;
	}
	case 1:
	{
		typedef typename std::map<unsigned int, unsigned int> DataType;

		DataType loadedData;
		std::string filePath = "";

		for (const std::string &location : dataInputs)
		{
			widgetTitle.append(location + ", ");
			filePath = "data/" + location + "videos.csv";
			loader.loadCountPairs<DataType>(
				loadedData, filePath.c_str(), independent, dependent);
		}

		widgetTitle.append("using BST (Top " + std::to_string(ranking) + ")");

		rawData = dataMod.getLargest(loadedData, ranking);
		break;
	}
	}

	timer.stop();

	//std::cout << "Time: " << timer.getMilliseconds().count() / 1000.0f << "s" << std::endl;
	std::string logTxt = "Time: " + std::to_string(timer.getMilliseconds().count() / 1000.0f) + "s";
	Log::getInstance()->push(logTxt);

	switch (independent)
	{
	case VideoData::CATEGORY::CATEGORY_ID:
		readyData = dataMod.categoryIdKeysToStrings(rawData);
		break;
	}

	unsigned int chartWidth = Global::SCREEN_WIDTH / 2;
	unsigned int chartHeight = Global::SCREEN_HEIGHT / 2;
	float dX = Global::SCREEN_WIDTH / 2.0f - chartWidth / 2.0f;
	float dY = Global::SCREEN_HEIGHT / 2.0f - chartHeight / 2.0f;

	BarChart *chart = new BarChart(chartWidth, chartHeight, readyData);
	Widget *widget = new Widget(dX, dY, widgetTitle, chart);
	UIPool::add(widget);

	UIPool::removeOverlay();
}

void InputPanel::updateOnMousePress()
{
	Mouse &mouse = *Mouse::getInstance();

	if (mouse.interactable() &&
		mouse.isPressed(Mouse::BUTTON::LEFT) &&
		Collideable::isColliding(mouse.getPosition()))
	{
		//Do not reset Mouse::BUTTON::LEFT here, because it is done in Button::isClicked().

		bool allSelected = true;

		for (ListBox *lb : listBoxes_)
		{
			if (!lb->somethingSelected())
				allSelected = false;

			if (lb->isColliding(Mouse::getInstance()->getPosition()))
			{
				lb->updateOnMousePress();
				return;
			}
		}

		if (allSelected &&
			analyzeButton_.isClicked())
		{
			VideoData::CATEGORY independent = VideoData::CATEGORY::CATEGORY_ID;
			VideoData::CATEGORY dependent = VideoData::CATEGORY::NUM_VIEWS;

			std::unordered_set<size_t> locationChoices =
				static_cast<ListBoxMultiple *>(listBoxes_[0])->selectedIndicies();

			int independentChoice =
				static_cast<ListBoxSingle *>(listBoxes_[1])->selectedIndex();

			int dependentChoice =
				static_cast<ListBoxSingle *>(listBoxes_[2])->selectedIndex();

			int rankingChoice =
				static_cast<ListBoxSingle *>(listBoxes_[3])->selectedIndex();

			int methodChoice =
				static_cast<ListBoxSingle *>(listBoxes_[4])->selectedIndex();

			UIPool::toggleOverlay(UIPool::OVERLAY_ID::LOADING);
			dataQ_.push(ChoiceSet(locationChoices, independentChoice, dependentChoice, rankingChoice, methodChoice));
		}
	}
}

/*void InputPanel::updateOnTick()
{
	if (!dataQ_.empty())
	{
		this->loadData(dataQ_.front());
		dataQ_.pop();

		if(dataQ_.empty())
			UIPool::removeOverlay();
	}
}*/

void InputPanel::render(sf::RenderWindow &window) const
{
	/*sf::RectangleShape rs;
	rs.setPosition(aabb_.left, aabb_.top);
	rs.setSize(sf::Vector2f(aabb_.width, aabb_.height));
	window.draw(rs);*/

	window.draw(title_);

	for (const sf::Text &txt : listTitles_)
		window.draw(txt);

	for (const ListBox *lb : listBoxes_)
		lb->render(window);

	analyzeButton_.render(window);
}