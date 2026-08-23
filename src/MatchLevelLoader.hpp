#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class MatchLevelLoader : public CCObject, public LevelDownloadDelegate {
protected:
    void levelDownloadFinished(GJGameLevel* level) override;
    void levelDownloadFailed(int) override;

public:
    static void loadAndEnter(int64_t levelId);
};
