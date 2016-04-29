#ifndef __updater_updater_helper_h__
#define __updater_updater_helper_h__

#include "cocos2d.h"
#include "network/CCDownloader.h"

namespace cocoslua_ext
{

class BinaryStream;
class UpdaterHelper : public cocos2d::Ref
{
public:
	UpdaterHelper(int countOfMaxProcessingTasks, int timeOutInSeconds, const std::string &tmpsuffix);
	~UpdaterHelper();


	static UpdaterHelper* getInstance(int countOfMaxProcessingTasks, int timeOutInSeconds, const std::string &tmpsuffix);
	static void destroy();
	void downloadFile(const std::string &url, const std::string &localpath, const std::string &id);
	void clear();
private:
	void dispatchEvent();
	static UpdaterHelper* m_self;
	std::shared_ptr<cocos2d::network::Downloader> m_downloader;
	BinaryStream *m_streamHelper;
};

}

#endif //__updater_updater_helper_h__
