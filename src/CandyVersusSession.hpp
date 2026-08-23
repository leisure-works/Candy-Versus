#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class CandyVersusSession {
protected:
    static inline CandyVersusSession* s_instance = nullptr;

    bool m_loggedIn = false;
    std::string m_username;
    std::string m_token;
    int m_elo = 0;

public:
    static CandyVersusSession* get() {
        if (!s_instance) s_instance = new CandyVersusSession();
        return s_instance;
    }

    bool isLoggedIn() const { return m_loggedIn; }
    std::string getUsername() const { return m_username; }
    std::string getToken() const { return m_token; }
    int getElo() const { return m_elo; }

    void setElo(int elo) { m_elo = elo; }

    void setLoggedIn(std::string const& username, int elo, std::string const& token) {
        m_loggedIn = true;
        m_username = username;
        m_elo = elo;
        m_token = token;
        log::info("Session: logged in as {} (Elo: {})", username, elo);
    }

    void logout() {
        m_loggedIn = false;
        m_username.clear();
        m_token.clear();
        m_elo = 0;
    }
};
