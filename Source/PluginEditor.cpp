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
	RMSLabel.reset(new Label("RMS = 0 dB"));
	addAndMakeVisible(RMSLabel.get());
	RMSLabel->setText("RMS = 0 dB", dontSendNotification);
	RMSLabel->setColour(Label::ColourIds::textColourId, Colour(Colours::white));
	
	peakLabel.reset(new Label("Peak = 0 dB"));
	addAndMakeVisible(peakLabel.get());
	peakLabel->setText("Peak = 0 dB", dontSendNotification);
	peakLabel->setColour(Label::ColourIds::textColourId, Colour(Colours::white));

	crestLabel.reset(new Label("Crest Factor = 0 dB"));
	addAndMakeVisible(crestLabel.get());
	crestLabel->setText("Crest Factor = 0 dB", dontSendNotification);
	crestLabel->setColour(Label::ColourIds::textColourId, Colour(Colours::white));

	actualizaBoton.reset(new TextButton());
	addAndMakeVisible(actualizaBoton.get());
	actualizaBoton->setButtonText("");
	actualizaBoton->setColour(TextButton::ColourIds::buttonColourId, Colour(0x00ffffff));
	actualizaBoton->onClick = [this] {processor.peakL = 0; processor.peakR = 0;};

	// Grafica de Espectro de Frecuencia
	frequencySpectrum.reset(new FrequencySpectrumClass());
	addAndMakeVisible(frequencySpectrum.get());

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	setSize(1000, 700);

	frequencySpectrum->setBounds(0, 0, 1000, 500);
	RMSLabel->setBounds(0, 520, 1000, 60);
	peakLabel->setBounds(0, 580, 1000, 60);
	crestLabel->setBounds(0, 660, 1000, 60);
	actualizaBoton->setBounds(0, 580, 1000, 60);

	startTimerHz(30);
}

CoronameterAudioProcessorEditor::~CoronameterAudioProcessorEditor()
{

}

//==============================================================================
void CoronameterAudioProcessorEditor::timerCallback()
{
	String peakL = String(20 * log10(processor.peakL), 2);
	String peakR = String(20 * log10(processor.peakR), 2);

	String RMSL = String(20 * log10(sqrt(processor.RMSL.getSum() / processor.RMSL.getDataSize())));
	String RMSR = String(20 * log10(sqrt(processor.RMSR.getSum() / processor.RMSR.getDataSize())));
	
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
