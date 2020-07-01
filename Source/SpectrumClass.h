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
		data.reset (new float[samples * 2]);
		zeromem(data.get(), sizeof(float) * samples * 2);
	}

	~SpectrumClass()
	{

	}

	void receiveAndProcess(float* buffer)
	{
		memcpy(data.get(), buffer, sizeof(float) * bufferSize);

		window.multiplyWithWindowingTable(data.get(), bufferSize);
		FFTProcessor.performFrequencyOnlyForwardTransform(data.get());

		FloatVectorOperations::multiply (data.get(), (1 / (float)(bufferSize / 2)), bufferSize);

		repaint();
	}

	void paint(Graphics& g) override
	{
		g.fillAll(Colour(Colours::grey));
		Path magnitude;

		magnitude.startNewSubPath(0, getHeight());

		float min = -80;
		float max = 0;

		float step = getWidth() / (float)(bufferSize / 2);


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
	std::unique_ptr<float[]> data;
	dsp::FFT FFTProcessor;
	dsp::WindowingFunction<float> window;
};
