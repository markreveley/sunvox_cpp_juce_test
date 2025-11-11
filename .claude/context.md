# Project Context & Architecture

## 🎯 Project Overview

**Name**: sunvox_juce_v2
**Type**: Audio Plugin (VST3/AU/Standalone)
**Purpose**: Integrate SunVox DSP engine into a JUCE plugin framework
**Status**: Both objectives complete (v1 and v2 exist)

### What This Project Is
A bare-bones JUCE audio plugin that loads the SunVox library and uses it to generate audio. Currently generates a continuous 440Hz tone using SunVox's Generator module.

### What This Project Is NOT
- Not a full-featured synthesizer
- Not a DAW
- Not a standalone SunVox wrapper
- Not intended for production use (proof of concept)

---

## 🏗️ Architecture

### High-Level Structure
```
┌─────────────────────────────────────────┐
│         JUCE Plugin Host (DAW)          │
└──────────────┬──────────────────────────┘
               │ Audio/MIDI
               ▼
┌─────────────────────────────────────────┐
│      SunVoxPluginAudioProcessor         │
│  ┌─────────────────────────────────┐   │
│  │   JUCE Audio Callback           │   │
│  │   (Planar: LL/RR format)        │   │
│  └──────────┬──────────────────────┘   │
│             │ Format Conversion         │
│  ┌──────────▼──────────────────────┐   │
│  │   SunVox Audio Engine           │   │
│  │   sv_audio_callback()           │   │
│  │   (Interleaved: LRLR format)    │   │
│  │  ┌──────────────────────────┐   │   │
│  │  │  Generator Module        │   │   │
│  │  │  (440Hz tone)            │   │   │
│  │  └──────────────────────────┘   │   │
│  └─────────────────────────────────┘   │
└─────────────────────────────────────────┘
```

### Key Components

#### 1. PluginProcessor (Source/PluginProcessor.cpp)
- **Role**: Bridge between JUCE and SunVox
- **Responsibilities**:
  - Initialize/shutdown SunVox engine
  - Manage SunVox lifecycle
  - Convert audio formats (interleaved ↔ planar)
  - Forward audio callbacks to SunVox
  - Create and manage SunVox modules

#### 2. SunVox Engine (sunvox_lib/)
- **Type**: Dynamic library (sunvox.so)
- **Mode**: Offline (SV_INIT_FLAG_OFFLINE)
- **Format**: Float32, Stereo, Interleaved
- **Slot**: Uses slot 0 (single instance)

#### 3. Generator Module
- **Type**: SunVox built-in synthesizer module
- **Configuration**: Default settings
- **Trigger**: Note ON (MIDI note 69 = 440Hz = A4)
- **Output**: Connected to main output (module 0)

#### 4. PluginEditor (Source/PluginEditor.cpp)
- **Role**: GUI display (minimal)
- **Shows**: Plugin name and status
- **Size**: 400x300 pixels
- **Interaction**: None (display only)

---

## 🔧 Technical Stack

### Frameworks & Libraries

| Component | Version | Purpose |
|-----------|---------|---------|
| **JUCE** | 7.0.12 | Plugin framework, audio I/O, GUI |
| **SunVox** | Latest | DSP engine, audio synthesis |
| **CMake** | 3.15+ | Build system |
| **C++** | C++17 | Language standard |

### Build System
- **Tool**: CMake
- **Generator**: Unix Makefiles (Linux)
- **Configuration**: Release build recommended
- **Targets**:
  - `sunvox_juce_v2` (shared library)
  - `sunvox_juce_v2_Standalone` (executable)
  - `sunvox_juce_v2_VST3` (plugin bundle)

---

## 🎨 Design Decisions

### Why JUCE?
- ✅ Industry standard for audio plugins
- ✅ Cross-platform (Windows, macOS, Linux)
- ✅ Handles VST3/AU/AAX formats automatically
- ✅ Mature audio callback system
- ✅ Built-in GUI framework

### Why SunVox Library?
- ✅ Modular synthesis engine
- ✅ C API available
- ✅ Lightweight and fast
- ✅ Well-documented
- ✅ Developer confirmed feasibility (see research.md)

### Why Offline Mode?
SunVox has two modes:
1. **Online**: SunVox manages its own audio thread
2. **Offline**: User calls sv_audio_callback() manually

**We use Offline because:**
- ✅ Plugin hosts manage audio threads (not us)
- ✅ Gives us control over when audio is generated
- ✅ Prevents thread conflicts
- ✅ Required for plugin architecture

### Why Float32?
- ✅ JUCE's native format
- ✅ Better precision than int16
- ✅ Industry standard for plugins
- ✅ Direct compatibility (no extra conversion)

### Why Single Threaded?
**Flag**: `SV_INIT_FLAG_ONE_THREAD`

**Reason**: Plugin hosts handle threading. We want SunVox to operate synchronously in the audio callback, not manage its own threads.

---

## 🔄 Audio Flow

### Format Conversion Pipeline

```
DAW Audio Thread
    ↓
JUCE processBlock() [Planar: float**]
    ↓
Copy to temp buffer
    ↓
sv_audio_callback() [Interleaved: float*]
    ↓
SunVox DSP Processing
    ↓
Return interleaved audio
    ↓
Convert back to planar
    ↓
Write to JUCE output buffer
    ↓
Return to DAW
```

### Buffer Format Details

**JUCE Format (Planar)**:
```cpp
buffer.getWritePointer(0) = [L0, L1, L2, L3, ...] // Left channel
buffer.getWritePointer(1) = [R0, R1, R2, R3, ...] // Right channel
```

**SunVox Format (Interleaved)**:
```cpp
tempBuffer = [L0, R0, L1, R1, L2, R2, L3, R3, ...] // Mixed
```

**Conversion Code**:
```cpp
// JUCE → SunVox (not used currently, future for input)
for (int i = 0; i < numSamples; ++i) {
    tempBuffer[i * 2] = leftChannel[i];
    tempBuffer[i * 2 + 1] = rightChannel[i];
}

// SunVox → JUCE (current usage)
for (int i = 0; i < numSamples; ++i) {
    leftChannel[i] = tempBuffer[i * 2];
    rightChannel[i] = tempBuffer[i * 2 + 1];
}
```

---

## 📦 Module System

### SunVox Module Hierarchy
```
Main Output (Module 0)
    ↑
    │ [Connected]
    │
Generator (Module N)
```

**Module 0**: Always exists, main audio output
**Generator**: Created dynamically, number assigned by SunVox

### Module Creation Pattern
```cpp
sv_lock_slot(0);  // Thread safety
int mod_num = sv_new_module(0, "Generator", "Name", x, y, z);
sv_connect_module(0, mod_num, 0);  // Connect to output
sv_unlock_slot(0);
```

---

## 🧪 Testing Strategy

### Validation Points

1. **Build Success**
   - CMake configures without errors
   - All targets compile
   - No linker errors

2. **Library Loading**
   - sunvox.so found and loaded
   - sv_load_dll() returns 0
   - sv_init() returns version number

3. **Module Creation**
   - Generator module created (mod_num >= 0)
   - Successfully connected to output
   - Debug log shows creation

4. **Audio Generation**
   - sv_audio_callback() returns non-zero
   - Buffer contains non-zero values
   - 440Hz tone is audible

5. **Lifecycle**
   - Plugin loads in DAW
   - Plugin shuts down cleanly
   - No memory leaks
   - No crashes on close

---

## 🐛 Known Limitations

### Current Version (v2)

1. **Fixed Note**: Always plays 440Hz, no MIDI processing
2. **No Envelope**: Note stays on continuously
3. **No Parameters**: Can't adjust Generator settings
4. **Single Note**: No polyphony support
5. **No Persistence**: Settings not saved between sessions

### Architectural Constraints

1. **Linux Only**: Build tested on Linux x86_64 only
2. **Dynamic Library**: Requires sunvox.so at runtime
3. **Single Slot**: Only uses SunVox slot 0
4. **No Input**: Doesn't process audio input (synth only)

---

## 🔮 Evolution Path

### v1 → v2 (DONE)
- Added SunVox library integration
- Implemented audio generation
- Format conversion working

### v2 → v3 (Future)
- MIDI input processing
- Note ON/OFF events
- Envelope control
- Parameter controls

### v3 → v4 (Future)
- Multiple modules
- Effect chains
- Pattern/sequence support
- Load .sunvox files

---

## 📚 Key Files Reference

| File | Purpose | Lines |
|------|---------|-------|
| `Source/PluginProcessor.cpp` | Main integration logic | ~210 |
| `Source/PluginProcessor.h` | Class definition | ~48 |
| `Source/PluginEditor.cpp` | GUI implementation | ~35 |
| `Source/PluginEditor.h` | GUI definition | ~20 |
| `CMakeLists.txt` | Build configuration | ~73 |
| `sunvox_lib/sunvox_lib/headers/sunvox.h` | SunVox API | ~1034 |

---

## 🎓 Learning Resources

### SunVox Integration
- **research.md**: Developer's guidance on integration
- **sunvox_lib/examples/c/**: Reference implementations
- **SunVox API docs**: In sunvox.h header comments

### JUCE
- **JUCE tutorials**: https://juce.com/learn/tutorials
- **AudioProcessor docs**: JUCE API reference
- **Plugin examples**: JUCE/examples/Plugins/

---

**Last Updated**: November 6, 2025
**Maintained By**: Claude instances working on this project
