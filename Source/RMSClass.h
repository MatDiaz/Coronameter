/*
  ==============================================================================

    RMSClass.h
    Created: 16 Apr 2020 5:43:01pm
    Author:  WATEO

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class RMSClass
{
public:
	RMSClass() 
	{
		dataSize = 0;
		counter = 0;
		sum = 0;
		first = true;
	}
	~RMSClass() {}


	void dataInit(float sampleRate, float segundos)
	{
		dataSize = (int)(sampleRate * segundos);

		Data.resize(dataSize);

		for (int i = 0; i < dataSize; ++i)
		{
			Data.set(i, 0);
		}
	}

	void setData(float sample)
	{	
		sum -= Data[counter];
		Data.set(counter, powf(sample, 2.0));
		sum += powf(sample, 2.0);

		counter++;
		if (counter >= dataSize) 
		{ counter = 0; }
	}

	float getSum()
	{
		return sum;
	}

	float getDataSize()
	{
		return dataSize;
	}

	float* getArrayOfData()
	{
		return Data.getRawDataPointer();
	}

private:
	int counter;
	bool first;
	float sum;

	int dataSize;
	Array<float> Data;
};