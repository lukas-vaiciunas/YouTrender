#pragma once

#include <unordered_map>
#include <queue>
#include "UI.h"
#include "Toolbar.h"

class UIPool
{
private:
	static unsigned int nextUID_;
	static std::queue<unsigned int> availableUIDs_;
	static std::unordered_map<unsigned int, UI *> UIs_;
	static std::deque<unsigned int> order_;
	static bool flagCleanup_;

	Toolbar toolbar_;

	static void returnUID(unsigned int uID);

	void removeAt(size_t orderIndex);
	void moveToToolbar(size_t orderIndex);
public:
	UIPool();
	~UIPool();

	void updateCleanup();
	void updateOnMousePress();
	void updateOnMouseRelease();
	void updateOnMouseAxes();

	void render(sf::RenderWindow &window) const;

	static void add(UI *newUI);

	static void flagCleanup();
	static void remove(unsigned int uID);
	static void prioritize(unsigned int uID);
	static unsigned int getNewUID();
};