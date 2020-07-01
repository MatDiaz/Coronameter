/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "FrequencySpectrumClass.h"
#include "Meter.h"
#include "SpectrumClass.h"

//==============================================================================
/**
*/
class CoronameterAudioProcessorEditor  : public AudioProcessorEditor,
										 private Timer
{
public:
    CoronameterAudioProcessorEditor (CoronameterAudioProcessor&);
    ~CoronameterAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void timerCallback() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
	std::unique_ptr<Label> RMSLabel, peakLabel, crestLabel;
	std::unique_ptr<FrequencySpectrumClass> frequencySpectrum;
	std::unique_ptr<TextButton> actualizaBoton;
	std::unique_ptr<Meter> leftMeter, rightMeter, leftPeak, rightPeak;
	std::unique_ptr<Slider> peakTime, RMSTime;
	SpectrumClass spectrumMagnitude;
    CoronameterAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CoronameterAudioProcessorEditor)
};
