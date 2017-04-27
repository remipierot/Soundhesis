#ifndef __SINUS_SOUND__
#define __SINUS_SOUND__

/**
* Synth� sinusoidal.
*/
#include "continuous_sound.h"
#include <stdio.h>

class SinusSound : public ContinuousSound
{
	public:
		SinusSound() : ContinuousSound()
		{
			_Time = 0;
			_Phase = 0;
			_FreqSin = 440;
		}

		void setFreq(float freq)
		{
			_TmpFreq = freq;
		}

	private:
		float _FreqSin;
		float _TmpFreq;
		float _Time;
		float _Phase;
		float _PreviousSin;

		float _Sin(float frequency, float time, float phase)
		{
			return sin((2 * M_PI * frequency * time) + phase);
		}

	protected :
		virtual void init(){ }

		/**
		  * Remplissage du buffer de synth�se, jusqu'au pointeur de lecture
		  */
		virtual float getNextSample()
		{
			// Le temps entre 2 samples �quivaut � la p�riode d'�chantillonnage
			_Time += 1.0f / _Frequency;

			// Calcul de la prochaine it�ration du sinus
			float nextSin = _Sin(_FreqSin, _Time, _Phase);

			// On s'assure que le sinus change de signe et redevient positif, 
			// ce qui correspond � la fin de sa p�riode, 
			// pour pouvoir modifier sa fr�quence sans impact sur la phase
			if (_PreviousSin <= 0 && nextSin > 0)
			{
				// Si la fr�quence actuelle est diff�rente de la fr�quence vis�e
				if (_FreqSin != _TmpFreq) 
				{
					// Formule qui donne un r�sultat compl�tement cass� mais super rigolo hihi
					// _Phase = _Phase + 2 * M_PI * _Time * (_FreqSin - _TmpFreq);

					// Bonne formule
					_Phase = asin(nextSin);	// Calcul de la nouvelle phase
					_FreqSin += _FreqSin > _TmpFreq ? -1 : +1;	// Lerp de la fr�quence courante vers celle vis�e
					_Time = 0;	// R�initialisation du temps
				}
			}

			// Calcul du prochain sinus gr�ce aux nouvelles donn�es
			_PreviousSin = _Sin(_FreqSin, _Time, _Phase);

			return _PreviousSin * 0.5f;
		}
};


#endif
