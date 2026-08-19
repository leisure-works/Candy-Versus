#include <Geode/Geode.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/ui/Popup.hpp>

using namespace geode::prelude;

class LoginPopup : public Popup {
protected:
    CCLabelBMFont* m_statusLabel = nullptr;
    CCLabelBMFont* m_codeLabel = nullptr;
    CCMenuItemSpriteExtra* m_generateBtn = nullptr;
    bool m_waitingConfirm = false;

    bool init() {
        if (!Popup::init(320.f, 200.f))
            return false;

        this->setTitle("Candy Versus - Login");

        m_statusLabel = CCLabelBMFont::create("Chua lien ket tai khoan", "chatFont.fnt");
        m_statusLabel->setPosition(m_mainLayer->getContentSize().width / 2, 130.f);
        m_statusLabel->setScale(0.7f);
        m_mainLayer->addChild(m_statusLabel);

        m_codeLabel = CCLabelBMFont::create("", "bigFont.fnt");
        m_codeLabel->setPosition(m_mainLayer->getContentSize().width / 2, 90.f);
        m_codeLabel->setVisible(false);
        m_mainLayer->addChild(m_codeLabel);

        auto genSpr = ButtonSprite::create("Generate Code");
        m_generateBtn = CCMenuItemSpriteExtra::create(
            genSpr, this, menu_selector(LoginPopup::onGenerateCode)
        );

        auto menu = CCMenu::create();
        menu->addChild(m_generateBtn);
        menu->setPosition(m_mainLayer->getContentSize().width / 2, 45.f);
        m_mainLayer->addChild(menu);

        return true;
    }

    void onGenerateCode(CCObject*) {
        if (m_waitingConfirm) return;
        m_waitingConfirm = true;

        std::string fakeCode = generateFakeCode();
        m_codeLabel->setString(fakeCode.c_str());
        m_codeLabel->setVisible(true);
        m_statusLabel->setString("Nhap code nay vao web de xac nhan...");
        m_generateBtn->setVisible(false);

        this->runAction(CCSequence::create(
            CCDelayTime::create(3.0f),
            CCCallFunc::create(this, callfunc_selector(LoginPopup::onFakeConfirm)),
            nullptr
        ));
    }

    void onFakeConfirm() {
        m_statusLabel->setString("Da lien ket! Chao mung, Player123");
        m_codeLabel->setVisible(false);
        m_waitingConfirm = false;
    }

    std::string generateFakeCode() {
        static const char chars[] = "ABCDEFGHJKLMNPQRSTUVWXYZ23456789";
        std::string code;
        srand(static_cast<unsigned>(time(nullptr)));
        for (int i = 0; i < 6; i++) code += chars[rand() % (sizeof(chars) - 1)];
        return code;
    }

public:
    static LoginPopup* create() {
        auto popup = new LoginPopup();
        if (popup->init()) {
            popup->autorelease();
            return popup;
        }
        delete popup;
        return nullptr;
    }
};

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
