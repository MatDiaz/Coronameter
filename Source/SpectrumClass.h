/*
  ==============================================================================

    SpectrumClass.h
    Created: 17 Jun 2020 11:44:47am
    Author:  WATEO

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class SpectrumClass : public Component
{
public:
	SpectrumClass(int order, int samples) :
		FFTProcessor(order), window(samples, dsp::WindowingFunction<float>::WindowingMethod::hamming),
		bufferSize(samples)
	{
		data = new float[samples * 2];
		zeromem(data, sizeof(float) * samples * 2);
	}

	~SpectrumClass()
	{

	}

	void receiveAndProcess(float* buffer)
	{
		memcpy(data, buffer, sizeof(float) * bufferSize);

		window.multiplyWithWindowingTable(data, bufferSize);
		FFTProcessor.performFrequencyOnlyForwardTransform(data);

		for (auto i = 0; i < bufferSize; ++i)
		{
			data[i] /= (bufferSize / 2);
		}

		repaint();
	}

	void paint(Graphics& g) override
	{
		Path magnitude;

		magnitude.startNewSubPath(0, getHeight());

		float min = -80;
		float max = 0;

		float step = getWidth() / (bufferSize / 2);

		for (auto i = 0; i < floor(bufferSize / 2); ++i)
		{
			int posX = (log10(step * i) / log10(getWidth())) * (getWidth() - 1);
			posX = posX < 0 ? 0 : posX;

			float valueY = (1 - (jlimit(min, max, Decibels::gainToDecibels(data[i])) / min)) * getHeight();

			magnitude.lineTo(posX, getHeight() - valueY);
		}

		g.setColour(Colour(Colours::white));
		g.strokePath(magnitude, PathStrokeType(1.0f, PathStrokeType::curved));
	}

private:
	int bufferSize;
	float* data;
	dsp::FFT FFTProcessor;
	dsp::WindowingFunction<float> window;
};
