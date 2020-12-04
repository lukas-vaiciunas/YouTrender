#include "UIPool.h"
#include "EventQueue.h"

std::unordered_map<unsigned int, UI *> UIPool::UIs_;
bool UIPool::flagCleanup_ = false;

std::unordered_map<uint8_t, Overlay *> UIPool::overlays_ = std::unordered_map<uint8_t, Overlay *>
{
	{ UIPool::OVERLAY_ID::LOADING, new Overlay("Loading...", 32, sf::Color(255, 255, 255, 255), sf::Color(0, 0, 0, 125)) }
};
bool UIPool::isOverlayOn_ = false;
uint8_t UIPool::overlayId_ = UIPool::OVERLAY_ID::LOADING;

std::deque<unsigned int> UIPool::order_;

std::queue<unsigned int> UIPool::availableUIDs_;
unsigned int UIPool::nextUID_ = 0;

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

void UIPool::returnUID(unsigned int uID)
{
	availableUIDs_.push(uID);
}

void UIPool::removeAt(size_t orderIndex)
{
	unsigned int uID = order_[orderIndex];

	delete UIs_[uID];
	UIs_[uID] = nullptr;

	UIs_.erase(uID);
	order_.erase(order_.cbegin() + orderIndex);

	UIPool::returnUID(uID);
}

void UIPool::moveToToolbar(size_t orderIndex)
{
	unsigned int uID = order_[orderIndex];

	toolbar_.add(UIs_.at(uID));

	UIs_.erase(uID);
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
}

void UIPool::render(sf::RenderWindow &window) const
{
	toolbar_.render(window);

	for (size_t i = order_.size(); i-- > 0;)
		UIs_[order_[i]]->render(window);

	if (isOverlayOn_)
	{
		overlays_[overlayId_]->render(window);

		if (overlayId_ == OVERLAY_ID::LOADING)
			EventQueue::getInstance()->send(Event::EVENT::LOAD);
	}
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

void UIPool::flagCleanup()
{
	flagCleanup_ = true;
}

void UIPool::add(UI *newUI)
{
	unsigned int uID = newUI->getUID();

	UIs_.emplace(uID, newUI);
	order_.push_front(uID);
}

void UIPool::remove(unsigned int uID)
{
	delete UIs_[uID];
	UIs_[uID] = nullptr;

	UIs_.erase(uID);

	for (auto it = order_.cbegin(); it != order_.cend();)
	{
		if (*it == uID)
		{
			order_.erase(it);
			break;
		}
		else it++;
	}	

	UIPool::returnUID(uID);
}

void UIPool::prioritize(unsigned int uID)
{
	size_t idIndex = 0;

	for (size_t i = 0; i < order_.size(); i++)
	{
		if (order_[i] == uID)
		{
			idIndex = i;
			break;
		}
	}

	for (size_t i = idIndex; i > 0; i--)
		order_[i] = order_[i - 1];

	order_[0] = uID;
}

unsigned int UIPool::getNewUID()
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