cmake_minimum_required(VERSION 3.15)

project(sunvox_juce_v2 VERSION 2.0.0)

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
juce_add_plugin(sunvox_juce_v2
    COMPANY_NAME "SunVox"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD FALSE
    PLUGIN_MANUFACTURER_CODE Svox
    PLUGIN_CODE Svx2
    FORMATS VST3 AU Standalone
    PRODUCT_NAME "sunvox_juce_v2"
)

# Add source files
target_sources(sunvox_juce_v2
    PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginEditor.cpp
)

# SunVox library path
set(SUNVOX_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/sunvox_lib/sunvox_lib/headers")
set(SUNVOX_LIB_DIR "${CMAKE_SOURCE_DIR}/sunvox_lib/sunvox_lib/linux/lib_x86_64")

# Add SunVox include directory
target_include_directories(sunvox_juce_v2
    PRIVATE
        ${SUNVOX_INCLUDE_DIR}
)

# Link JUCE modules and SunVox
target_link_libraries(sunvox_juce_v2
    PRIVATE
        juce::juce_audio_utils
        ${SUNVOX_LIB_DIR}/sunvox.so
        dl
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

# Compile definitions
target_compile_definitions(sunvox_juce_v2
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

# Define SUNVOX_MAIN only for PluginProcessor.cpp
set_source_files_properties(Source/PluginProcessor.cpp
    PROPERTIES COMPILE_DEFINITIONS "SUNVOX_MAIN=1"
)
