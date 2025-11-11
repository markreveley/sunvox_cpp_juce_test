# sunvox_juce_v2

## Overview

**sunvox_juce_v2** is the second iteration of the JUCE-based plugin, implementing **Objective #2** from plan.md: integrating SunVox DSP to emit a continuous tone. This version successfully demonstrates the integration of the SunVox audio engine within a JUCE plugin architecture.

**Version**: 2.0.0
**Status**: Complete - SunVox DSP integrated with tone generation
**Created**: November 6, 2025
**Builds on**: sunvox_juce_v1

## Intent

The purpose of sunvox_juce_v2 is to:
- Integrate the SunVox library with JUCE's audio processing pipeline
- Demonstrate working audio synthesis using SunVox's Generator module
- Establish the foundation for future MIDI-controlled synthesis
- Validate the integration approach documented in research.md

This version plays a continuous 440Hz tone (A4 note) using SunVox's built-in Generator module, proving that the SunVox DSP engine can successfully operate within a JUCE plugin environment.

## Architecture

### Core Components

1. **PluginProcessor** (`Source/PluginProcessor.h/cpp`)
   - Manages SunVox lifecycle (initialization, shutdown)
   - Handles audio callback integration
   - Creates and configures SunVox Generator module
   - Converts between JUCE's planar and SunVox's interleaved audio formats
   - Sends Note ON events to trigger tone generation

2. **PluginEditor** (`Source/PluginEditor.h/cpp`)
   - Displays plugin status and current functionality
   - Shows "Playing 440Hz tone via SunVox Generator" message

3. **CMakeLists.txt**
   - Links SunVox shared library (sunvox.so)
   - Includes SunVox headers
   - Defines SUNVOX_MAIN for dynamic library loading

4. **SunVox Integration**
   - Uses dynamic library loading (sv_load_dll)
   - Operates in offline mode (SV_INIT_FLAG_OFFLINE)
   - Float32 audio format (SV_INIT_FLAG_AUDIO_FLOAT32)
   - Single-threaded mode (SV_INIT_FLAG_ONE_THREAD)

### Plugin Configuration

- **Product Name**: sunvox_juce_v2
- **Company**: SunVox
- **Plugin Type**: Synthesizer
- **MIDI Input**: Yes (not yet processed)
- **MIDI Output**: No
- **Audio Output**: Stereo (2 channels)
- **Plugin Code**: Svx2
- **Manufacturer Code**: Svox

## Features

### Current Capabilities
- ✅ Loads in DAW hosts as VST3
- ✅ Runs as standalone application
- ✅ Initializes SunVox engine
- ✅ Creates SunVox Generator module
- ✅ Generates 440Hz tone (MIDI note 69 - A4)
- ✅ Processes audio through SunVox DSP
- ✅ Converts between audio formats (interleaved ↔ planar)
- ✅ Properly manages SunVox lifecycle

### Limitations
- ❌ No MIDI processing (fixed note only)
- ❌ No parameter controls
- ❌ No envelope shaping (continuous tone)
- ❌ Single Generator module only
- ❌ No pattern/sequence support

## Technical Implementation

### SunVox Initialization

```cpp
void initSunVox(double sampleRate)
{
    // Load dynamic library
    sv_load_dll();

    // Initialize in offline mode for plugin use
    int flags = SV_INIT_FLAG_OFFLINE |
                SV_INIT_FLAG_AUDIO_FLOAT32 |
                SV_INIT_FLAG_ONE_THREAD;
    sv_init(nullptr, sampleRate, 2, flags);

    // Open slot 0
    sv_open_slot(0);

    // Create Generator module and connect to output
    generatorModuleNum = sv_new_module(0, "Generator", "Tone Generator", 0, 0, 0);
    sv_connect_module(0, generatorModuleNum, 0);

    // Send Note ON (440Hz / A4 / MIDI note 69)
    sv_send_event(0, 0, 69, 128, generatorModuleNum + 1, 0, 0);
}
```

### Audio Processing

```cpp
void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    // Get audio from SunVox (interleaved: LRLRLR...)
    sv_audio_callback(tempBuffer.data(), numSamples, 0, sv_get_ticks());

    // Convert from interleaved to planar format (JUCE)
    for (int i = 0; i < numSamples; ++i)
    {
        leftChannel[i] = tempBuffer[i * 2];      // L
        rightChannel[i] = tempBuffer[i * 2 + 1]; // R
    }
}
```

### Format Conversion

**SunVox Audio Format**: Interleaved stereo (LRLRLR...)
```
[L0, R0, L1, R1, L2, R2, ...]
```

**JUCE Audio Format**: Planar stereo
```
Left:  [L0, L1, L2, ...]
Right: [R0, R1, R2, ...]
```

The plugin converts between these formats in the processBlock() method.

## Build Instructions

### Prerequisites

**System Dependencies** (Linux):
```bash
sudo apt-get install -y \
    libasound2-dev \
    libfreetype6-dev \
    libx11-dev \
    libxinerama-dev \
    libxrandr-dev \
    libxcursor-dev \
    libgl1-mesa-dev
```

**Build Tools**:
- CMake 3.15 or higher
- C++17 compatible compiler (GCC 13.3.0 tested)
- Git (for fetching JUCE)

### Build Steps

```bash
# From project root
rm -rf build  # Clean previous build
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### Build Output

**Artifacts** (in `build/sunvox_juce_v2_artefacts/`):
- `Standalone/sunvox_juce_v2` - Standalone executable (~22MB)
- `VST3/sunvox_juce_v2.vst3/` - VST3 plugin bundle (~20MB)

## Code Structure

```
sunvox_cpp_juce_test/
├── CMakeLists.txt              # Build configuration with SunVox linking
├── Source/
│   ├── PluginProcessor.h       # Audio processor with SunVox integration
│   ├── PluginProcessor.cpp     # SunVox lifecycle and audio processing
│   ├── PluginEditor.h          # GUI editor interface
│   └── PluginEditor.cpp        # GUI showing status
├── sunvox_lib/                 # SunVox library
│   └── sunvox_lib/
│       ├── headers/sunvox.h    # SunVox API
│       └── linux/lib_x86_64/
│           └── sunvox.so       # SunVox shared library
├── plan.md                     # Project objectives
├── research.md                 # SunVox integration notes
├── sunvox_juce_v1.md          # v1 documentation
└── sunvox_juce_v2.md          # This documentation
```

## Key Differences from v1

| Feature | v1 | v2 |
|---------|----|----|
| Audio Output | Silence | 440Hz Tone |
| SunVox Integration | None | Full |
| Dynamic Library | Not used | sunvox.so linked |
| Module Creation | N/A | Generator module |
| Audio Processing | Pass-through | SunVox DSP |
| Format Conversion | N/A | Interleaved ↔ Planar |

## Testing

### Standalone Test
```bash
cd build/sunvox_juce_v2_artefacts/Standalone
./sunvox_juce_v2
```
**Expected**: Window opens, plugin displays status, and you hear a continuous 440Hz tone.

### VST3 Installation
```bash
# Copy to system VST3 directory
sudo cp -r build/sunvox_juce_v2_artefacts/VST3/sunvox_juce_v2.vst3 \
    ~/.vst3/
```
**Expected**: Plugin appears in DAW, loads successfully, and generates 440Hz tone when track is active.

### Debug Output

The plugin logs to debug console:
- "SunVox initialized. Version: X.X.X"
- "Generator module created: N"
- "SunVox fully initialized and playing tone"
- "SunVox shut down" (on close)

## Technical Notes

### SunVox API Usage

**Initialization Sequence**:
1. `sv_load_dll()` - Load shared library
2. `sv_init()` - Initialize engine with sample rate and flags
3. `sv_open_slot(0)` - Open audio slot
4. `sv_new_module()` - Create Generator module
5. `sv_connect_module()` - Connect to main output
6. `sv_send_event()` - Trigger note ON

**Audio Callback**:
- `sv_audio_callback(buffer, frames, latency, ticks)` - Get audio

**Shutdown Sequence**:
1. `sv_send_event()` - Send note OFF
2. `sv_close_slot(0)` - Close audio slot
3. `sv_deinit()` - Shutdown engine
4. `sv_unload_dll()` - Unload library

### JUCE Module Usage
- `juce_audio_processors` - Core plugin framework
- `juce_audio_utils` - Audio utilities
- `juce_gui_basics` - GUI rendering
- `juce_events` - Event handling
- `juce_core` - Core utilities

### Compiler Notes

**SUNVOX_MAIN Definition**:
- Must be defined in exactly ONE compilation unit
- Set via `set_source_files_properties()` in CMake
- Enables dynamic library loading implementation
- Including in multiple files causes "multiple definition" linker errors

**Required Headers**:
- `<dlfcn.h>` - For dlopen/dlsym/dlclose (before sunvox.h)
- `sunvox.h` - SunVox API declarations

### Performance Characteristics

- **Sample Rate**: Adaptive (matches host)
- **Buffer Size**: Adaptive (matches host)
- **Latency**: Low (offline mode, no buffering)
- **CPU Usage**: Minimal (single Generator module)
- **Memory**: ~22MB (includes JUCE + SunVox)

## Integration Validation

This implementation successfully validates the integration approach from research.md:

✅ **Dynamic Library Loading**: Working via sv_load_dll()
✅ **Offline Mode**: Correct flag usage (SV_INIT_FLAG_OFFLINE)
✅ **Audio Callback**: sv_audio_callback() integrates with JUCE
✅ **Module Creation**: Generator module creates and connects
✅ **Event System**: sv_send_event() triggers notes
✅ **Format Conversion**: Interleaved ↔ Planar conversion working

## Known Issues

1. **Continuous Tone**: Note stays on indefinitely (no envelope)
2. **No MIDI**: MIDI input not yet processed
3. **Fixed Note**: Always plays A4 (440Hz)
4. **No UI Controls**: Cannot change parameters

## Future Enhancements (v3+)

Potential next steps:
- Process MIDI input for note control
- Add envelope (ADSR) to Generator module
- Implement parameter controls for Generator settings
- Support multiple simultaneous notes (polyphony)
- Add pattern/sequence support
- Load SunVox project files (.sunvox)
- Implement effect modules (reverb, delay, etc.)
- Add preset management

## References

- **Plan**: plan.md (Objective #2)
- **Research**: research.md (SunVox + JUCE integration notes from developer)
- **Previous Version**: sunvox_juce_v1.md
- **JUCE Framework**: https://github.com/juce-framework/JUCE
- **SunVox Library**: sunvox_lib/
- **SunVox API**: sunvox_lib/sunvox_lib/headers/sunvox.h
- **Example Code**: sunvox_lib/sunvox_lib/examples/c/

## Validation

This implementation proves:
1. ✅ SunVox can operate within JUCE plugin architecture
2. ✅ Dynamic library loading works correctly
3. ✅ Audio callback integration is functional
4. ✅ Module creation and routing works
5. ✅ Audio format conversion is correct
6. ✅ Lifecycle management is proper

**Objective #2 Complete**: The plugin successfully integrates SunVox DSP and emits a tone.
