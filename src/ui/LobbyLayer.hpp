#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class LobbyLayer : public CCLayer {
protected:
    bool init();
    void onBack(CCObject*);

public:
    static CCScene* scene();
    static LobbyLayer* create();
};
