#include "VideoData.h"
#include "Conversion.h"

std::unordered_map<unsigned int, std::string> VideoData::categoryIdMap_ =
std::unordered_map<unsigned int, std::string>
{
	{ 1,	"Film & Animation"		},
	{ 2,	"Autos & Vehicles"		},
	{ 10,	"Music"					},
	{ 15,	"Pets & Animals"		},
	{ 17,	"Sports"				},
	{ 18,	"Short Movies"			},
	{ 19,	"Travel & Events"		},
	{ 20,	"Gaming"				},
	{ 21,	"Videoblogging"			},
	{ 22,	"People & Blogs"		},
	{ 23,	"Comedy"				},
	{ 24,	"Entertainment"			},
	{ 25,	"News & Politics"		},
	{ 26,	"Howto & Style"			},
	{ 27,	"Education"				},
	{ 28,	"Science & Technology"	},
	{ 29,	"Nonprofits & Activism" },
	{ 30,	"Movies"				},
	{ 31,	"Anime / Animation"		},
	{ 32,	"Action / Adventure"	},
	{ 33,	"Classics"				},
	{ 34,	"Comedy"				},
	{ 35,	"Documentary"			},
	{ 36,	"Drama"					},
	{ 37,	"Family"				},
	{ 38,	"Foreign"				},
	{ 39,	"Horror"				},
	{ 40,	"Sci - Fi / Fantasy"	},
	{ 41,	"Thriller"				},
	{ 42,	"Shorts"				},
	{ 43,	"Shows"					},
	{ 44,	"Trailers"				}
};

std::unordered_map<unsigned int, std::string> VideoData::locationIdMap_ =
std::unordered_map<unsigned int, std::string>
{
	{ VideoData::ORIGIN_COUNTRY::UNITED_STATES, "US" },
	{ VideoData::ORIGIN_COUNTRY::CANADA,		"CA" },
	{ VideoData::ORIGIN_COUNTRY::GERMANY,		"DE" },
	{ VideoData::ORIGIN_COUNTRY::FRANCE,		"FR" },
	{ VideoData::ORIGIN_COUNTRY::BRITAIN,		"GB" },
	{ VideoData::ORIGIN_COUNTRY::INDIA,			"IN" },
	{ VideoData::ORIGIN_COUNTRY::JAPAN,			"JP" },
	{ VideoData::ORIGIN_COUNTRY::KOREA,			"KR" },
	{ VideoData::ORIGIN_COUNTRY::MEXICO,		"MX" },
	{ VideoData::ORIGIN_COUNTRY::RUSSIA,		"RU" },
};

VideoData::VideoData
(//unsigned char country,
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
	const std::string &description
) :
	//country_(country),
	id_(id),
	trendDate_(trendDate),
	title_(title),
	channelTitle_(channelTitle),
	categoryId_(categoryId),
	publishTime_(publishTime),
	tags_(tags),
	numViews_(numViews),
	numLikes_(numLikes),
	numDislikes_(numDislikes),
	numComments_(numComments),
	thumbnailLink_(thumbnailLink),
	areCommentsDisabled_(areCommentsDisabled),
	areRatingsDisabled_(areRatingsDisabled),
	isVideoErrorOrRemoved_(isVideoErrorOrRemoved),
	description_(description)
{}

VideoData::VideoData(const std::vector<std::string> &strData)
{
	//country_ = Conversion::stot<unsigned char>(strData[COUNTRY]);
	id_ = strData[ID];
	trendDate_ = strData[TREND_DATE];
	title_ = strData[TITLE];
	channelTitle_ = strData[CHANNEL_TITLE];
	categoryId_ = Conversion::stot<unsigned char>(strData[CATEGORY_ID]);
	publishTime_ = strData[PUBLISH_TIME];
	//tags_
	numViews_ = Conversion::stot<unsigned int>(strData[NUM_VIEWS]);
	numLikes_ = Conversion::stot<unsigned int>(strData[NUM_LIKES]);
	numDislikes_ = Conversion::stot<unsigned int>(strData[NUM_DISLIKES]);
	numComments_ = Conversion::stot<unsigned int>(strData[NUM_COMMENTS]);
	thumbnailLink_ = strData[THUMBNAIL_LINK];
	areCommentsDisabled_ = Conversion::stot<bool>(strData[ARE_COMMENTS_DISABLED]);
	areRatingsDisabled_ = Conversion::stot<bool>(strData[ARE_RATINGS_DISABLED]);
	isVideoErrorOrRemoved_ = Conversion::stot<bool>(strData[IS_VIDEO_ERROR_OR_REMOVED]);
	description_ = strData[DESCRIPTION];
}

const std::unordered_map<unsigned int, std::string> &VideoData::categoryIdMap()
{
	return categoryIdMap_;
}

const std::unordered_map<unsigned int, std::string> &VideoData::locationIdMap()
{
	return locationIdMap_;
}

/*unsigned char VideoData::country() const
{
	return country_;
}*/

const std::string &VideoData::id() const
{
	return id_;
}

const std::string &VideoData::trendDate() const
{
	return trendDate_;
}

const std::string &VideoData::title() const
{
	return title_;
}

const std::string &VideoData::channelTitle() const
{
	return channelTitle_;
}

unsigned char VideoData::categoryId() const
{
	return categoryId_;
}

const std::string &VideoData::publishTime() const
{
	return publishTime_;
}

const std::unordered_set<std::string> &VideoData::tags() const
{
	return tags_;
}

unsigned int VideoData::numViews() const
{
	return numViews_;
}

unsigned int VideoData::numLikes() const
{
	return numLikes_;
}

unsigned int VideoData::numDislikes() const
{
	return numDislikes_;
}

unsigned int VideoData::numComments() const
{
	return numComments_;
}

const std::string &VideoData::thumbnailLink() const
{
	return thumbnailLink_;
}

bool VideoData::areCommentsDisabled() const
{
	return areCommentsDisabled_;
}

bool VideoData::areRatingsDisabled() const
{
	return areRatingsDisabled_;
}

bool VideoData::isVideoErrorOrRemoved() const
{
	return isVideoErrorOrRemoved_;
}

const std::string &VideoData::description() const
{
	return description_;
}