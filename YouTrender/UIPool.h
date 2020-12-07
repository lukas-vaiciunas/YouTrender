#pragma once

#include <unordered_map>
#include <queue>
#include "UI.h"
#include "Toolbar.h"
#include "Overlay.h"
#include "Tooltip.h"
#include "Tooltipped.h"

class UIPool
{
private:
	typedef unsigned int Uid;

	static std::unordered_map<Uid, UI *> UIs_;
	static bool flagCleanup_;

	//static std::vector<Tooltipped *> tooltipped_;
	static std::unordered_map<Uid, Tooltipped *> tooltipped_;
	static bool isTooltipActive_;
	static Uid activeTooltipped_;

	static std::unordered_map<uint8_t, Overlay *> overlays_;
	static bool isOverlayOn_;
	static uint8_t overlayId_;

	static std::deque<Uid> order_;

	static std::queue<Uid> availableUIDs_;
	static Uid nextUID_;

	static void returnUID(Uid uid);

	Toolbar toolbar_;
	Tooltip tooltip_;

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
	static void remove(Uid uid);
	static void prioritize(Uid uid);
	static void flagCleanup();

	static void addTooltipped(Tooltipped *tooltipped);
	static void removeTooltipped(Uid uid);

	static void toggleOverlay(OVERLAY_ID overlayId);
	static void removeOverlay();

	static Uid getNewUID();
};