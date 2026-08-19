#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/ui/TextInput.hpp>
#include <Geode/utils/web.hpp>

using namespace geode::prelude;

class LoginPopup : public Popup {
protected:
    TextInput* m_usernameInput = nullptr;
    TextInput* m_passwordInput = nullptr;
    CCLabelBMFont* m_statusLabel = nullptr;
    EventListener<web::WebTask> m_loginListener;

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

        m_statusLabel->setString("Dang dang nhap...");

        // TODO: thay URL thật khi backend sẵn sàng
        auto req = web::WebRequest();
        req.bodyJSON(matjson::Value({
            {"username", username},
            {"password", password}
        }));

        m_loginListener.bind(this, &LoginPopup::onLoginResponse);
        m_loginListener.setFilter(req.post("https://your-backend.com/api/login"));
    }

    void onLoginResponse(web::WebTask::Event* e) {
        if (auto res = e->getValue()) {
            if (res->ok()) {
                auto json = res->json().unwrapOr(matjson::Value());
                std::string token = json["token"].asString().unwrapOr("");
                std::string username = json["username"].asString().unwrapOr("");
                int elo = static_cast<int>(json["elo"].asInt().unwrapOr(0));

                if (!token.empty()) {
                    m_statusLabel->setString("Dang nhap thanh cong!");
                    // TODO: CandyVersusSession::get()->setLoggedIn(username, elo, token);
                    log::info("Login success: {} (Elo: {})", username, elo);
                } else {
                    m_statusLabel->setString("Sai username hoac password!");
                }
            } else {
                m_statusLabel->setString("Loi server, thu lai sau!");
            }
        }
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
