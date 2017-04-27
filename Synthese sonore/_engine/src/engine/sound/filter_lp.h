#ifndef __FILTER_LP__
#define __FILTER_LP__

/**
*Filtre abstrait
*/
#include "filter.h"


class FilterLP : public FilterAudio
{
public:

	void setAlpha(float alpha)
	{
		alpha = (alpha < 0) ? 0 : (alpha > 1) ? 1 : alpha;
		_Alpha = alpha;
	}

	FilterLP() : FilterAudio()
	{
		setAlpha(1);
		_LastEch = 0;
	}

	virtual float doFilter(float ech)
	{
		_LastEch += _Alpha * (ech - _LastEch);
		return _LastEch;
	}	

private :
	float _Alpha;
	float _LastEch;

};


#endif
