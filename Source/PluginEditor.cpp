/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CoronameterAudioProcessorEditor::CoronameterAudioProcessorEditor (CoronameterAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	peakTime.reset(new Slider());
	addAndMakeVisible(peakTime.get());
	peakTime->setRange(0, 100, 0.0);
	peakTime->setSliderStyle(Slider::LinearBar);
	peakTime->setColour(Slider::trackColourId, Colour(Colours::darkgrey));
	peakTime->onValueChange = [this] 
	{ processor.hold = (100 - peakTime->getValue()) / 100; };
	peakTime->setTextValueSuffix(" %");
	peakTime->setNumDecimalPlacesToDisplay(0);

	RMSTime.reset(new Slider());
	addAndMakeVisible(RMSTime.get());
	RMSTime->setRange(50, 5000, 0.0);
	RMSTime->setSliderStyle(Slider::LinearBar);
	RMSTime->setColour(Slider::textBoxTextColourId, Colour(Colours::white));
	RMSTime->setColour(Slider::trackColourId, Colour(Colours::darkgrey));
	RMSTime->setNumDecimalPlacesToDisplay(0);
	RMSTime->onValueChange = [this]
	{
		processor.RMSL.setTime(RMSTime->getValue());
		processor.RMSR.setTime(RMSTime->getValue());
	};

	RMSLabel.reset(new Label("RMS = 0 dB"));
	addAndMakeVisible(RMSLabel.get());
	RMSLabel->setText("RMS = 0 dB", dontSendNotification);
	RMSLabel->setColour(Label::ColourIds::textColourId, Colour(Colours::white));
	RMSLabel->setJustificationType(Justification::centred);
	
	peakLabel.reset(new Label("Peak = 0 dB"));
	addAndMakeVisible(peakLabel.get());
	peakLabel->setText("Peak = 0 dB", dontSendNotification);
	peakLabel->setColour(Label::ColourIds::textColourId, Colour(Colours::white));
	peakLabel->setJustificationType(Justification::centred);

	crestLabel.reset(new Label("Crest Factor = 0 dB"));
	addAndMakeVisible(crestLabel.get());
	crestLabel->setText("Crest Factor = 0 dB", dontSendNotification);
	crestLabel->setColour(Label::ColourIds::textColourId, Colour(Colours::white));
	crestLabel->setJustificationType(Justification::centred);

	actualizaBoton.reset(new TextButton());
	addAndMakeVisible(actualizaBoton.get());
	actualizaBoton->setButtonText("");
	actualizaBoton->setColour(TextButton::ColourIds::buttonColourId, Colour(0x00ffffff));
	actualizaBoton->onClick = [this] {processor.peakL = 0; processor.peakR = 0;};

	// Grafica de Espectro de Frecuencia
	frequencySpectrum.reset(new FrequencySpectrumClass());
	addAndMakeVisible(frequencySpectrum.get());

	// Medidor
	leftMeter.reset(new Meter());
	addAndMakeVisible(leftMeter.get());

	rightMeter.reset(new Meter());
	addAndMakeVisible(rightMeter.get());

	leftPeak.reset(new Meter());
	addAndMakeVisible(leftPeak.get());

	rightPeak.reset(new Meter());
	addAndMakeVisible(rightPeak.get());

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	setSize(1000, 700);

	frequencySpectrum->setBounds(0, 0, 700, 600);
	// Label
	RMSLabel->setBounds(700, 0, 300, 50);
	peakLabel->setBounds(700, 50, 300, 50);
	actualizaBoton->setBounds(700, 50, 300, 50);
	crestLabel->setBounds(700, 600, 300, 50);
	// Medidores
	leftMeter->setBounds(750, 120, 50, 460);  // Medidor RMS L
	leftPeak->setBounds(800, 120, 20, 460); // Medidor Peak L

	rightPeak->setBounds(880, 120, 20, 460); // Medidor Peak R
	rightMeter->setBounds(900, 120, 50, 460); // Medidor RMS R
	// Slider
	peakTime->setBounds(25, 620, 250, 25);
	RMSTime->setBounds(25, 655, 250, 25);

	startTimerHz(30);
}

CoronameterAudioProcessorEditor::~CoronameterAudioProcessorEditor()
{

}

//==============================================================================
void CoronameterAudioProcessorEditor::timerCallback()
{
	String peakL = String(20 * log10(processor.peakL), 1);
	String peakR = String(20 * log10(processor.peakR), 1);

	String RMSL = String(20 * log10(sqrt(processor.RMSL.getSum() / processor.RMSL.getSampTime())), 1);
	String RMSR = String(20 * log10(sqrt(processor.RMSR.getSum() / processor.RMSR.getSampTime())), 1);
	
	leftMeter->setAmp(sqrt(processor.RMSL.getSum() / processor.RMSL.getSampTime()));
	rightMeter->setAmp(sqrt(processor.RMSR.getSum() / processor.RMSR.getSampTime()));

	leftPeak->setAmp(processor.peakL);
	rightPeak->setAmp(processor.peakR);

	peakLabel->setText("PeakL :" + peakL + " dB " + "peakR: " + peakR + " dB", dontSendNotification);
	RMSLabel->setText("RMSL :" + RMSL + " dB " + "RMSR: " + RMSR + " dB", dontSendNotification);
}

void CoronameterAudioProcessorEditor::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(Colour(Colours::black));
}

void CoronameterAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
