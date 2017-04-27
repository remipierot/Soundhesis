#ifndef __FILTER_REVERB__
#define __FILTER_REVERB__

#define BUFFER_SIZE 8192

/**
*Filtre abstrait
*/
#include "filter.h"

class FilterReverb : public FilterAudio
{
public:

	void setReverb(float reverb)
	{
		
	}

	FilterReverb() : FilterAudio()
	{
		for (int i = 0; i < BUFFER_SIZE; i++)
		{
			_PreviousEchs[i] = 0;
		}
	}

	void init()
	{
		
	}

	virtual float doFilter(float ech)
	{
		int delay = 100;
		float decay = 0.5f;

		for (int i = 0; i < BUFFER_SIZE-1; i++)
		{
			_PreviousEchs[i] = _PreviousEchs[i+1];
		}
		_PreviousEchs[BUFFER_SIZE - 1] = (ech + _PreviousEchs[BUFFER_SIZE - 1 - delay] * decay) * 0.5f;

		return _PreviousEchs[BUFFER_SIZE - 1];
	}	

private :
	float _PreviousEchs[BUFFER_SIZE];
};


#endif
