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
		Fs = 44100;
		timeInt = 3000;
		sampInt = (timeInt / 1000) * Fs;
	}
	~RMSClass() {}


	void dataInit(float sampleRate, float segundos)
	{
		Fs = sampleRate;
		dataSize = (int)(Fs * 5);

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
		if (counter >= sampInt) 
		{ counter = 0; }
	}

	void setTime(float seconds)
	{
		sampInt = (seconds / 1000) * Fs;
	}

	float getSampTime()
	{
		return sampInt;
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

	float getRMS()
	{
		return sqrt(getSum() / getSampTime());
	}

	void resetSum()
	{
		sum = 0;
	}

private:
	int counter;
	bool first;
	float sum, timeInt, sampInt, Fs;

	int dataSize;
	Array<float> Data;
};