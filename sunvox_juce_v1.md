# sunvox_juce_v1

## Overview

**sunvox_juce_v1** is the first iteration of a JUCE-based plugin designed to integrate SunVox DSP capabilities. This version fulfills **Objective #1** from plan.md: creating the simplest possible JUCE plugin that loads successfully.

**Version**: 1.0.0
**Status**: Complete - Basic plugin that loads (no DSP processing)
**Created**: November 6, 2025

## Intent

The purpose of sunvox_juce_v1 is to establish a working JUCE plugin foundation that:
- Successfully compiles and builds
- Loads in DAWs as a VST3 plugin
- Runs as a standalone application
- Provides a clean architecture for future SunVox DSP integration (v2)

This version intentionally **does not** process audio - it passes silence. It serves as proof-of-concept that the JUCE framework is properly configured and the plugin infrastructure works.

## Architecture

### Core Components

1. **PluginProcessor** (`Source/PluginProcessor.h/cpp`)
   - Inherits from `juce::AudioProcessor`
   - Handles audio callback (currently passes silence)
   - Manages MIDI input (accepted but not processed)
   - Configures as stereo output synth

2. **PluginEditor** (`Source/PluginEditor.h/cpp`)
   - Inherits from `juce::AudioProcessorEditor`
   - Provides basic GUI (400x300 pixels)
   - Displays plugin name and status

3. **CMakeLists.txt**
   - Fetches JUCE 7.0.12 from GitHub
   - Configures plugin as VST3/AU/Standalone
   - Links necessary JUCE modules

### Plugin Configuration

- **Product Name**: sunvox_juce_v1
- **Company**: SunVox
- **Plugin Type**: Synthesizer
- **MIDI Input**: Yes
- **MIDI Output**: No
- **Audio Output**: Stereo (2 channels)
- **Plugin Code**: Svx1
- **Manufacturer Code**: Svox

## Features

### Current Capabilities
- ✅ Loads in DAW hosts as VST3
- ✅ Runs as standalone application
- ✅ Accepts MIDI input
- ✅ Provides GUI window
- ✅ Properly initializes/deinitializes
- ✅ Handles audio callbacks

### Limitations
- ❌ No audio processing (outputs silence)
- ❌ No SunVox DSP integration
- ❌ No sound generation
- ❌ No parameter controls

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
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### Build Output

**Artifacts** (in `build/sunvox_juce_v1_artefacts/`):
- `Standalone/sunvox_juce_v1` - Standalone executable (~22MB)
- `VST3/sunvox_juce_v1.vst3/` - VST3 plugin bundle (~20MB)

## Code Structure

```
sunvox_cpp_juce_test/
├── CMakeLists.txt              # Build configuration
├── Source/
│   ├── PluginProcessor.h       # Audio processor interface
│   ├── PluginProcessor.cpp     # Audio processor implementation
│   ├── PluginEditor.h          # GUI editor interface
│   └── PluginEditor.cpp        # GUI editor implementation
├── sunvox_lib/                 # SunVox library (not used in v1)
├── plan.md                     # Project objectives
├── research.md                 # SunVox integration notes
└── sunvox_juce_v1.md          # This documentation
```

## Key Functions

### Audio Processing
```cpp
void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
```
- **Current Behavior**: Clears all output channels (silence)
- **Purpose**: Placeholder for future SunVox DSP integration

### Initialization
```cpp
void prepareToPlay(double sampleRate, int samplesPerBlock)
```
- **Current Behavior**: No-op (accepts but ignores parameters)
- **Purpose**: Future SunVox initialization point

### GUI Rendering
```cpp
void paint(juce::Graphics& g)
```
- **Current Behavior**: Displays "sunvox_juce_v1" title and status
- **Purpose**: Basic visual confirmation plugin is loaded

## Testing

### Standalone Test
```bash
cd build/sunvox_juce_v1_artefacts/Standalone
./sunvox_juce_v1
```
Expected: Window opens showing plugin name and status. Audio engine runs (silent).

### VST3 Installation
```bash
# Copy to system VST3 directory
sudo cp -r build/sunvox_juce_v1_artefacts/VST3/sunvox_juce_v1.vst3 \
    ~/.vst3/
```
Expected: Plugin appears in DAW plugin list under "SunVox" manufacturer.

## Technical Notes

### JUCE Module Usage
- `juce_audio_processors` - Core plugin framework
- `juce_audio_utils` - Audio utilities
- `juce_gui_basics` - GUI rendering
- `juce_events` - Event handling
- `juce_core` - Core utilities
- `juce_audio_devices` - Audio I/O
- `juce_audio_formats` - File formats
- `juce_graphics` - Graphics rendering

### Compiler Warnings
During build, you may see:
```
warning: 'virtual void juce::AudioProcessor::processBlock(juce::AudioBuffer<double>&, ...)' was hidden
```
This is expected - we only implement the float version of processBlock.

## Next Steps (v2)

sunvox_juce_v2 will add:
1. SunVox library integration
2. Tone generation using SunVox DSP
3. Audio output (440Hz test tone or similar)
4. Proper lifecycle management (sv_init, sv_deinit)

See `research.md` for integration guidance from SunVox developer.

## References

- **Plan**: plan.md (Objective #1)
- **Research**: research.md (SunVox + JUCE integration notes)
- **JUCE Framework**: https://github.com/juce-framework/JUCE
- **SunVox Library**: sunvox_lib/
