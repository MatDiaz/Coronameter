/*
  ==============================================================================

    ArrayManager.h
    Created: 21 May 2020 6:49:10pm
    Author:  WATEO

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class ArrayManager
{
public:
	ArrayManager(int size) 
	{
		arraySize = size;
		FiFo.reset(new AbstractFifo{ size });
	}
	~ArrayManager() {}
	void addToFifo()
	{

	}
	void readFromFifo()
	{

	}

private:
	int arraySize;
	std::unique_ptr<AbstractFifo> FiFo;
};
