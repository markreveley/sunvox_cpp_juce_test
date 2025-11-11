#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <dlfcn.h>

SunVoxPluginAudioProcessor::SunVoxPluginAudioProcessor()
    : AudioProcessor(BusesProperties()
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true))
    , sunvoxInitialized(false)
    , generatorModuleNum(-1)
{
}

SunVoxPluginAudioProcessor::~SunVoxPluginAudioProcessor()
{
    shutdownSunVox();
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
    initSunVox(sampleRate);

    // Allocate temp buffer for interleaved audio (2 channels)
    tempBuffer.resize(samplesPerBlock * 2);
}

void SunVoxPluginAudioProcessor::releaseResources()
{
    shutdownSunVox();
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

    if (!sunvoxInitialized)
    {
        buffer.clear();
        return;
    }

    int numSamples = buffer.getNumSamples();

    // Get audio from SunVox (interleaved format: LRLRLR...)
    sv_audio_callback(tempBuffer.data(), numSamples, 0, sv_get_ticks());

    // Convert from interleaved to planar format
    float* leftChannel = buffer.getWritePointer(0);
    float* rightChannel = buffer.getWritePointer(1);

    for (int i = 0; i < numSamples; ++i)
    {
        leftChannel[i] = tempBuffer[i * 2];
        rightChannel[i] = tempBuffer[i * 2 + 1];
    }
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

void SunVoxPluginAudioProcessor::initSunVox(double sampleRate)
{
    if (sunvoxInitialized)
        return;

    // Load SunVox DLL
    if (sv_load_dll() != 0)
    {
        DBG("Failed to load SunVox DLL");
        return;
    }

    // Initialize SunVox in offline mode
    int flags = SV_INIT_FLAG_OFFLINE | SV_INIT_FLAG_AUDIO_FLOAT32 | SV_INIT_FLAG_ONE_THREAD;
    int ver = sv_init(nullptr, static_cast<int>(sampleRate), 2, flags);

    if (ver < 0)
    {
        DBG("Failed to initialize SunVox: " + juce::String(ver));
        sv_unload_dll();
        return;
    }

    DBG("SunVox initialized. Version: " + juce::String((ver >> 16) & 0xFF) + "." +
        juce::String((ver >> 8) & 0xFF) + "." + juce::String(ver & 0xFF));

    // Open slot 0
    sv_open_slot(0);

    // Create a Generator module and connect it to output
    sv_lock_slot(0);
    generatorModuleNum = sv_new_module(0, "Generator", "Tone Generator", 0, 0, 0);
    if (generatorModuleNum >= 0)
    {
        sv_connect_module(0, generatorModuleNum, 0);  // Connect to main output
        DBG("Generator module created: " + juce::String(generatorModuleNum));
    }
    sv_unlock_slot(0);

    // Send a Note ON event to play a 440Hz tone (A4)
    // Note 69 is A4 (440 Hz in standard tuning)
    sv_send_event(0, 0, 69, 128, generatorModuleNum + 1, 0, 0);

    sunvoxInitialized = true;
    DBG("SunVox fully initialized and playing tone");
}

void SunVoxPluginAudioProcessor::shutdownSunVox()
{
    if (!sunvoxInitialized)
        return;

    // Send note off
    sv_send_event(0, 0, NOTECMD_NOTE_OFF, 0, 0, 0, 0);

    // Close and cleanup
    sv_close_slot(0);
    sv_deinit();
    sv_unload_dll();

    sunvoxInitialized = false;
    generatorModuleNum = -1;
    DBG("SunVox shut down");
}

// This creates new instances of the plugin
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SunVoxPluginAudioProcessor();
}
