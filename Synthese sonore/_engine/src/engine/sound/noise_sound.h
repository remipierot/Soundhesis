#ifndef __NOISE_SOUND__
#define __NOISE_SOUND__

#define NUMBER_OF_NOISES 8

/**
* Bruit de variabilité ajustable
*/
#include "continuous_sound.h"

class NoiseSound : public ContinuousSound
{
public:
	
	NoiseSound() : ContinuousSound()
	{		
		setFreq(50);
	}

	void setFreq(float freq)
	{
		_FreqNoise = freq;

		for (int i = 0; i < NUMBER_OF_NOISES; i++) 
			_Counts[i] = 0;	
	}

private:
	float _FreqNoise;
	float _PreviousSamples[NUMBER_OF_NOISES];
	float _Counts[NUMBER_OF_NOISES];

protected :

	/**
	  * Remplissage du buffer de synthèse, jusqu'au pointeur de lecture
	  */
	virtual float getNextSample()
	{	
		float nextSample = 0;

		for (int i = 0; i < NUMBER_OF_NOISES; i++)
		{
			_Counts[i] += 1.0f / _Frequency;

			if (_Counts[i] > 1.0f / (_FreqNoise * (i+1)))
			{
				_Counts[i] = 0;
				_PreviousSamples[i] = randf();
			}

			nextSample += _PreviousSamples[i];
		}

		return ((nextSample / NUMBER_OF_NOISES) * 2.0f - 1.0f) * 0.5f;
	}	

};

#endif
