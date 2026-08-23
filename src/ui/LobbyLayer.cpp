#include "LobbyLayer.hpp"
#include "MatchLevelLoader.hpp"
#include "../CandyVersusSession.hpp"
#include "../CandyVersusMatch.hpp"
#include "../SupabaseConfig.hpp"

bool LobbyLayer::init() {
    if (!CCLayer::init()) return false;

    if (!CandyVersusSession::get()->isLoggedIn()) {
        log::warn("LobbyLayer opened without login!");
        return false;
    }

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint center = {winSize.width / 2, winSize.height / 2};

    auto bg = CCLayerColor::create({20, 20, 30, 255});
    this->addChild(bg);

    // Panel nền cho khung nội dung, dùng sprite 9-slice chuẩn của GD
    auto panel = CCScale9Sprite::create("GJ_square01.png");
    panel->setContentSize({340.f, 220.f});
    panel->setPosition(center);
    panel->setOpacity(230);
    this->addChild(panel);

    std::string username = CandyVersusSession::get()->getUsername();
    int elo = CandyVersusSession::get()->getElo();

    auto greeting = CCLabelBMFont::create(
        ("Chao mung, " + username + "!").c_str(), "bigFont.fnt"
    );
    greeting->setScale(0.75f);
    greeting->setPosition({center.x, center.y + 75.f});
    this->addChild(greeting);

    auto eloLabel = CCLabelBMFont::create(
        fmt::format("Elo: {}", elo).c_str(), "chatFont.fnt"
    );
    eloLabel->setScale(0.8f);
    eloLabel->setPosition({center.x, center.y + 40.f});
    this->addChild(eloLabel);

    auto divider = CCLayerColor::create({255, 255, 255, 60}, 280.f, 1.f);
    divider->setPosition({center.x - 140.f, center.y + 15.f});
    this->addChild(divider);

    m_queueStatusLabel = CCLabelBMFont::create("San sang thi dau!", "chatFont.fnt");
    m_queueStatusLabel->setScale(0.65f);
    m_queueStatusLabel->setColor({180, 180, 200});
    m_queueStatusLabel->setPosition({center.x, center.y - 15.f});
    this->addChild(m_queueStatusLabel);

    auto quickMatchSpr = ButtonSprite::create("Quick Match");
    m_quickMatchBtn = CCMenuItemSpriteExtra::create(
        quickMatchSpr, this, menu_selector(LobbyLayer::onQuickMatch)
    );
    m_quickMatchMenu = CCMenu::create(m_quickMatchBtn, nullptr);
    m_quickMatchMenu->setPosition({center.x, center.y - 65.f});
    this->addChild(m_quickMatchMenu);

    auto cancelSpr = ButtonSprite::create("Cancel");
    m_cancelBtn = CCMenuItemSpriteExtra::create(
        cancelSpr, this, menu_selector(LobbyLayer::onCancelQueue)
    );
    m_cancelMenu = CCMenu::create(m_cancelBtn, nullptr);
    m_cancelMenu->setPosition({center.x, center.y - 65.f});
    m_cancelMenu->setVisible(false);
    this->addChild(m_cancelMenu);

    auto backBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this, menu_selector(LobbyLayer::onBack)
    );
    auto backMenu = CCMenu::create(backBtn, nullptr);
    backMenu->setPosition({30.f, winSize.height - 30.f});
    this->addChild(backMenu);

    return true;
}

web::WebRequest LobbyLayer::buildAuthedRequest() {
    auto req = web::WebRequest();
    req.header("Content-Type", "application/json");
    req.header("apikey", SupabaseConfig::ANON_KEY);
    req.header("Authorization", std::string("Bearer ") + CandyVersusSession::get()->getToken());
    req.bodyJSON(matjson::Value::object());
    return req;
}

void LobbyLayer::onQuickMatch(CCObject*) {
    m_quickMatchMenu->setVisible(false);
    m_queueStatusLabel->setString("Dang vao hang doi...");

    m_actionListener.spawn(
        buildAuthedRequest().post(std::string(SupabaseConfig::URL) + "/rest/v1/rpc/join_queue"),
        [this](web::WebResponse res) {
            this->onJoinQueueResponse(std::move(res));
        }
    );
}

void LobbyLayer::onJoinQueueResponse(web::WebResponse res) {
    if (!res.ok()) {
        m_queueStatusLabel->setString("Loi khi vao hang doi!");
        m_quickMatchMenu->setVisible(true);
        return;
    }

    auto json = res.json().unwrapOr(matjson::Value());
    std::string status = json["status"].asString().unwrapOr("");

    if (status == "matched") {
        std::string matchId = json["match_id"].asString().unwrapOr("");
        int64_t levelId = json["level_id"].asInt().unwrapOr(0);
        onMatchFound(matchId, levelId);
        return;
    }

    m_queueStatusLabel->setString("Dang tim doi thu...");
    m_cancelMenu->setVisible(true);

    this->schedule(schedule_selector(LobbyLayer::pollFindMatch), 2.5f);
}

void LobbyLayer::pollFindMatch(float) {
    m_pollListener.spawn(
        buildAuthedRequest().post(std::string(SupabaseConfig::URL) + "/rest/v1/rpc/find_match"),
        [this](web::WebResponse res) {
            this->onFindMatchResponse(std::move(res));
        }
    );
}

void LobbyLayer::onFindMatchResponse(web::WebResponse res) {
    if (!res.ok()) return;

    auto json = res.json().unwrapOr(matjson::Value());
    std::string status = json["status"].asString().unwrapOr("");

    if (status == "matched") {
        this->unschedule(schedule_selector(LobbyLayer::pollFindMatch));
        std::string matchId = json["match_id"].asString().unwrapOr("");
        int64_t levelId = json["level_id"].asInt().unwrapOr(0);
        onMatchFound(matchId, levelId);
        return;
    }

    if (status == "waiting") {
        int eloRange = static_cast<int>(json["elo_range"].asInt().unwrapOr(0));
        int waitSec = static_cast<int>(json["wait_seconds"].asInt().unwrapOr(0));
        m_queueStatusLabel->setString(
            fmt::format("Dang tim doi thu... ({}s, +-{} elo)", waitSec, eloRange).c_str()
        );
        return;
    }

    this->unschedule(schedule_selector(LobbyLayer::pollFindMatch));
    m_queueStatusLabel->setString("Mat ket noi hang doi, thu lai.");
    resetQueueUI();
}

void LobbyLayer::onCancelQueue(CCObject*) {
    this->unschedule(schedule_selector(LobbyLayer::pollFindMatch));

    m_actionListener.spawn(
        buildAuthedRequest().post(std::string(SupabaseConfig::URL) + "/rest/v1/rpc/leave_queue"),
        [this](web::WebResponse res) {
            m_queueStatusLabel->setString("San sang thi dau!");
            resetQueueUI();
        }
    );
}

void LobbyLayer::resetQueueUI() {
    m_quickMatchMenu->setVisible(true);
    m_cancelMenu->setVisible(false);
}

void LobbyLayer::onMatchFound(std::string const& matchId, int64_t levelId) {
    m_queueStatusLabel->setString("Tim thay doi thu! Dang vao level...");
    log::info("Match found: {} (level: {})", matchId, levelId);

    if (levelId == 0) {
        m_queueStatusLabel->setString("Loi: pool level dang trong!");
        resetQueueUI();
        return;
    }

    CandyVersusMatch::get()->setMatch(matchId, levelId);
    MatchLevelLoader::loadAndEnter(levelId);
}

void LobbyLayer::onBack(CCObject*) {
    this->unschedule(schedule_selector(LobbyLayer::pollFindMatch));

    auto scene = CCScene::create();
    scene->addChild(MenuLayer::scene(false));
    CCDirector::sharedDirector()->replaceScene(
        CCTransitionFade::create(0.5f, scene)
    );
}

CCScene* LobbyLayer::scene() {
    auto layer = LobbyLayer::create();
    auto scene = CCScene::create();
    scene->addChild(layer);
    return scene;
}

LobbyLayer* LobbyLayer::create() {
    auto ret = new LobbyLayer();
    if (ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}
