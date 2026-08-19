#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(CandyVersusMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto btn = typeinfo_cast<CCMenuItemSpriteExtra*>(
            this->getChildByID("versus-button")
        );

        if (btn) {
            btn->setEnabled(true);
            btn->setTarget(this, menu_selector(CandyVersusMenuLayer::onOpenCandyVersus));

            if (auto normalImg = btn->getNormalImage()) {
                // Xóa các child overlay (grayscale effect) nếu có
                if (normalImg->getChildren()) {
                    for (auto node : CCArrayExt<CCNode*>(normalImg->getChildren())) {
                        normalImg->removeChild(node, true);
                    }
                }

                // normalImg thường là CCSprite, cast để dùng setColor/setOpacity
                if (auto sprite = typeinfo_cast<CCSprite*>(normalImg)) {
                    sprite->setColor({255, 255, 255});
                    sprite->setOpacity(255);
                }
            }
        }

        return true;
    }

    void onOpenCandyVersus(CCObject*) {
        log::info("Candy Versus opened!");
        // TODO: CandyVersusPopup::create()->show();
    }
};
