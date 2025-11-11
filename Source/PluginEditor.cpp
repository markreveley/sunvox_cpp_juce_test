#include "PluginProcessor.h"
#include "PluginEditor.h"

SunVoxPluginAudioProcessorEditor::SunVoxPluginAudioProcessorEditor(SunVoxPluginAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(400, 300);
}

SunVoxPluginAudioProcessorEditor::~SunVoxPluginAudioProcessorEditor()
{
}

void SunVoxPluginAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(24.0f);
    g.drawFittedText("sunvox_juce_v2", getLocalBounds(), juce::Justification::centred, 1);

    g.setFont(14.0f);
    g.drawFittedText("Objective #2: SunVox DSP Integration",
                     getLocalBounds().reduced(20).translated(0, 40),
                     juce::Justification::centred, 1);

    g.setFont(12.0f);
    g.drawFittedText("Playing 440Hz tone via SunVox Generator",
                     getLocalBounds().reduced(20).translated(0, 70),
                     juce::Justification::centred, 1);
}

void SunVoxPluginAudioProcessorEditor::resized()
{
}
