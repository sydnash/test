#include "lua_custom_listener.h"

namespace cocoslua_ext
{

static const std::string LUA_CUSTOM_EVENT_LISTENER_ID = "lua_custom_event_listener_id";
LuaCustomEventManager* LuaCustomEventManager::m_self = nullptr;

LuaCustomEventManager* LuaCustomEventManager::getInstance()
{
	if (!m_self) {
		m_self = new LuaCustomEventManager();
	}
	return m_self;
}

void LuaCustomEventManager::dispatchEvent(unsigned char* buff, int len)
{
	LuaCustomEvent event(m_eventName, buff, len);
	m_eventDispatcher->dispatchEvent(&event);
}

LuaCustomEventManager::LuaCustomEventManager()
{
	m_eventDispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
	m_eventName = cocos2d::StringUtils::format("%s__%p", LUA_CUSTOM_EVENT_LISTENER_ID.c_str(), this);
}

LuaCustomEventListener* LuaCustomEventListener::create(LuaCustomEventManager* lem, const LuaCustomEventCallback &callback)
{
	auto ret = new LuaCustomEventListener;
	if (ret && ret->init(lem, callback)) {
		ret->autorelease();
	} else {
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

LuaCustomEventListener::LuaCustomEventListener()
	: m_listener(nullptr)
	, m_manager(nullptr)
{
}

bool LuaCustomEventListener::checkAvailable()
{
	bool ret = false;
	if (EventListener::checkAvailable() && m_manager != nullptr) {
		ret = true;
	}
	return ret;
}

bool LuaCustomEventListener::init(LuaCustomEventManager* lcm, const LuaCustomEventCallback &callback)
{
	bool ret = false;

	m_manager = lcm;
	m_listener = callback;

	auto func = [this](cocos2d::EventCustom *event) -> void {
		LuaCustomEvent *eventListener = dynamic_cast<LuaCustomEvent*>(event);
		if (m_listener) {
			m_listener(eventListener);
		}
	};
	if (EventListenerCustom::init(lcm->getEventName(), func)) {
		ret = true;
	}
	return ret;
}


}