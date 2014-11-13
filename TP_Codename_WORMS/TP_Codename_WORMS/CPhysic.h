#include "C2DVector.h"
//#include <time.h>

class CPhysics{
private:
	C2DVector * m_Wind;
	double m_Gravity;
	double m_MaxSpeed;
	double m_MaxWindSpeed;
	//srand(time(NULL));

public:
	// Constructeur:
	//	Parametres: _Gravity - affecte la valeur de la gravit� (1 fois par jeu).
	//				_MaxSpeed - affecte la valeur maximale de l'acc�l�ration gravitationnelle.
	//				_MaxWindSpeed - affecte la valeur maximale de la force du vent sur un axe (donc maximum: MaxWindSpeed sur X + MaxWindSpeed sur Y).
	CPhysics(){
		m_Wind->setX(0);
		m_Wind->setY(0);
		m_Gravity = 1;
		m_MaxSpeed = 1;
		m_MaxWindSpeed = 50;
	}
	
	//M�thode: RedefineWind permet de changer aleatoirement la direction du vent.
	void RedefineWind(){
		m_Wind->setX(rand() % (m_MaxWindSpeed / 2) - (MaxWindSpeed / 4));
		m_Wind->setY(rand() % (m_MaxWindSpeed / 2) - (MaxWindSpeed / 4));
	}

	//M�thode: VerifyCollision permet de v�rifier une collision entre deux entit�s
	//		Param�tres: _Collider - Entit� qui cr�e la collision, donc est en mouvement.
	//					_Collidee - Entit� qui re�oit la collision, donc est immobile.
	bool VerifyCollision(CEntity* _Collider, CEntity* _Collidee){

	}





};