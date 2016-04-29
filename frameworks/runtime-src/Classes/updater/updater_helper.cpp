#include "updater_helper.h"
#include "custom_lua_listener/lua_custom_listener.h"
#include "proto/binary_stream_proto.h"

namespace cocoslua_ext
{

UpdaterHelper* UpdaterHelper::m_self = nullptr;
UpdaterHelper::UpdaterHelper(int countOfMaxProcessingTasks, int timeOutInSeconds, const std::string &tmpsuffix)
{
	m_streamHelper = BinaryStream::create(500);
	m_streamHelper->retain();

	cocos2d::network::DownloaderHints hints =
	{
		countOfMaxProcessingTasks,
		timeOutInSeconds,
		tmpsuffix.c_str(),
	};
	m_downloader = std::shared_ptr<cocos2d::network::Downloader>(new cocos2d::network::Downloader(hints));
	//    _downloader->setConnectionTimeout(DEFAULT_CONNECTION_TIMEOUT);
	m_downloader->onTaskError = [this](const cocos2d::network::DownloadTask& task,
		int errorCode,
		int errorCodeInternal,
		const std::string& errorStr) {
		m_streamHelper->reset();
		m_streamHelper->writeInt(9);
		m_streamHelper->writeString(task.requestURL.c_str(), task.requestURL.size());
		m_streamHelper->writeString(task.storagePath.c_str(), task.storagePath.size());
		m_streamHelper->writeString(task.identifier.c_str(), task.identifier.size());
		m_streamHelper->writeInt(errorCode);
		m_streamHelper->writeInt(errorCodeInternal);
		m_streamHelper->writeString(errorStr.c_str(), errorStr.size());
		dispatchEvent();
	};
	m_downloader->onTaskProgress = [this](const cocos2d::network::DownloadTask& task,
		int64_t bytesReceived,
		int64_t totalBytesReceived,
		int64_t totalBytesExpected) {
		//this->onProgress(totalBytesExpected, totalBytesReceived, task.requestURL, task.identifier);
		m_streamHelper->reset();
		m_streamHelper->writeInt(10);
		m_streamHelper->writeInt(totalBytesExpected);
		m_streamHelper->writeInt(totalBytesReceived);
		m_streamHelper->writeString(task.identifier.c_str(), task.identifier.size());
		dispatchEvent();
	};
	m_downloader->onFileTaskSuccess = [this](const cocos2d::network::DownloadTask& task) {
		//this->onSuccess(task.requestURL, task.storagePath, task.identifier);
		m_streamHelper->reset();
		m_streamHelper->writeInt(11);
		m_streamHelper->writeString(task.requestURL.c_str(), task.requestURL.size());
		m_streamHelper->writeString(task.storagePath.c_str(), task.storagePath.size());
		m_streamHelper->writeString(task.identifier.c_str(), task.identifier.size());
		dispatchEvent();
	};
}

void UpdaterHelper::dispatchEvent()
{
	int len;
	auto buff = m_streamHelper->getTotalBuff(&len);
	LuaCustomEventManager::getInstance()->dispatchEvent((unsigned char*)buff, len);
}

UpdaterHelper::~UpdaterHelper()
{
}


UpdaterHelper* UpdaterHelper::getInstance(int countOfMaxProcessingTasks, int timeOutInSeconds, const std::string &tmpsuffix)
{
	if (!m_self) {
		m_self = new UpdaterHelper(countOfMaxProcessingTasks, timeOutInSeconds, tmpsuffix);
	}
	return m_self;
}

void UpdaterHelper::destroy()
{
	if (m_self) {
		delete m_self;
		m_self = nullptr;
	}
}

void UpdaterHelper::downloadFile(const std::string &url, const std::string &localpath, const std::string &id)
{
	m_downloader->createDownloadFileTask(url, localpath, id);
}

void UpdaterHelper::clear()
{
}

}