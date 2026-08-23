#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class CandyVersusMatch {
protected:
    static inline CandyVersusMatch* s_instance = nullptr;

    bool m_inMatch = false;
    std::string m_matchId;
    int64_t m_levelId = 0;

public:
    static CandyVersusMatch* get() {
        if (!s_instance) s_instance = new CandyVersusMatch();
        return s_instance;
    }

    bool isInMatch() const { return m_inMatch; }
    std::string getMatchId() const { return m_matchId; }
    int64_t getLevelId() const { return m_levelId; }

    void setMatch(std::string const& matchId, int64_t levelId) {
        m_inMatch = true;
        m_matchId = matchId;
        m_levelId = levelId;
    }

    void clearMatch() {
        m_inMatch = false;
        m_matchId.clear();
        m_levelId = 0;
    }
};
