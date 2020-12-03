#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>

class VideoData
{
private:
	static std::unordered_map<unsigned int, std::string> categoryIdMap_;
	static std::unordered_map<unsigned int, std::string> locationIdMap_;

	//unsigned char country_;
	std::string id_;
	std::string trendDate_;
	std::string title_;
	std::string channelTitle_;
	unsigned char categoryId_;
	std::string publishTime_;
	std::unordered_set<std::string> tags_;
	unsigned int numViews_;
	unsigned int numLikes_;
	unsigned int numDislikes_;
	unsigned int numComments_;
	std::string thumbnailLink_;
	bool areCommentsDisabled_;
	bool areRatingsDisabled_;
	bool isVideoErrorOrRemoved_;
	std::string description_;
public:
	enum CATEGORY : uint8_t
	{
		//COUNTRY,
		ID,
		TREND_DATE,
		TITLE,
		CHANNEL_TITLE,
		CATEGORY_ID,
		PUBLISH_TIME,
		TAGS,
		NUM_VIEWS,
		NUM_LIKES,
		NUM_DISLIKES,
		NUM_COMMENTS,
		THUMBNAIL_LINK,
		ARE_COMMENTS_DISABLED,
		ARE_RATINGS_DISABLED,
		IS_VIDEO_ERROR_OR_REMOVED,
		DESCRIPTION
	};

	enum ORIGIN_COUNTRY : uint8_t
	{
		UNITED_STATES,
		CANADA,
		GERMANY,
		FRANCE,
		BRITAIN,
		INDIA,
		JAPAN,
		KOREA,
		MEXICO,
		RUSSIA
	};

	VideoData(//unsigned char country,
		const std::string &id,
		const std::string &trendDate,
		const std::string &title,
		const std::string &channelTitle,
		unsigned char categoryId,
		const std::string &publishTime,
		const std::unordered_set<std::string> &tags,
		unsigned int numViews,
		unsigned int numLikes,
		unsigned int numDislikes,
		unsigned int numComments,
		const std::string &thumbnailLink,
		bool areCommentsDisabled,
		bool areRatingsDisabled,
		bool isVideoErrorOrRemoved,
		const std::string &description);

	VideoData(const std::vector<std::string> &strData);

	static const std::unordered_map<unsigned int, std::string> &categoryIdMap();
	static const std::unordered_map<unsigned int, std::string> &locationIdMap();

	//unsigned char country() const;
	const std::string &id() const;
	const std::string &trendDate() const;
	const std::string &title() const;
	const std::string &channelTitle() const;
	unsigned char categoryId() const;
	const std::string &publishTime() const;
	const std::unordered_set<std::string> &tags() const;
	unsigned int numViews() const;
	unsigned int numLikes() const;
	unsigned int numDislikes() const;
	unsigned int numComments() const;
	const std::string &thumbnailLink() const;
	bool areCommentsDisabled() const;
	bool areRatingsDisabled() const;
	bool isVideoErrorOrRemoved() const;
	const std::string &description() const;
};