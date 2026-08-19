 #include <Geode/Geode.hpp>
#include "CandyVersusSettings.hpp"

using namespace geode::prelude;

$execute {
    // Load settings từ mod.json
    log::info("Candy Versus loaded!");
    log::info("Server: {}", CandyVersusSettings::getServerAddress());
    log::info("Auto reconnect: {}", CandyVersusSettings::getAutoReconnect());
    log::info("Sync interval: {}ms", CandyVersusSettings::getSyncInterval());

    // Load custom setting (không có trong mod.json) — vd feature flag
    bool debugMode = CandyVersusSettings::getCustom<bool>("debug-mode", false);
    log::info("Debug mode (custom): {}", debugMode);

    // Lắng nghe khi settings trong mod.json bị đổi
    listenForSettingChanges("server-address", [](std::string value) {
        log::info("Server address changed to: {}", value);
    });

    listenForSettingChanges("auto-reconnect", +[](bool value) {
        log::info("Auto reconnect changed: {}", value);
    });

    listenForSettingChanges("sync-interval-ms", +[](int64_t value) {
        log::info("Sync interval changed: {}ms", value);
    });
}
