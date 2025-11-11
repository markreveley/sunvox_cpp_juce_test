# Claude Code Context

**Auto-loaded on startup** - This file provides immediate context for Claude Code instances.

---

## ⚡ IMMEDIATE NEXT ACTION

**The code is COMPLETE. Your primary job is to help the user BUILD and TEST the existing plugins.**

### Build Command
```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

### Test Command
```bash
./build/sunvox_juce_v2_artefacts/Standalone/sunvox_juce_v2
```

**Expected Result**: You should hear a continuous 440Hz tone (A4 note).

---

## 📊 Project Status

| Objective | Status | Version |
|-----------|--------|---------|
| Basic JUCE plugin that loads | ✅ COMPLETE | sunvox_juce_v1 |
| SunVox DSP integration + tone | ✅ COMPLETE | sunvox_juce_v2 |

**Current Version**: 2.0.0 (sunvox_juce_v2)
**Last Updated**: November 6, 2025

---

## 🎯 What This Project Is

A JUCE audio plugin (VST3/Standalone) that integrates the SunVox DSP library to generate a 440Hz tone using SunVox's Generator module.

**Key Points**:
- Both objectives are DONE (see [.claude/plan.md](.claude/plan.md))
- Code compiles successfully on Linux x86_64
- Plugin generates audio (not silence)
- Ready for user testing

---

## 💡 Your Mission

### DO:
1. ✅ Help user build the plugin (guide through cmake process)
2. ✅ Help user test standalone executable
3. ✅ Verify they hear the 440Hz tone
4. ✅ Troubleshoot build/test failures
5. ✅ Answer questions about the implementation

### DON'T:
- ❌ Start planning new features (unless user asks)
- ❌ Modify existing code (it's working)
- ❌ Ask "what should we build?" (it's built)
- ❌ Ignore the testing priority

---

## 📁 Detailed Documentation

For deeper context, see:

- **[.claude/plan.md](.claude/plan.md)** - Project plan, objectives, test validation
- **[.claude/architecture.md](.claude/architecture.md)** - Architecture, design decisions
- **[.claude/workflows.md](.claude/workflows.md)** - Common tasks, how-tos
- **[sunvox_juce_v2.md](sunvox_juce_v2.md)** - Current implementation details
- **[research.md](research.md)** - SunVox integration research

---

## 🐛 Common Issues

### Build fails: "JUCE not found"
```bash
# Install dependencies
sudo apt-get install -y libasound2-dev libfreetype6-dev libx11-dev \
  libxinerama-dev libxrandr-dev libxcursor-dev libgl1-mesa-dev
```

### No sound output
- Check audio device not muted
- Verify with: `aplay -l` (shows audio devices)
- Try different audio backend: `JUCE_ALSA_DEVICE=hw:0,0 ./sunvox_juce_v2`

### "sunvox.so not found"
- Library location: `sunvox_lib/sunvox_lib/linux/lib_x86_64/sunvox.so`
- Check CMakeLists.txt SUNVOX_LIB_DIR setting
- Verify with: `ldd ./sunvox_juce_v2 | grep sunvox`

---

## 🏗️ Architecture Overview

```
JUCE Plugin (VST3/Standalone)
    ↓
PluginProcessor (processBlock)
    ↓
Format Conversion (Planar ↔ Interleaved)
    ↓
sv_audio_callback()
    ↓
SunVox Engine (Generator Module)
    ↓
440Hz Tone Output
```

**Key Technical Points**:
- SunVox in offline mode (SV_INIT_FLAG_OFFLINE)
- Float32 audio format
- Generator module plays MIDI note 69 (440Hz = A4)
- Audio format conversion between JUCE planar and SunVox interleaved

See [.claude/architecture.md](.claude/architecture.md) for full architecture details.

---

## ✅ Test Validation

When testing succeeds, verify:
- [ ] Build completed without errors
- [ ] Standalone executable runs
- [ ] 440Hz tone is audible and continuous
- [ ] GUI shows "sunvox_juce_v2"
- [ ] No crashes or console errors
- [ ] (Optional) VST3 loads in DAW

---

## 🔮 What's Next (Future)

**Only after successful testing**:
- v3: MIDI input processing
- v3: Envelope control (ADSR)
- v3: Parameter controls
- v4: Multiple modules, effects

**But first: Confirm v2 works!**

---

**This file is automatically loaded by Claude Code. Keep it updated with current project state.**
**Last verified working**: November 6, 2025 on Linux x86_64
