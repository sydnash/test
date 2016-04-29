#ifndef _lua_custom_listener_h_
#define _lua_custom_listener_h_

#include "cocos2d.h"

namespace cocoslua_ext
{

class LuaCustomEvent : public cocos2d::EventCustom
{
public:
	enum class EventCode
	{
		kGetRemoteVersionInfo = 0,
	};
	LuaCustomEvent(const std::string &eventName, unsigned char* buff, int len)
		: EventCustom(eventName)
		, m_buff(nullptr)
		, m_len(0)
	{
		m_len = len;
		m_buff = new unsigned char[m_len];
		memcpy(m_buff, buff, m_len);
	}
	~LuaCustomEvent()
	{
		if (m_buff) {
			delete[] m_buff;
			m_len = 0;
			m_buff = nullptr;
		}
	}
	unsigned char* getBuffer(int *len) {
		*len = m_len;
		return m_buff;
	}
private:
	unsigned char* m_buff;
	int m_len;
};

class LuaCustomEventManager : public cocos2d::Ref
{
public:
	static LuaCustomEventManager* getInstance();

	void dispatchEvent(unsigned char* buff, int len);
	const std::string getEventName() const {
		return m_eventName;
	}
protected:
	static LuaCustomEventManager* m_self;
	LuaCustomEventManager();
private:
	std::string m_eventName;
	cocos2d::EventDispatcher *m_eventDispatcher;
};

typedef std::function<void(LuaCustomEvent*)> LuaCustomEventCallback;
class LuaCustomEventListener : public cocos2d::EventListenerCustom
{
public:
	static LuaCustomEventListener* create(LuaCustomEventManager* lem, const LuaCustomEventCallback &callback);

	LuaCustomEventListener();
	virtual bool checkAvailable() override;
	bool init(LuaCustomEventManager* lcm, const LuaCustomEventCallback &callback);

	virtual LuaCustomEventListener* clone() { assert(false); return nullptr; }
private:
	LuaCustomEventCallback m_listener;
	LuaCustomEventManager *m_manager;
};

}
#endif //_lua_custom_listener_h_
