#pragma once

#include <unordered_map>
#include <queue>
#include "UI.h"
#include "Toolbar.h"
#include "Overlay.h"

class UIPool
{
private:
	
	static std::unordered_map<unsigned int, UI *> UIs_;
	static bool flagCleanup_;

	static std::unordered_map<uint8_t, Overlay *> overlays_;
	static bool isOverlayOn_;
	static uint8_t overlayId_;

	static std::deque<unsigned int> order_;

	static std::queue<unsigned int> availableUIDs_;
	static unsigned int nextUID_;

	Toolbar toolbar_;

	static void returnUID(unsigned int uID);

	void removeAt(size_t orderIndex);
	void moveToToolbar(size_t orderIndex);
public:
	enum OVERLAY_ID : uint8_t
	{
		LOADING
	};

	UIPool();
	~UIPool();

	void updateCleanup();
	void updateOnMousePress();
	void updateOnMouseRelease();
	void updateOnMouseAxes();

	void render(sf::RenderWindow &window) const;

	static void add(UI *newUI);

	static void toggleOverlay(OVERLAY_ID overlayId);
	static void removeOverlay();
	static void flagCleanup();
	static void remove(unsigned int uID);
	static void prioritize(unsigned int uID);
	static unsigned int getNewUID();
};