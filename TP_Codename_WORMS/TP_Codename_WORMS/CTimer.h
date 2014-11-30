//
//  CTimer.h
//  CFenetre
//
//  Created by Richer Archambault on 2014-10-07.
//  Copyright (c) 2014 Richer Archambault. All rights reserved.
//

#ifndef CFenetre_CTimer_h
#define CFenetre_CTimer_h


/*!
 @class CTimer
 @discussion Classe pour impl�ment� une minuterie
 */
class CTimer {
private:
	unsigned int m_uiTicks,			// Nombre de ticks du d�part du timer (miliSecondes).
				 m_uiTimeToElapse;	// Combien de ticks avant le d�clenchement(miliSecondes).
	bool m_boPause;
	bool m_boIsStart;

public:

	/*!
	 @method Constructeur
	 */
	CTimer(){
		m_uiTicks = 0;
		m_uiTimeToElapse = 0;
		m_boPause = false;
		m_boIsStart = false;
	}
	
	/*!
	 @method Start
	 @brief M�thode qui d�marre la minuterie
	 */
	void Start(){
		m_uiTicks = SDL_GetTicks();
		m_boIsStart = true;
	}
	
	/*!
	 @method SetTimer
	 @brief M�thode qui ajuste le temps de la minuterie
	 @param _timeToElapse : Entier du temps � �couler 
	 */
	void SetTimer(unsigned int _timeToElapse){
		m_uiTimeToElapse = _timeToElapse;
	}
	
	/*!
	 @method IsElapsed
	 @brief Fonction qui retourne par un bool si le temps de la minuterie est �coul� ou non
	 @return true : la minuterie est �coul�e
	 @return false : la minuterie n'est pas �coul�e
	 */
	bool IsElapsed(){
		return ((SDL_GetTicks() - m_uiTicks) >= m_uiTimeToElapse);
	}

	/*!
	@method HasStarted
	@brief Fonction qui retourne par un bool si la minuterie est commenc�e ou non
	@return true : la minuterie est start
	@return false : la minuterie n'est pas start
	*/
	bool HasStarted(){
		return m_boIsStart;
	}
	/*!
	 @method Pause
	 @brief M�thode qui red�finie le temps de la minuterie pour la mettre en pause
	 */
	void Pause(){
		m_uiTimeToElapse = m_uiTimeToElapse - (SDL_GetTicks() - m_uiTicks);
		m_boPause = true;
	}

	/*!
	 @method UnPause
	 @brief M�thode qui appelle Start pour red�marrer la minuterie
	 @discussion Assez superflu, mais pratique pour ne pas oublier de red�marrer la minuterie apr�s une pause
	 */
	void UnPause(){
		if (m_boPause){
			Start();
			m_boPause = false;
		}
	}
	
	unsigned int getElapsedTime(){
		return SDL_GetTicks() - m_uiTicks;
	}
};

#endif
