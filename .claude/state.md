# Project State & Objectives

**Last Updated**: November 6, 2025
**Version**: 2.0.0 (sunvox_juce_v2)
**Status**: ✅ **CODE COMPLETE - READY FOR TESTING**

---

## ⚡ IMMEDIATE NEXT ACTION

**Your job is to help the user BUILD and TEST the completed plugins.**

### Step 1: Build
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

**Expected Output:**
- ✅ `build/sunvox_juce_v2_artefacts/Standalone/sunvox_juce_v2` (~22MB)
- ✅ `build/sunvox_juce_v2_artefacts/VST3/sunvox_juce_v2.vst3/` (~20MB)

### Step 2: Test Standalone
```bash
./build/sunvox_juce_v2_artefacts/Standalone/sunvox_juce_v2
```

**Expected Result:**
- ✅ Window opens displaying "sunvox_juce_v2"
- ✅ **You hear a continuous 440Hz tone** (A4 note)
- ✅ Tone starts playing immediately

### Step 3: Test VST3 (Optional)
```bash
# Install to system
cp -r build/sunvox_juce_v2_artefacts/VST3/sunvox_juce_v2.vst3 ~/.vst3/

# Then load in DAW (Reaper, Ableton, etc.)
```

**Expected Result:**
- ✅ Plugin appears under "SunVox" manufacturer
- ✅ Loads without errors
- ✅ Generates 440Hz tone when track is active

---

## 📊 Objectives

**Project Goal**: Create the most bare bones version of a VST plugin using JUCE framework which contains DSP code from SunVox tracker.

### Objective #1: ✅ COMPLETE
**Create the simplest possible JUCE plugin that loads**

- **Status**: COMPLETE (11/6/25)
- **Implementation**: sunvox_juce_v1
- **Documentation**: [sunvox_juce_v1.md](../sunvox_juce_v1.md)
- **Output**: VST3 + Standalone plugin that loads successfully (outputs silence)

### Objective #2: ✅ COMPLETE
**Create the simplest variant that loads SunVox DSP and emits a tone**

- **Status**: COMPLETE (11/6/25)
- **Implementation**: sunvox_juce_v2
- **Documentation**: [sunvox_juce_v2.md](../sunvox_juce_v2.md)
- **Output**: VST3 + Standalone plugin with SunVox Generator generating 440Hz tone

---

## 🎯 What's Been Built

### sunvox_juce_v2 (Current)
- Full SunVox library integration
- Dynamic library loading (`sunvox.so`)
- Generator module creating 440Hz tone
- Audio format conversion (interleaved ↔ planar)
- Proper lifecycle management (init/shutdown)
- Builds as VST3 and Standalone

### sunvox_juce_v1 (Previous)
- Basic JUCE plugin infrastructure
- Loads successfully but outputs silence
- Foundation for v2

---

## 🚨 Common Issues

### Build fails with "JUCE not found"
```bash
# Install dependencies first:
sudo apt-get install -y libasound2-dev libfreetype6-dev \
  libx11-dev libxinerama-dev libxrandr-dev libxcursor-dev libgl1-mesa-dev
```

### No sound output
- Check audio device is not muted
- Try different audio backend
- Check debug output for "SunVox initialized" message

### "sunvox.so not found"
- Library is at: `sunvox_lib/sunvox_lib/linux/lib_x86_64/sunvox.so`
- CMake should handle this automatically
- Check CMakeLists.txt SUNVOX_LIB_DIR is correct

---

## 💡 For New Claude Instances

### Your Mission
The code is **ALREADY COMPLETE**. Do NOT write new code unless asked.

**Your primary job: Help the user build and test.**

### What to Do
1. ✅ Guide user through build process above
2. ✅ Run the standalone plugin with them
3. ✅ Verify they hear the 440Hz tone
4. ✅ Troubleshoot any build/test failures
5. ✅ Report success or specific errors

### What NOT to Do
- ❌ Start planning new features
- ❌ Ask "what should we build next?"
- ❌ Modify existing code without user request
- ❌ Ignore the testing priority

### Quick Reference Files
- **Architecture**: [context.md](context.md)
- **Workflows**: [workflows.md](workflows.md)
- **Implementation v2**: [../sunvox_juce_v2.md](../sunvox_juce_v2.md)
- **Research notes**: [../research.md](../research.md)

---

## ✅ Test Validation Checklist

When testing is complete, verify:
- [ ] Build completed without errors
- [ ] Standalone executable runs
- [ ] 440Hz tone is audible
- [ ] Tone is continuous (not stopping/starting)
- [ ] GUI window shows "sunvox_juce_v2"
- [ ] No crashes or errors in console
- [ ] VST3 plugin installs (optional)
- [ ] VST3 loads in DAW (optional)

---

## 🔮 Future Objectives (After Testing)

**Note**: These are potential future directions. Current priority is **testing v2** to validate the integration approach.

### Objective #3: MIDI Input Processing (v3)
**Goal**: Process MIDI input to control note generation

**Features**:
- Respond to MIDI Note ON/OFF events
- Map MIDI note numbers to SunVox notes
- Velocity control
- Basic envelope (ADSR)
- Polyphony (multiple simultaneous notes)

**Technical**:
- Process `MidiBuffer` in `processBlock()`
- Send `sv_send_event()` for each MIDI message
- Track active notes for note OFF
- Manage multiple Generator instances or use polyphonic module

### Objective #4: Parameter Controls (v3)
**Goal**: Expose Generator parameters to DAW

**Features**:
- Volume control
- Waveform selection (sine, square, saw, triangle)
- Filter cutoff/resonance
- Attack/Decay/Sustain/Release controls

**Technical**:
- JUCE `AudioProcessorValueTreeState`
- Parameter automation support
- `sv_set_module_ctl_value()` for SunVox parameters
- GUI sliders/knobs

### Objective #5: Advanced Synthesis (v4)
**Goal**: Multiple modules and effect chains

**Features**:
- Multiple SunVox modules (not just Generator)
- Effect modules (reverb, delay, filter, distortion)
- Module routing/patching
- Save/load module configurations

**Technical**:
- `sv_new_module()` for various module types
- `sv_connect_module()` for routing
- Module management system
- Preset system

### Objective #6: Pattern Support (v4)
**Goal**: Load and play SunVox patterns/projects

**Features**:
- Load .sunvox files
- Pattern playback
- Timeline/sequencer integration
- DAW tempo sync

**Technical**:
- `sv_load()` for project files
- `sv_play()` for pattern playback
- Sync with DAW transport
- Pattern editing (future)

---

**Reference**: See [research.md](../research.md) for notes from the SunVox developer about the viability of this approach.
