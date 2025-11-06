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
    g.drawFittedText("sunvox_juce_v1", getLocalBounds(), juce::Justification::centred, 1);

    g.setFont(14.0f);
    g.drawFittedText("Objective #1: Basic Plugin (No DSP)",
                     getLocalBounds().reduced(20).translated(0, 40),
                     juce::Justification::centred, 1);
}

void SunVoxPluginAudioProcessorEditor::resized()
{
}
