#include "LobbyLayer.hpp"
#include "../CandyVersusSession.hpp"

bool LobbyLayer::init() {
    if (!CCLayer::init()) return false;

    // Bảo vệ: không cho vào Lobby nếu chưa login thành công
    if (!CandyVersusSession::get()->isLoggedIn()) {
        log::warn("LobbyLayer opened without login!");
        return false;
    }

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto bg = CCLayerColor::create({20, 20, 30, 255});
    this->addChild(bg);

    std::string username = CandyVersusSession::get()->getUsername();
    int elo = CandyVersusSession::get()->getElo();

    auto greeting = CCLabelBMFont::create(
        ("Chao mung, " + username + "!").c_str(), "bigFont.fnt"
    );
    greeting->setPosition({winSize.width / 2, winSize.height / 2 + 20.f});
    this->addChild(greeting);

    auto eloLabel = CCLabelBMFont::create(
        fmt::format("Elo: {}", elo).c_str(), "chatFont.fnt"
    );
    eloLabel->setScale(0.8f);
    eloLabel->setPosition({winSize.width / 2, winSize.height / 2 - 15.f});
    this->addChild(eloLabel);

    auto backBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this, menu_selector(LobbyLayer::onBack)
    );
    auto menu = CCMenu::create(backBtn, nullptr);
    menu->setPosition({30.f, winSize.height - 30.f});
    this->addChild(menu);

    return true;
}

void LobbyLayer::onBack(CCObject*) {
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
