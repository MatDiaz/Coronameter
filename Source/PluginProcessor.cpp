/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CoronameterAudioProcessor::CoronameterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	peakL = 0;
	peakR = 0;
}

CoronameterAudioProcessor::~CoronameterAudioProcessor()
{
}

//==============================================================================
const String CoronameterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CoronameterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CoronameterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CoronameterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CoronameterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CoronameterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CoronameterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CoronameterAudioProcessor::setCurrentProgram (int index)
{
}

const String CoronameterAudioProcessor::getProgramName (int index)
{
    return {};
}

void CoronameterAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void CoronameterAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	peakL = 0;
	peakR = 0;
}

void CoronameterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CoronameterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void CoronameterAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

	for (int channel = 0; channel < totalNumInputChannels; ++channel)
	{
		auto* channelData = buffer.getWritePointer(channel);
		
		for (auto sample = 0; sample < buffer.getNumSamples(); ++sample)
		{
			if (std::abs(channelData[sample]) > peakL && channel == 0)
			{
				peakL = std::abs(channelData[sample]);
			}
			else if (std::abs(channelData[sample]) > peakR && channel == 1)
			{
				peakR = std::abs(channelData[sample]);
			}
		}
    }
}

//==============================================================================
bool CoronameterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* CoronameterAudioProcessor::createEditor()
{
    return new CoronameterAudioProcessorEditor (*this);
}

//==============================================================================
void CoronameterAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void CoronameterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CoronameterAudioProcessor();
}
