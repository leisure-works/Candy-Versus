 #pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class CandyVersusSettings {
public:
    // ===== Settings CÓ trong mod.json (Geode Settings UI quản lý) =====
    static std::string getServerAddress() {
        return Mod::get()->getSettingValue<std::string>("server-address");
    }

    static bool getAutoReconnect() {
        return Mod::get()->getSettingValue<bool>("auto-reconnect");
    }

    static int getSyncInterval() {
        return static_cast<int>(Mod::get()->getSettingValue<int64_t>("sync-interval-ms"));
    }

    static bool getShowOpponentIcon() {
        return Mod::get()->getSettingValue<bool>("show-opponent-icon");
    }

    // ===== Custom settings KHÔNG có trong mod.json =====
    // Lưu tự do qua matjson, không hiện trong Settings UI,
    // tiện cho config nội bộ (feature flags, debug toggles, v.v.)

    template <typename T>
    static T getCustom(std::string const& key, T defaultValue) {
        auto data = Mod::get()->getSavedValue<matjson::Value>("custom-settings", matjson::Value());
        if (data.contains(key)) {
            if constexpr (std::is_same_v<T, std::string>) {
                return data[key].asString().unwrapOr(defaultValue);
            } else if constexpr (std::is_same_v<T, bool>) {
                return data[key].asBool().unwrapOr(defaultValue);
            } else if constexpr (std::is_same_v<T, int>) {
                return static_cast<int>(data[key].asInt().unwrapOr(defaultValue));
            }
        }
        return defaultValue;
    }

    template <typename T>
    static void setCustom(std::string const& key, T value) {
        auto data = Mod::get()->getSavedValue<matjson::Value>("custom-settings", matjson::Value());
        data[key] = value;
        Mod::get()->setSavedValue("custom-settings", data);
    }
};
