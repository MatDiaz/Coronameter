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
		g.setColour(Colours::white);
		g.drawRect(0, 0, getWidth(), getHeight());

		uint8 R2, G2, B2;
		R2 = 255 * ampl; G2 = 255 * (1 - ampl); B2 = 0;

		g.setColour(Colour(R2, G2, B2));
		g.fillRect(1, 1, getWidth() - 2, (int)abs(getHeight()* ampl));
	}

	void setAmp(float newAmp)
	{
		ampl = newAmp;
		repaint();
	}

	void resized() override {}

private:
	float ampl;
};
