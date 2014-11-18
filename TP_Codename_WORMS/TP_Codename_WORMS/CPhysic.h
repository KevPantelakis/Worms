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
		for (int x1 = 0; x1 < _Collider->getRect().w; x1++){
			for (int x2 = 0; x2 < _Collidee->getRect().w; x2++){
				if (x1 == x2) {
					for (int y1 = 0; y1 < _Collider->getRect().h; y1++){
						for (int y2 = 0; y2 < _Collidee->getRect().h; y2++){
							if (y1 == y2) return true;
						}
					}
				}
			}
		}
		return false;
	}

	//M�thode: Fall:	Calcule la trajectoire d'une chute d'une entit�.
	//			Param�tres:	_Vit - Vecteur(vitesse et direction) initiale de la chute.
	//						_X et _Y - Positions en X et en Y intiales de l'entit�.
	CTrajectory * Fall(C2DVector * _Vit, int _X, int _Y){
		return CTrajectory(C2DVector(_X, _Y), _Vit);
	}

	//M�thode: Fall:	Calcule la trajectoire d'un glissement d'une entit�.
	//			Param�tres:	_Vector - Vecteur(vitesse et direction) initiale du glissement.
	//						_X et _Y - Positions en X et en Y intiales de l'entit�.
	CTrajectory * Slide(C2DVector * _Vector, int _X, int _Y){

	}

	/*M�thode : Propulsion
	Brief : Fonction qui retourne la trajectoire d'une entit� propuls�e
	Params :
	_PosInit : Position initiale de la propulsion
	_Vit : Vitesse initiale de la propulsion
	*/
	CTrajectory * Propulsion(C2DVector* _PosInit, C2DVector* _Vit){
		return CTrajectory(_PosInit, _Vit);
	}
	/*
	M�thode: Explosion
	Brief: Fonction qui determine les effets cr�es par une explosion.
	Params:
	_X et _Y : Determinent la position du centre de l'explosion
	_Rad : Rayon de l'explosion.
	*/
	void Explosion(int _X, int _Y, int _Rad){

	}

};