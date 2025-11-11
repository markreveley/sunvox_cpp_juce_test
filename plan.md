11/6/25 12:22pm

Our goal is to create the most bare bones version of a vst plugin using the JUCE framework which contains DSP code from SunVox the tracker (included in repo.)

## Objective #1: ✅ COMPLETE
Create the simplest possible JUCE plugin that loads

**Status**: COMPLETE (11/6/25)
**Implementation**: sunvox_juce_v1
**Documentation**: [sunvox_juce_v1.md](sunvox_juce_v1.md)
**Output**: VST3 + Standalone plugin that loads successfully (outputs silence)

## Objective #2: ✅ COMPLETE
Create the simplest possible variant of this initial loading plugin that loads the Sunvox DSP and emits a tone

**Status**: COMPLETE (11/6/25)
**Implementation**: sunvox_juce_v2
**Documentation**: [sunvox_juce_v2.md](sunvox_juce_v2.md)
**Output**: VST3 + Standalone plugin with SunVox Generator generating 440Hz tone

---

**Reference**: See [research.md](research.md) for notes from the SunVox developer about the viability of this idea.

**Current Status**: See [claude.md](claude.md) or [.claude/state.md](.claude/state.md) for detailed project state and build instructions.

---

## Future Objectives (After Testing)

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
