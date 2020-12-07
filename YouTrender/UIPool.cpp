#include "UIPool.h"
#include "EventQueue.h"
#include "Mouse.h"

std::unordered_map<UIPool::Uid, UI *> UIPool::UIs_;
bool UIPool::flagCleanup_ = false;

std::unordered_map<UIPool::Uid, Tooltipped *> UIPool::tooltipped_;
bool UIPool::isTooltipActive_ = false;
UIPool::Uid UIPool::activeTooltipped_ = 0;

std::unordered_map<uint8_t, Overlay *> UIPool::overlays_ = std::unordered_map<uint8_t, Overlay *>
{
	{ UIPool::OVERLAY_ID::LOADING, new Overlay("Loading...", 32, sf::Color(255, 255, 255, 255), sf::Color(0, 0, 0, 125)) }
};
bool UIPool::isOverlayOn_ = false;
uint8_t UIPool::overlayId_ = UIPool::OVERLAY_ID::LOADING;

std::deque<UIPool::Uid> UIPool::order_;

std::queue<UIPool::Uid> UIPool::availableUIDs_;
UIPool::Uid UIPool::nextUID_ = 0;

UIPool::UIPool() :
	toolbar_(32.0f)
{}

UIPool::~UIPool()
{
	for(auto it = UIs_.begin(); it != UIs_.end(); it++)
	{
		delete it->second;
		it->second = nullptr;
	}

	for (auto it = overlays_.begin(); it != overlays_.end(); it++)
	{
		delete it->second;
		it->second = nullptr;
	}
}

void UIPool::returnUID(Uid uid)
{
	availableUIDs_.push(uid);
}

void UIPool::removeAt(size_t orderIndex)
{
	unsigned int uid = order_[orderIndex];

	delete UIs_[uid];
	UIs_[uid] = nullptr;

	UIs_.erase(uid);
	order_.erase(order_.cbegin() + orderIndex);

	UIPool::returnUID(uid);
}

void UIPool::moveToToolbar(size_t orderIndex)
{
	unsigned int uid = order_[orderIndex];

	toolbar_.add(UIs_.at(uid));

	UIs_.erase(uid);
	order_.erase(order_.cbegin() + orderIndex);
}

void UIPool::updateCleanup()
{
	if (!flagCleanup_)
		return;

	for (size_t i = 0; i < order_.size();)
	{
		if (UIs_[order_[i]]->isClosed())
			this->removeAt(i);
		else if (UIs_[order_[i]]->isMinimized())
			this->moveToToolbar(i);
		else i++;
	}
	flagCleanup_ = false;
}

void UIPool::updateOnMousePress()
{
	for (auto it = order_.cbegin(); it != order_.cend(); it++)
		UIs_[*it]->updateOnMousePress();

	toolbar_.updateOnMousePress();
}

void UIPool::updateOnMouseRelease()
{
	for (auto it = order_.cbegin(); it != order_.cend(); it++)
		UIs_[*it]->updateOnMouseRelease();
}

void UIPool::updateOnMouseAxes()
{
	for (auto it = order_.cbegin(); it != order_.cend(); it++)
		UIs_[*it]->updateOnMouseAxes();

	if (isTooltipActive_)
	{
		tooltip_.updateOnMouseAxes();

		if (!Mouse::getInstance()->interactable() ||
				!tooltipped_[activeTooltipped_]->isHovered())
			isTooltipActive_ = false;
	}
	else if (Mouse::getInstance()->interactable())
	{
		for (auto it = tooltipped_.cbegin(); it != tooltipped_.cend(); it++)
		{
			if (it->second->isHovered())
			{
				isTooltipActive_ = true;
				activeTooltipped_ = it->first;
				tooltip_.activate(it->second->getTip());
				break;
			}
		}
	}	
}

void UIPool::render(sf::RenderWindow &window) const
{
	toolbar_.render(window);

	for (size_t i = order_.size(); i-- > 0;)
		UIs_[order_[i]]->render(window);

	if (isTooltipActive_)
		tooltip_.render(window);

	if (isOverlayOn_)
	{
		overlays_[overlayId_]->render(window);

		if (overlayId_ == OVERLAY_ID::LOADING)
			EventQueue::getInstance()->send(Event::EVENT::LOAD);
	}
}

void UIPool::add(UI *newUI)
{
	unsigned int uid = newUI->getUID();

	UIs_.emplace(uid, newUI);
	order_.push_front(uid);
}

void UIPool::remove(Uid uid)
{
	delete UIs_[uid];
	UIs_[uid] = nullptr;

	UIs_.erase(uid);

	for (auto it = order_.cbegin(); it != order_.cend();)
	{
		if (*it == uid)
		{
			order_.erase(it);
			break;
		}
		else it++;
	}

	UIPool::returnUID(uid);
}

void UIPool::prioritize(Uid uid)
{
	size_t idIndex = 0;

	for (size_t i = 0; i < order_.size(); i++)
	{
		if (order_[i] == uid)
		{
			idIndex = i;
			break;
		}
	}

	for (size_t i = idIndex; i > 0; i--)
		order_[i] = order_[i - 1];

	order_[0] = uid;
}

void UIPool::flagCleanup()
{
	flagCleanup_ = true;
}

void UIPool::addTooltipped(Tooltipped *tooltipped)
{
	tooltipped_.emplace(tooltipped->getUId(), tooltipped);
}

void UIPool::removeTooltipped(Uid uid)
{
	if (activeTooltipped_ == uid)
		isTooltipActive_ = false;

	tooltipped_.erase(uid);
	
	UIPool::returnUID(uid);
}

void UIPool::toggleOverlay(OVERLAY_ID overlayId)
{
	if (!isOverlayOn_)
	{
		isOverlayOn_ = true;
		overlayId_ = overlayId;
	}
	else
	{
		if (overlayId_ == overlayId)
			isOverlayOn_ = false;
		else overlayId_ = overlayId;
	}
}

void UIPool::removeOverlay()
{
	isOverlayOn_ = false;
}

UIPool::Uid UIPool::getNewUID()
{
	if (availableUIDs_.empty())
		return nextUID_++;
	else
	{
		unsigned int next = availableUIDs_.front();
		availableUIDs_.pop();

		return next;
	}
}