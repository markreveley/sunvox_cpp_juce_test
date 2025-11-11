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

**Current Status**: See [STATUS.md](STATUS.md) for detailed project state and build instructions.
