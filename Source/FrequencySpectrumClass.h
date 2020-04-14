/*
  ==============================================================================

    FrequencySpectrumClass.h
    Created: 26 Mar 2020 5:31:28pm
    Author:  WATEO

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class FrequencySpectrumClass    : public Component
{
public:
    FrequencySpectrumClass()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.

    }

    ~FrequencySpectrumClass()
    {
    }

    void paint (Graphics& g) override
    {
		g.fillAll(Colour(Colours::white));
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FrequencySpectrumClass)
};
