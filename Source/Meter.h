/*
  ==============================================================================

    Meter.h
    Created: 23 Apr 2020 5:34:04pm
    Author:  WATEO

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class Meter: public Component
{
public:
	Meter() 
	{
		ampl = 0;
	}
	~Meter() {}

	void paint(Graphics& g) override
	{
		g.addTransform(AffineTransform::verticalFlip(getHeight()));

		// Rectangulo Medidor
		g.setColour(Colours::white);
		g.drawRect(0, 0, getWidth(), getHeight() * 0.93);

		g.setColour(Colour(Colours::green));
		g.fillRect(1, 1, getWidth() - 2, discretize(Decibels::gainToDecibels(ampl)));

		// Rectangulo Clipping
		Colour colorClip;
		colorClip = clip == true ? Colours::red : Colours::darkred;

		g.setColour(colorClip);
		g.fillRect(0, getHeight()*0.95, getWidth(), getHeight() * 0.05);
	}

	void mouseDown(const MouseEvent& event) override
	{
		if (event.mods.isLeftButtonDown())
		{
			clip = false;
		}
	}

	void setAmp(float newAmp)
	{
		ampl = newAmp;
		if (ampl >= 1.0f) { clip = true; }
		repaint();
	}

	int discretize(float dBValue)
	{
		dBValue = dBValue < -80 ? -80 : dBValue;
		dBValue = dBValue > 0 ? 0 : dBValue;
		return (getHeight() * 0.93 - 2)-((dBValue / -80) * (getHeight() * 0.93 - 2));
	}

	void resized() override {}

private:
	float ampl;
	bool clip = false;
};
 