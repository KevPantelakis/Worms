#define GROUND 1111
#define CEILING 2222
#define LEFT 3333
#define RIGHT 4444
#define GROUNDLEFT 5555
#define GROUNDRIGHT 6666
#define CEILINGLEFT 7777
#define CEILINGRIGHT 8888
#define NOCONTACT 9999
#define GROUNDCEILING 1337

class CTrajectory;
static class CPhysics{
private:
	static C2DVector * m_Wind;
	static double m_Gravity;
	static int m_MaxSpeed;
	static int m_MaxWindSpeed;
	static SDL_Surface * m_Map;

public:
	// Constructeur:
	//	Parametres: _Gravity - affecte la valeur de la gravit� (1 fois par jeu).
	//				_MaxSpeed - affecte la valeur maximale de l'acc�l�ration gravitationnelle.
	//				_MaxWindSpeed - affecte la valeur maximale de la force du vent sur un axe (donc maximum: MaxWindSpeed sur X + MaxWindSpeed sur Y).
	//CPhysics(){
		//m_Wind->setX(0);
		//m_Wind->setY(0);
		//m_Gravity = 1;
		//m_MaxSpeed = 1;
		//m_MaxWindSpeed = 50;
	//}

	//M�thode: RedefineWind permet de changer aleatoirement la direction du vent.
	static void RedefineWind(){
		m_Wind->setX(rand() % (m_MaxWindSpeed) - m_MaxWindSpeed/2);
		m_Wind->setY(rand() % (m_MaxWindSpeed) - m_MaxWindSpeed/2);
	}

	//M�thode: VerifyCollision permet de v�rifier une collision entre deux rectangles
	//		Param�tres: _Collider - Rectangle qui cr�e la collision, donc est en mouvement.
	//					_Collidee - Rectangle qui re�oit la collision, donc est immobile.
	static bool VerifyCollision(SDL_Rect _Collider, SDL_Rect _Collidee){
		if ((_Collider.x + _Collider.w > _Collidee.x) || (_Collider.x < _Collidee.x + _Collidee.w)){
			if ((_Collider.y + _Collider.h > _Collidee.y) || (_Collider.y < _Collidee.y + _Collidee.h)){
				return true;
			}
		}
		return false;
	}

	/*
	M�thode : VerifyGroundCollision
	Brief : Fonction qui retourne par un entier l'�tat d'un rect par rapport au terrain
	Params : 
		_Rect : Rectangle dont on v�rifie la collision
	Return : 
		NOCONTACT : Le rectangle ne touche � rien
		GROUND : Le rectangle touche au sol
		LEFT : Le rectangle touche le terrain � gauche
		RIGHT : Le rectangle touche le terrain � droite
		CEILING : Le rectangle touche le plafond
		GROUNDLEFT : Le rectangle touche le sol et la gauche
		GROUNDRIGHT : Le rectangle touche le sol et la droite
		CEILINGLEFT : Le rectangle touche le plafond et la gauche
		CEILINGRIGHT : Le rectangle touche le plafond et la droite
		GROUNDCEILING : Le rectangle touche au plafond et au sol
	*/
	//Valeur de la transparence : 16777215

	//� V�RIFIER
	static int VerifyGroundCollision(SDL_Rect _Rect){
		bool boGround = false;
		bool boCeiling = false;
		bool boLeft = false;
		bool boRight = false;
		for (int i = 0; i < _Rect.w; i++){
			if (((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect.y + _Rect.h) + _Rect.x + i] == 0 && !boGround){
				boGround = true;
			}
			if (((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect.y - 1) + _Rect.x + i] == 0 && !boCeiling){
				boCeiling = true;
			}
		}
		for (int i = 0; i < _Rect.h; i ++){
			if (((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect.y) + _Rect.x + _Rect.w + 1 + i] == 0 && !boRight){
				boRight = true;
			}
			if (((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect.y - 1 + i) + _Rect.x -1] == 0 && !boLeft){
				boLeft = true;
			}
		}
		return 0;
	}

	//M�thode: Fall:	Calcule la trajectoire d'un glissement d'une entit�.
	//			Param�tres:	_Vector - Vecteur(vitesse et direction) initiale du glissement.
	//						_X et _Y - Positions en X et en Y intiales de l'entit�.
	static CTrajectory * Slide(C2DVector * _Vector, int _X, int _Y){

	}

	/*M�thode : Propulsion
	Brief : Fonction qui retourne la trajectoire d'une entit� propuls�e
	Params :
	_PosInit : Position initiale de la propulsion
	_Vit : Vitesse initiale de la propulsion
	*/
	static CTrajectory* Propulsion(C2DVector* _PosInit, C2DVector* _Vit){
		//return new CTrajectory(_PosInit, _Vit);
	}

	//Accesseurs...
	static C2DVector* GetWind(){
		return m_Wind;
	}
	static double GetGravity(){
		return m_Gravity;
	}
};
C2DVector * CPhysics::m_Wind = new C2DVector(0.,0.);
double CPhysics::m_Gravity = 1;
int CPhysics::m_MaxSpeed = 1;
int CPhysics::m_MaxWindSpeed =50;
SDL_Surface * CPhysics::m_Map = nullptr;