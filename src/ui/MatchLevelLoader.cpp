#include "MatchLevelLoader.hpp"

void MatchLevelLoader::loadAndEnter(int64_t levelId) {
    auto loader = new MatchLevelLoader();
    GameLevelManager::sharedState()->m_levelDownloadDelegate = loader;
    GameLevelManager::sharedState()->downloadLevel(static_cast<int>(levelId), false);
}

void MatchLevelLoader::levelDownloadFinished(GJGameLevel* level) {
    GameLevelManager::sharedState()->m_levelDownloadDelegate = nullptr;

    CCDirector::sharedDirector()->replaceScene(
        CCTransitionFade::create(0.5f, PlayLayer::scene(level, false, false))
    );

    this->release();
}

void MatchLevelLoader::levelDownloadFailed(int) {
    GameLevelManager::sharedState()->m_levelDownloadDelegate = nullptr;
    log::error("Failed to download match level!");
    this->release();
}
