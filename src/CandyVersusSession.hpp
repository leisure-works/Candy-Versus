#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class CandyVersusSession {
protected:
    static inline CandyVersusSession* s_instance = nullptr;

    bool m_loggedIn = false;
    std::string m_username;
    int m_elo = 0;

public:
    static CandyVersusSession* get() {
        if (!s_instance) s_instance = new CandyVersusSession();
        return s_instance;
    }

    bool isLoggedIn() const { return m_loggedIn; }
    std::string getUsername() const { return m_username; }
    int getElo() const { return m_elo; }

    void setLoggedIn(std::string const& username, int elo) {
        m_loggedIn = true;
        m_username = username;
        m_elo = elo;
        log::info("Session: logged in as {} (Elo: {})", username, elo);
    }

    void logout() {
        m_loggedIn = false;
        m_username.clear();
        m_elo = 0;
    }
};
