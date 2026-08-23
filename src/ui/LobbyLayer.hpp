#pragma once
#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/utils/async.hpp>

using namespace geode::prelude;

class LobbyLayer : public CCLayer {
protected:
    CCMenuItemSpriteExtra* m_quickMatchBtn = nullptr;
    CCMenuItemSpriteExtra* m_cancelBtn = nullptr;
    CCLabelBMFont* m_queueStatusLabel = nullptr;

    async::TaskHolder<web::WebResponse> m_actionListener;
    async::TaskHolder<web::WebResponse> m_pollListener;

    bool init();
    void onBack(CCObject*);
    void onQuickMatch(CCObject*);
    void onCancelQueue(CCObject*);

    web::WebRequest buildAuthedRequest();
    void onJoinQueueResponse(web::WebResponse res);
    void pollFindMatch(float dt);
    void onFindMatchResponse(web::WebResponse res);
    void onMatchFound(std::string const& matchId, int64_t levelId);
    void resetQueueUI();

public:
    static CCScene* scene();
    static LobbyLayer* create();
};
