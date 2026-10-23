#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <deque>

using namespace geode::prelude;

// Frame-based input delay prototype for GD 2.2083 / Android.
// This delays and replays inputs; it does NOT detect valid jump windows
// and cannot guarantee frame-perfect timing.

namespace {
    struct InputEvent {
        bool down;
        int button;
        bool player1;
        int framesLeft;
    };

    std::deque<InputEvent> g_events;
    bool g_replaying = false;
}

class $modify(PredictiveInputBufferPlayLayer, PlayLayer) {
    void handleButton(bool down, int button, bool isPlayer1) {
        if (g_replaying ||
            !Mod::get()->getSettingValue<bool>("enabled")) {
            PlayLayer::handleButton(down, button, isPlayer1);
            return;
        }

        auto delay = static_cast<int>(
            Mod::get()->getSettingValue<int64_t>("buffer-frames")
        );

        if (delay <= 0) {
            PlayLayer::handleButton(down, button, isPlayer1);
            return;
        }

        // Queue both press and release, preserving order and hold duration.
        // This avoids forwarding a release before its delayed press.
        g_events.push_back({down, button, isPlayer1, delay});
    }

    void update(float dt) {
        PlayLayer::update(dt);

        // One countdown step per game update. Events retain FIFO order.
        for (auto& event : g_events) {
            if (event.framesLeft > 0) {
                --event.framesLeft;
            }
        }

        while (!g_events.empty() && g_events.front().framesLeft <= 0) {
            auto event = g_events.front();
            g_events.pop_front();

            g_replaying = true;
            PlayLayer::handleButton(event.down, event.button, event.player1);
            g_replaying = false;
        }
    }

    void resetLevel() {
        g_events.clear();
        g_replaying = false;
        PlayLayer::resetLevel();
    }
};
