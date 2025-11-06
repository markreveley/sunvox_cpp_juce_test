cmake_minimum_required(VERSION 3.15)

project(SunVoxPlugin VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch JUCE from GitHub
include(FetchContent)
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG 7.0.12
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(JUCE)

# Create the plugin
juce_add_plugin(SunVoxPlugin
    COMPANY_NAME "SunVox"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD FALSE
    PLUGIN_MANUFACTURER_CODE Svox
    PLUGIN_CODE Svx1
    FORMATS VST3 AU Standalone
    PRODUCT_NAME "SunVox Plugin"
)

# Add source files
target_sources(SunVoxPlugin
    PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginEditor.cpp
)

# Link JUCE modules
target_link_libraries(SunVoxPlugin
    PRIVATE
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

# Compile definitions
target_compile_definitions(SunVoxPlugin
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)
