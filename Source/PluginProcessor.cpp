#include "PluginProcessor.h"
#include "PluginEditor.h"

SunVoxPluginAudioProcessor::SunVoxPluginAudioProcessor()
    : AudioProcessor(BusesProperties()
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
}

SunVoxPluginAudioProcessor::~SunVoxPluginAudioProcessor()
{
}

const juce::String SunVoxPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SunVoxPluginAudioProcessor::acceptsMidi() const
{
    return true;
}

bool SunVoxPluginAudioProcessor::producesMidi() const
{
    return false;
}

bool SunVoxPluginAudioProcessor::isMidiEffect() const
{
    return false;
}

double SunVoxPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SunVoxPluginAudioProcessor::getNumPrograms()
{
    return 1;
}

int SunVoxPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SunVoxPluginAudioProcessor::setCurrentProgram(int index)
{
    juce::ignoreUnused(index);
}

const juce::String SunVoxPluginAudioProcessor::getProgramName(int index)
{
    juce::ignoreUnused(index);
    return {};
}

void SunVoxPluginAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
    juce::ignoreUnused(index, newName);
}

void SunVoxPluginAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(sampleRate, samplesPerBlock);
}

void SunVoxPluginAudioProcessor::releaseResources()
{
}

bool SunVoxPluginAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    return true;
}

void SunVoxPluginAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                               juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused(midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Clear any output channels that don't contain input data
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // For now, just pass silence (Objective #1: simplest plugin that loads)
    // Objective #2 will add SunVox DSP here
}

bool SunVoxPluginAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* SunVoxPluginAudioProcessor::createEditor()
{
    return new SunVoxPluginAudioProcessorEditor(*this);
}

void SunVoxPluginAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    juce::ignoreUnused(destData);
}

void SunVoxPluginAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    juce::ignoreUnused(data, sizeInBytes);
}

// This creates new instances of the plugin
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SunVoxPluginAudioProcessor();
}
