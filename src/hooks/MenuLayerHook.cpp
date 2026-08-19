#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(CandyVersusMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto btn = typeinfo_cast<CCMenuItemSpriteExtra>(
            this->getChildByID("versus-button")
        );

        if (btn) {
            // 1. Đảm bảo nút nhận touch
            btn->setEnabled(true);

            // 2. Đổi callback sang function của mình
            btn->setTarget(this, menu_selector(CandyVersusMenuLayer::onOpenCandyVersus));

            // 3. Gỡ grayscale — tìm sprite con và remove
            if (auto normalImg = btn->getNormalImage()) {
                // Duyệt qua children để tìm CCSpriteGrayscale (hoặc node overlay)
                if (normalImg->getChildren()) {
                    CCArray* children = normalImg->getChildren();
                    CCObject* obj;
                    CCARRAY_FOREACH(children, obj) {
                        if (auto node = typeinfo_cast<CCNode>(obj)) {
                            // Xóa mọi child overlay (grayscale layer thường là child cuối)
                            normalImg->removeChild(node, true);
                        }
                    }
                }
                // Trả lại màu bình thường phòng khi có setColor xám
                normalImg->setColor({255, 255, 255});
                normalImg->setOpacity(255);
            }
        }

        return true;
    }

    void onOpenCandyVersus(CCObject*) {
        log::info("Candy Versus opened!");
        // TODO: CandyVersusPopup::create()->show();
    }
};
