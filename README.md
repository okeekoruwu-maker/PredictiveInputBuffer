# Predictive Input Buffer — Android / Geometry Dash 2.2083

## What this prototype does
- Targets Geometry Dash Android 2.2083.
- Provides an on/off setting.
- Provides a frame delay from 0 to 3 game updates.
- Queues presses and releases in order, so a release is not sent before its delayed press.
- Clears queued inputs when the level resets.

## Important limitations
This is a **source project**, not a compiled or device-tested `.geode` package. It delays and replays events; it does not predict future touches, identify valid jump windows, or guarantee frame-perfect inputs. Added delay may make controls feel worse. Test in practice mode and keep buffering disabled by default until verified.

The hook signature and Geode version must be checked against the exact Geode SDK installed for your Geometry Dash build. `geode` in `mod.json` is set to `v5.0.0` as a starting point; change it to the exact SDK/loader version you build against if different.

## Build outline
1. Install the Geode SDK/CLI and Android build dependencies.
2. Open this project with the matching Geode development setup.
3. Verify `mod.json` with the Geode VS Code extension / CLI.
4. Build for Android 2.2083 using the current official Geode build workflow.
5. Install the resulting `.geode` package through Geode and test in Practice mode first.

Official documentation:
- https://docs.geode-sdk.org/mods/configuring/
- https://docs.geode-sdk.org/mods/settings/
