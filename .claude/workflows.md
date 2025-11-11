# Development Workflows

Common tasks and how to perform them on this project.

---

## 🔨 Build Workflows

### Clean Build
```bash
# Remove old build
rm -rf build

# Fresh build
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

**When to use**: After changing CMakeLists.txt, adding dependencies, or build issues

### Incremental Build
```bash
cd build
cmake --build . --config Release
```

**When to use**: After modifying source files only

### Debug Build
```bash
mkdir build-debug
cd build-debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
```

**When to use**: Need detailed error messages or want to use debugger

### Verify Build Output
```bash
# Check artifacts exist
ls -lh build/sunvox_juce_v2_artefacts/Standalone/
ls -lh build/sunvox_juce_v2_artefacts/VST3/

# Check file sizes (should be ~20-22MB)
du -h build/sunvox_juce_v2_artefacts/Standalone/sunvox_juce_v2
du -h build/sunvox_juce_v2_artefacts/VST3/sunvox_juce_v2.vst3/
```

---

## 🧪 Testing Workflows

### Test Standalone Plugin
```bash
# Run from build directory
./build/sunvox_juce_v2_artefacts/Standalone/sunvox_juce_v2

# Or with audio backend selection (if needed)
JUCE_ALSA_DEVICE=hw:0,0 ./build/sunvox_juce_v2_artefacts/Standalone/sunvox_juce_v2
```

**Expected**: Window opens, 440Hz tone plays continuously

**Common Issues**:
- No sound: Check audio device not muted, try different backend
- Crashes: Check sunvox.so is accessible, build in Debug mode for details

### Test VST3 Plugin

#### Install
```bash
# Copy to user VST3 directory
mkdir -p ~/.vst3
cp -r build/sunvox_juce_v2_artefacts/VST3/sunvox_juce_v2.vst3 ~/.vst3/

# Verify installation
ls -lh ~/.vst3/sunvox_juce_v2.vst3/
```

#### Load in DAW
```bash
# Example: Reaper
reaper &

# In Reaper:
# 1. Create new track
# 2. Add FX
# 3. Search for "sunvox"
# 4. Load plugin
# 5. Play track (should hear 440Hz tone)
```

**Expected**:
- Plugin appears under "SunVox" manufacturer
- Loads without errors
- Generates tone when track is active

### Verify Audio Output
```bash
# Install audio analysis tools if needed
sudo apt-get install audacity

# Record output and verify:
# - Frequency: ~440Hz
# - Waveform: Sine wave
# - Amplitude: Consistent
# - No artifacts: Clean tone
```

---

## 🐛 Debugging Workflows

### Enable Debug Logging
Edit `Source/PluginProcessor.cpp`:
```cpp
// Add at top
#define DEBUG_SUNVOX 1

// Then use throughout:
#if DEBUG_SUNVOX
    DBG("SunVox status: " + juce::String(someValue));
#endif
```

Rebuild and check console output.

### Check SunVox Initialization
```bash
# Run standalone with stderr capture
./build/sunvox_juce_v2_artefacts/Standalone/sunvox_juce_v2 2>&1 | tee sunvox.log

# Check log for:
# - "SunVox initialized"
# - "Generator module created"
# - Version number
```

### Debug Build Failures

#### Missing Dependencies
```bash
# Install JUCE dependencies
sudo apt-get install -y \
    libasound2-dev \
    libfreetype6-dev \
    libx11-dev \
    libxinerama-dev \
    libxrandr-dev \
    libxcursor-dev \
    libgl1-mesa-dev

# Verify installations
dpkg -l | grep -E "alsa|freetype|x11|xinerama|xrandr|xcursor|mesa"
```

#### SunVox Library Not Found
```bash
# Check library exists
ls -lh sunvox_lib/sunvox_lib/linux/lib_x86_64/sunvox.so

# Check CMake found it
grep SUNVOX_LIB_DIR build/CMakeCache.txt

# Verify it's linked
ldd build/sunvox_juce_v2_artefacts/Standalone/sunvox_juce_v2 | grep sunvox
```

#### Compilation Errors
```bash
# Clean rebuild
rm -rf build
mkdir build && cd build

# Configure with verbose output
cmake .. --debug-output

# Build with verbose makefile
cmake --build . --config Release -- VERBOSE=1
```

---

## 📝 Documentation Workflows

### Update State After Changes
```bash
# Edit .claude/plan.md
nano .claude/plan.md

# Update:
# - "Last Updated" date
# - Status checkboxes if objectives changed
# - Test results if you ran tests
# - Known limitations if you found bugs
```

### Document New Feature
When adding a feature:

1. **Update architecture.md**: Add architecture section
2. **Update workflows.md**: Add "how to use" workflow
3. **Update plan.md**: Update status/objectives
4. **Update main docs**: Create/update feature-specific .md file

### Generate Documentation from Code
```bash
# If using Doxygen (future)
doxygen Doxyfile

# View generated docs
firefox docs/html/index.html
```

---

## 🔄 Git Workflows

### Commit Changes
```bash
# Stage files
git add Source/ CMakeLists.txt

# Commit with clear message
git commit -m "Add feature: <description>

Details:
- What changed
- Why it changed
- Testing done
"

# Push to branch
git push origin <branch-name>
```

### Check Project History
```bash
# See recent commits
git log --oneline --graph -10

# See what changed in a file
git log -p Source/PluginProcessor.cpp

# See changes between versions
git diff v1..v2
```

### Create Feature Branch
```bash
# From main
git checkout main
git pull

# Create branch
git checkout -b feature/midi-input

# Make changes, then push
git push -u origin feature/midi-input
```

---

## 🚀 Release Workflows

### Create Release Build
```bash
# Clean build
rm -rf build-release
mkdir build-release && cd build-release

# Configure for release
cmake -DCMAKE_BUILD_TYPE=Release ..

# Build
cmake --build . --config Release

# Verify
./sunvox_juce_v2_artefacts/Standalone/sunvox_juce_v2
```

### Package for Distribution
```bash
# Create package directory
mkdir -p sunvox_juce_v2-package

# Copy artifacts
cp -r build-release/sunvox_juce_v2_artefacts/* sunvox_juce_v2-package/

# Copy documentation
cp README.md sunvox_juce_v2.md sunvox_juce_v2-package/

# Create archive
tar -czf sunvox_juce_v2-v2.0.0-linux-x86_64.tar.gz sunvox_juce_v2-package/
```

### Version Bump
```bash
# Update version in CMakeLists.txt
sed -i 's/VERSION 2.0.0/VERSION 2.1.0/' CMakeLists.txt

# Update docs
sed -i 's/Version: 2.0.0/Version: 2.1.0/' .claude/plan.md
sed -i 's/v2.0.0/v2.1.0/' sunvox_juce_v2.md

# Commit version bump
git commit -am "Bump version to 2.1.0"
git tag v2.1.0
git push && git push --tags
```

---

## 🔍 Code Review Workflows

### Self-Review Checklist
Before committing:
- [ ] Code compiles without warnings
- [ ] Tested standalone build
- [ ] Tested VST3 build (if applicable)
- [ ] Updated documentation
- [ ] No debug print statements left in
- [ ] Comments explain "why" not "what"
- [ ] Follows existing code style

### Review Changes Before Commit
```bash
# See what changed
git diff

# See staged changes
git diff --cached

# Review specific file
git diff Source/PluginProcessor.cpp
```

---

## 🧹 Maintenance Workflows

### Clean Build Artifacts
```bash
# Remove build directory
rm -rf build build-debug build-release

# Remove CMake cache
rm -rf CMakeFiles/ CMakeCache.txt

# Remove editor temps
find . -name "*~" -delete
find . -name "*.swp" -delete
```

### Update Dependencies
```bash
# Update JUCE (in CMakeLists.txt)
# Change GIT_TAG to newer version
sed -i 's/GIT_TAG 7.0.12/GIT_TAG 7.0.13/' CMakeLists.txt

# Clean and rebuild
rm -rf build
mkdir build && cd build
cmake ..
cmake --build .
```

### Check for Memory Leaks
```bash
# Build with sanitizers
cmake -DCMAKE_BUILD_TYPE=Debug \
      -DCMAKE_CXX_FLAGS="-fsanitize=address -g" ..
cmake --build .

# Run and check for leaks
./sunvox_juce_v2_artefacts/Standalone/sunvox_juce_v2

# Should see "ASAN: no leaks detected" on exit
```

---

## 📊 Performance Workflows

### Profile Audio Callback
```bash
# Build with profiling
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
cmake --build .

# Run with profiler
perf record ./sunvox_juce_v2_artefacts/Standalone/sunvox_juce_v2

# Analyze results
perf report
```

### Measure CPU Usage
```bash
# Run plugin
./sunvox_juce_v2_artefacts/Standalone/sunvox_juce_v2 &
PID=$!

# Monitor CPU
top -p $PID

# Or detailed stats
perf stat -p $PID sleep 10

# Kill when done
kill $PID
```

---

## 🎯 Quick Reference

| Task | Command |
|------|---------|
| **Clean build** | `rm -rf build && mkdir build && cd build && cmake .. && cmake --build .` |
| **Test standalone** | `./build/sunvox_juce_v2_artefacts/Standalone/sunvox_juce_v2` |
| **Install VST3** | `cp -r build/sunvox_juce_v2_artefacts/VST3/sunvox_juce_v2.vst3 ~/.vst3/` |
| **Check logs** | `./sunvox_juce_v2 2>&1 \| tee debug.log` |
| **Verify library** | `ldd ./sunvox_juce_v2 \| grep sunvox` |

---

**Last Updated**: November 6, 2025
