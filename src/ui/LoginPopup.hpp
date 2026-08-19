#pragma once
#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/ui/TextInput.hpp>

using namespace geode::prelude;

class LoginPopup : public Popup {
protected:
    TextInput* m_usernameInput = nullptr;
    TextInput* m_passwordInput = nullptr;
    CCLabelBMFont* m_statusLabel = nullptr;

    bool init() {
        if (!Popup::init(320.f, 220.f))
            return false;

        this->setTitle("Candy Versus - Login");

        m_usernameInput = TextInput::create(240.f, "Username");
        m_usernameInput->setPosition(m_mainLayer->getContentSize().width / 2, 140.f);
        m_mainLayer->addChild(m_usernameInput);

        m_passwordInput = TextInput::create(240.f, "Password");
        m_passwordInput->setPasswordMode(true);
        m_passwordInput->setPosition(m_mainLayer->getContentSize().width / 2, 100.f);
        m_mainLayer->addChild(m_passwordInput);

        m_statusLabel = CCLabelBMFont::create("", "chatFont.fnt");
        m_statusLabel->setScale(0.6f);
        m_statusLabel->setPosition(m_mainLayer->getContentSize().width / 2, 65.f);
        m_mainLayer->addChild(m_statusLabel);

        auto loginSpr = ButtonSprite::create("Login");
        auto loginBtn = CCMenuItemSpriteExtra::create(
            loginSpr, this, menu_selector(LoginPopup::onLogin)
        );

        auto registerLabel = CCLabelBMFont::create("Chua co tai khoan? Dang ky tren web", "chatFont.fnt");
        registerLabel->setScale(0.4f);
        registerLabel->setPosition(m_mainLayer->getContentSize().width / 2, 25.f);
        m_mainLayer->addChild(registerLabel);

        auto menu = CCMenu::create();
        menu->addChild(loginBtn);
        menu->setPosition(m_mainLayer->getContentSize().width / 2, 45.f);
        m_mainLayer->addChild(menu);

        return true;
    }

    void onLogin(CCObject*) {
        std::string username = m_usernameInput->getString();
        std::string password = m_passwordInput->getString();

        if (username.empty() || password.empty()) {
            m_statusLabel->setString("Vui long nhap day du!");
            return;
        }

        // Giả lập login thành công — chưa gọi backend thật
        m_statusLabel->setString(("Xin chao, " + username + "!").c_str());
        log::info("Fake login: username={}", username);
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
