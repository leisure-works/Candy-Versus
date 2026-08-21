#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/ui/Scrollbar.hpp>

using namespace geode::prelude;

struct FeaturedLevel {
    std::string name;
    std::string difficulty;
    int eloReward;
};

// Đổi tên tránh trùng với GD's LevelCell (TableViewCell)
class CVLevelCell : public CCLayer {
protected:
    bool init(FeaturedLevel const& level) {
        if (!CCLayer::init()) return false;

        this->setContentSize({320.f, 40.f});

        auto nameLabel = CCLabelBMFont::create(level.name.c_str(), "bigFont.fnt");
        nameLabel->setScale(0.5f);
        nameLabel->setAnchorPoint({0.f, 0.5f});
        nameLabel->setPosition({10.f, 28.f});
        this->addChild(nameLabel);

        auto diffLabel = CCLabelBMFont::create(level.difficulty.c_str(), "chatFont.fnt");
        diffLabel->setScale(0.6f);
        diffLabel->setAnchorPoint({0.f, 0.5f});
        diffLabel->setColor({255, 200, 0});
        diffLabel->setPosition({10.f, 12.f});
        this->addChild(diffLabel);

        auto rewardLabel = CCLabelBMFont::create(
            fmt::format("+{} Elo", level.eloReward).c_str(), "bigFont.fnt"
        );
        rewardLabel->setScale(0.5f);
        rewardLabel->setAnchorPoint({1.f, 0.5f});
        rewardLabel->setColor({0, 255, 100});
        rewardLabel->setPosition({310.f, 20.f});
        this->addChild(rewardLabel);

        return true;
    }

public:
    static CVLevelCell* create(FeaturedLevel const& level) {
        auto ret = new CVLevelCell();
        if (ret->init(level)) {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }
};

class FeaturedLevelsPopup : public Popup {
protected:
    bool init() {
        if (!Popup::init(360.f, 260.f))
            return false;

        this->setTitle("Daily Featured Levels");

        std::vector<FeaturedLevel> levels = {
            {"Bloodlust", "Demon", 25},
            {"Cataclysm", "Hard", 15},
            {"Athanatos", "Extreme Demon", 50},
            {"Fingerdash", "Harder", 10},
            {"Deadlocked", "Insane", 20},
            {"Clubstep", "Demon", 30},
        };

        auto listContent = CCLayer::create();
        float yOffset = 0.f;
        for (auto const& lvl : levels) {
            auto cell = CVLevelCell::create(lvl);
            cell->setPosition({0.f, yOffset});
            listContent->addChild(cell);
            yOffset -= 42.f;
        }
        float totalHeight = std::max(-yOffset, 180.f);
        listContent->setContentSize({320.f, totalHeight});
        listContent->setAnchorPoint({0.f, 1.f});
        listContent->setPositionY(totalHeight);

        constexpr float scrollWidth = 320.f;
        constexpr float scrollHeight = 180.f;
        constexpr float scrollX = 20.f;
        constexpr float scrollY = 40.f;

        auto scrollLayer = ScrollLayer::create({scrollWidth, scrollHeight});
        scrollLayer->m_contentLayer->addChild(listContent);
        scrollLayer->m_contentLayer->setContentSize({scrollWidth, totalHeight});
        scrollLayer->setPosition({scrollX, scrollY});
        scrollLayer->setTouchEnabled(true);
        m_mainLayer->addChild(scrollLayer);

        // Scrollbar — neo theo đỉnh của scrollLayer và ép chiều cao khớp
        // để không tràn ra ngoài khung bo tròn của popup.
        auto scrollbar = Scrollbar::create(scrollLayer);
        scrollbar->setAnchorPoint({0.5f, 1.f});
        scrollbar->setPosition({scrollX + scrollWidth + 10.f, scrollY + scrollHeight});
        scrollbar->setContentSize({scrollbar->getContentSize().width, scrollHeight});
        m_mainLayer->addChild(scrollbar);

        return true;
    }

public:
    static FeaturedLevelsPopup* create() {
        auto popup = new FeaturedLevelsPopup();
        if (popup->init()) {
            popup->autorelease();
            return popup;
        }
        delete popup;
        return nullptr;
    }
};

class $modify(CandyVersusMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto menu = this->getChildByID("bottom-menu");
        if (!menu) return true;

        auto spr = CircleButtonSprite::create(
            CCSprite::createWithSpriteFrameName("GJ_timeIcon_001.png"),
            CircleBaseColor::Green,
            CircleBaseSize::Medium
        );
        auto btn = CCMenuItemSpriteExtra::create(
            spr, this, menu_selector(CandyVersusMenuLayer::onOpenFeatured)
        );
        btn->setID("candy-versus-daily-button"_spr);

        static_cast<CCMenu*>(menu)->addChild(btn);
        menu->updateLayout();

        return true;
    }

    void onOpenFeatured(CCObject*) {
        FeaturedLevelsPopup::create()->show();
    }
};
