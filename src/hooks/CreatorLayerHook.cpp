#include <Geode/Geode.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include "../ui/LoginPopup.hpp"

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

        log::info("versus-button FOUND, applying changes...");

        btn->setSprite(CCSprite::createWithSpriteFrameName("GJ_versusBtn_001.png"));
        btn->setScale(0.8f);
        btn->setTarget(this, menu_selector(CandyVersusCreatorLayer::onOpenCandyVersus));

        return true;
    }

    void onOpenCandyVersus(CCObject*) {
        LoginPopup::create()->show();
    }
}; 
