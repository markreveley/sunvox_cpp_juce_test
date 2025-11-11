#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "PluginProcessor.h"

class SunVoxPluginAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    SunVoxPluginAudioProcessorEditor(SunVoxPluginAudioProcessor&);
    ~SunVoxPluginAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    SunVoxPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SunVoxPluginAudioProcessorEditor)
};
