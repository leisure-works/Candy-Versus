#pragma once
#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/ui/TextInput.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/utils/async.hpp>

using namespace geode::prelude;

class LoginPopup : public Popup {
protected:
    TextInput* m_usernameInput = nullptr;
    TextInput* m_passwordInput = nullptr;
    CCLabelBMFont* m_statusLabel = nullptr;
    CCMenuItemSpriteExtra* m_loginBtn = nullptr;
    async::TaskHolder<web::WebResponse> m_loginListener;

    static constexpr auto SUPABASE_URL = "https://vwsmthfwhwzzlqtzsjvp.supabase.co";
    static constexpr auto SUPABASE_ANON_KEY =
        "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6InZ3c210aGZ3aHd6emxxdHpzanZwIiwicm9sZSI6ImFub24iLCJpYXQiOjE3ODcxMzcwNzIsImV4cCI6MjEwMjcxMzA3Mn0.Whzscv-OuixVRBpplx1_t_73hnLdv9ktEylUxEsOC3c";

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
        m_loginBtn = CCMenuItemSpriteExtra::create(
            loginSpr, this, menu_selector(LoginPopup::onLogin)
        );

        auto registerLabel = CCLabelBMFont::create("Chua co tai khoan? Dang ky tren web", "chatFont.fnt");
        registerLabel->setScale(0.4f);
        registerLabel->setPosition(m_mainLayer->getContentSize().width / 2, 25.f);
        m_mainLayer->addChild(registerLabel);

        auto menu = CCMenu::create();
        menu->addChild(m_loginBtn);
        menu->setPosition(m_mainLayer->getContentSize().width / 2, 45.f);
        m_mainLayer->addChild(menu);

        return true;
    }

    void setLoading(bool loading) {
        m_loginBtn->setEnabled(!loading);
        m_loginBtn->setOpacity(loading ? 120 : 255);
    }

    void onLogin(CCObject*) {
        std::string username = m_usernameInput->getString();
        std::string password = m_passwordInput->getString();

        if (username.empty() || password.empty()) {
            m_statusLabel->setString("Vui long nhap day du!");
            return;
        }

        m_statusLabel->setString("Dang dang nhap...");
        setLoading(true);

        matjson::Value body;
        body["username"] = username;
        body["password"] = password;

        auto req = web::WebRequest();
        req.header("Content-Type", "application/json");
        req.header("apikey", SUPABASE_ANON_KEY);
        req.header("Authorization", std::string("Bearer ") + SUPABASE_ANON_KEY);
        req.bodyJSON(body);

        // API mới (Geode v5): dùng async::TaskHolder thay cho EventListener<web::WebTask>
        m_loginListener.spawn(
            req.post(std::string(SUPABASE_URL) + "/functions/v1/login"),
            [this](web::WebResponse* res) {
                this->onLoginResponse(res);
            }
        );
    }

    void onLoginResponse(web::WebResponse* res) {
        setLoading(false);

        if (!res) {
            m_statusLabel->setString("Loi ket noi server!");
            return;
        }

        auto json = res->json().unwrapOr(matjson::Value());

        if (!res->ok()) {
            std::string errMsg = json.contains("error")
                ? json["error"].asString().unwrapOr("Loi khong xac dinh")
                : "Loi ket noi server";
            m_statusLabel->setString(errMsg.c_str());
            return;
        }

        std::string token = json["token"].asString().unwrapOr("");
        std::string username = json["username"].asString().unwrapOr("");
        int elo = static_cast<int>(json["elo"].asInt().unwrapOr(0));

        if (token.empty()) {
            m_statusLabel->setString("Dang nhap that bai!");
            return;
        }

        m_statusLabel->setString(("Xin chao, " + username + "!").c_str());
        log::info("Login success: {} (Elo: {})", username, elo);

        // TODO: CandyVersusSession::get()->setLoggedIn(username, elo, token);

        this->runAction(CCSequence::create(
            CCDelayTime::create(1.0f),
            CCCallFunc::create(this, callfunc_selector(LoginPopup::forceClose)),
            nullptr
        ));
    }

    void forceClose() {
        this->removeFromParentAndCleanup(true);
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
