#include <Geode/Geode.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include "../ui/LoginPopup.hpp"
#include "../ui/LobbyLayer.hpp"
#include "../CandyVersusSession.hpp"

using namespace geode::prelude;

class $modify(CandyVersusCreatorLayer, CreatorLayer) {
    bool init() {
        if (!CreatorLayer::init()) return false;

        auto btn = typeinfo_cast<CCMenuItemSpriteExtra*>(
            this->getChildByIDRecursive("versus-button")
        );

        if (!btn) {
            log::warn("versus-button NOT FOUND in CreatorLayer!");
            return true;
        }

        btn->setSprite(CCSprite::createWithSpriteFrameName("GJ_versusBtn_001.png"));
        btn->setScale(0.8f);
        btn->setTarget(this, menu_selector(CandyVersusCreatorLayer::onOpenCandyVersus));

        return true;
    }

    void onOpenCandyVersus(CCObject*) {
        // Đã login từ trước (cùng session) → vào thẳng Lobby, không hỏi lại
        if (CandyVersusSession::get()->isLoggedIn()) {
            CCDirector::sharedDirector()->replaceScene(
                CCTransitionFade::create(0.5f, LobbyLayer::scene())
            );
            return;
        }

        LoginPopup::create()->show();
    }
};
