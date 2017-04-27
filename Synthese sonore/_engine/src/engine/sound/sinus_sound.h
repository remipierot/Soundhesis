#ifndef __SINUS_SOUND__
#define __SINUS_SOUND__

/**
* Synthé sinusoidal.
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
		  * Remplissage du buffer de synthèse, jusqu'au pointeur de lecture
		  */
		virtual float getNextSample()
		{
			// Le temps entre 2 samples équivaut à la période d'échantillonnage
			_Time += 1.0f / _Frequency;

			// Calcul de la prochaine itération du sinus
			float nextSin = _Sin(_FreqSin, _Time, _Phase);

			// On s'assure que le sinus change de signe et redevient positif, 
			// ce qui correspond à la fin de sa période, 
			// pour pouvoir modifier sa fréquence sans impact sur la phase
			if (_PreviousSin <= 0 && nextSin > 0)
			{
				// Si la fréquence actuelle est différente de la fréquence visée
				if (_FreqSin != _TmpFreq) 
				{
					// Formule qui donne un résultat complètement cassé mais super rigolo hihi
					// _Phase = _Phase + 2 * M_PI * _Time * (_FreqSin - _TmpFreq);

					// Bonne formule
					_Phase = asin(nextSin);	// Calcul de la nouvelle phase
					_FreqSin += _FreqSin > _TmpFreq ? -1 : +1;	// Lerp de la fréquence courante vers celle visée
					_Time = 0;	// Réinitialisation du temps
				}
			}

			// Calcul du prochain sinus grâce aux nouvelles données
			_PreviousSin = _Sin(_FreqSin, _Time, _Phase);

			return _PreviousSin * 0.5f;
		}
};


#endif
