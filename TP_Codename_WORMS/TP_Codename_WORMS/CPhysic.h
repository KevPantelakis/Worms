#define TRANSPARENCY 0 //16777215 //268435455
#define GROUND 0x00000001
#define CEILING 0x00000010
#define LEFT 0x00000100
#define RIGHT 0x00001000
#define GROUNDLEFT (GROUND|LEFT)
#define GROUNDRIGHT (GROUND|RIGHT)
#define CEILINGLEFT (CEILING|LEFT)
#define CEILINGRIGHT (CEILING|RIGHT)
#define NOCONTACT 0x00000000
#define UNDERGROUND (GROUND|CEILING|LEFT|RIGHT)
#define GROUNDCEILING (GROUND|CEILING)
#define MOVING 420
#define BLOCKED 666
#define FROMBOTTOM 12345
#define FROMTOP 67890


class CPhysics{
private:
	static CPosition * m_Wind;
	static double m_Gravity;
	static int m_MaxSpeed;
	static int m_MaxWindSpeed;
	static SDL_Surface * m_Map;
	static unsigned int m_uiPixel[WIDTH * HEIGHT];

public:


	static void Init(SDL_Surface* _map, double _gravity, int _maxWind){
		m_Wind = new CPosition(0., 0.);
		m_Map = _map;
		m_Gravity = _gravity;
		m_MaxWindSpeed = _maxWind;
		RedefineWind();
	}

	static void Annihilate(){
		m_Map = nullptr;
		m_Gravity = 0;
		m_MaxWindSpeed = 0;
		delete m_Wind;
		m_Wind = nullptr;
	}

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
		m_Wind->setX(rand() % (m_MaxWindSpeed)-m_MaxWindSpeed / 2);
		m_Wind->setY(rand() % (m_MaxWindSpeed)-m_MaxWindSpeed / 2);
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

	//� V�RIFIER + optimisations possibles
	static int VerifyGroundCollision(SDL_Rect _Rect){
		bool boGround = false;
		bool boCeiling = false;
		bool boLeft = false;
		bool boRight = false;
		for (int i = 0; i < _Rect.w; i++){
			if (((unsigned int*)m_Map->pixels)[(m_Map->w * (_Rect.y + _Rect.h)) + _Rect.x + i] > TRANSPARENCY && !boGround){
				boGround = true;
			}
			if (_Rect.y > 0 && ((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect.y - 1) + _Rect.x + i] > TRANSPARENCY && !boCeiling){
				boCeiling = true;
			}
		}
		for (int i = 0; i < _Rect.h; i++){
			if (((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect.y + i) + _Rect.x + _Rect.w] > TRANSPARENCY && !boRight){
				boRight = true;
			}
			if (((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect.y + i) + _Rect.x - 1] > TRANSPARENCY && !boLeft){
				boLeft = true;
			}
		}

		if (boGround){
			if (boCeiling)
				return GROUNDCEILING;
			if (boLeft)
				return GROUNDLEFT;
			if (boRight)
				return GROUNDRIGHT;
			return GROUND;
		}
		else {
			if (boCeiling){
				if (boLeft)
					return CEILINGLEFT;
				if (boRight)
					return CEILINGRIGHT;
				return CEILING;
			}
			else {
				if (boRight)
					return RIGHT;
				if (boLeft)
					return LEFT;
				return NOCONTACT;
			}
		}
	}



	static CPosition* VerifyNextPosition(CTrajectory* _Trajectoire, SDL_Rect _EntityRect){
		C2DVector* pVector = new C2DVector((int)_Trajectoire->GetActualPosition()->getX(), (int)_Trajectoire->GetActualPosition()->getY(), (int)_Trajectoire->getNextPos()->getX(), (int)_Trajectoire->getNextPos()->getY());
		if (pVector->getNorme()){
			CPosition* CollisionPosition = new CPosition(0.f, 0.f);
			pVector->Normalize();
			bool boCollide = false;
			int iX, iY;
			iX = pVector->getComposanteX() + pVector->getXDebut();
			iY = pVector->getComposanteY() + pVector->getYDebut();
			while ((pVector->getXfin() >= pVector->getXDebut()) &&
				(pVector->getYfin() >= pVector->getYDebut()))
			{
				//x>0 y>0
				if (((pVector->getComposanteX()) > 0) && (pVector->getComposanteY() > 0)){
					for (int i = 0; i < _EntityRect.w; i++)
					{
						if (((unsigned int*)m_Map->pixels)[(m_Map->w * (iY + _EntityRect.h)) + (iX + i)] > TRANSPARENCY){
							CollisionPosition->setXY(iX, iY);
							return CollisionPosition;
						}
					}
					for (int i = 0; i < _EntityRect.h; i++)
					{
						if (((unsigned int*)m_Map->pixels)[(m_Map->w * (iY + i)) + (iX + _EntityRect.w)] > TRANSPARENCY){
							CollisionPosition->setXY(iX, iY);
							return CollisionPosition;
						}
					}
				}

				//x>0 y<0
				if (((pVector->getComposanteX()) > 0) && (pVector->getComposanteY() < 0)){
					for (int i = 0; i < _EntityRect.w; i++)
					{
						if (((unsigned int*)m_Map->pixels)[(m_Map->w * (iY)) + (iX + i)] > TRANSPARENCY){
							CollisionPosition->setXY(iX, iY);
							return CollisionPosition;
						}
					}


					for (int i = 0; i < _EntityRect.h; i++)
					{
						if (((unsigned int*)m_Map->pixels)[(m_Map->w * (iY + i)) + (iX + _EntityRect.w)] > TRANSPARENCY){
							CollisionPosition->setXY(iX, iY);
							return CollisionPosition;
						}
					}
				}

				//x<0 y>0
				if (((pVector->getComposanteX()) < 0) && (pVector->getComposanteY() > 0)){
					for (int i = 0; i < _EntityRect.w; i++)
					{
						if (((unsigned int*)m_Map->pixels)[(m_Map->w * (iY + _EntityRect.h)) + (iX + i)] > TRANSPARENCY){
							CollisionPosition->setXY(iX, iY);
							return CollisionPosition;
						}
					}
					for (int i = 0; i < _EntityRect.h; i++)
					{
						if (((unsigned int*)m_Map->pixels)[(m_Map->w * (iY + i)) + (iX)] > TRANSPARENCY){
							CollisionPosition->setXY(iX, iY);
							return CollisionPosition;
						}
					}
				}

				//x<0 y<0
				if (((pVector->getComposanteX()) < 0) && (pVector->getComposanteY() < 0)){
					for (int i = 0; i < _EntityRect.w; i++)
					{
						if (((unsigned int*)m_Map->pixels)[(m_Map->w * (iY)) + (iX + i)] > TRANSPARENCY){
							CollisionPosition->setXY(iX, iY);
							return CollisionPosition;
						}
					}
					for (int i = 0; i < _EntityRect.h; i++)
					{
						if (((unsigned int*)m_Map->pixels)[(m_Map->w * (iY + 1)) + (iX)] > TRANSPARENCY){
							CollisionPosition->setXY(iX, iY);
							return CollisionPosition;
						}
					}
				}

				//x=0 y>0
				if (((pVector->getComposanteX()) == 0) && (pVector->getComposanteY() > 0)){
					for (int i = 0; i < _EntityRect.w; i++)
					{
						if (((unsigned int*)m_Map->pixels)[(m_Map->w * (iY + _EntityRect.h)) + (iX + i)] > TRANSPARENCY){
							CollisionPosition->setXY(iX, iY);
							return CollisionPosition;
						}
					}
				}

				//x=0 y<0
				if (((pVector->getComposanteX()) == 0) && (pVector->getComposanteY() < 0)){
					for (int i = 0; i < _EntityRect.w; i++)
					{
						if (((unsigned int*)m_Map->pixels)[(m_Map->w * (iY)) + (iX + i)] > TRANSPARENCY){
							CollisionPosition->setXY(iX, iY);
							return CollisionPosition;
						}
					}
				}

				//x>0 y=0
				if (((pVector->getComposanteX()) > 0) && (pVector->getComposanteY() == 0)){
					for (int i = 0; i < _EntityRect.h; i++)
					{
						if (((unsigned int*)m_Map->pixels)[(m_Map->w * (iY + i)) + (iX + _EntityRect.w)] > TRANSPARENCY){
							CollisionPosition->setXY(iX, iY);
							return CollisionPosition;
						}
					}
				}

				//x<0 y=0
				if (((pVector->getComposanteX()) < 0) && (pVector->getComposanteY() == 0)){
					for (int i = 0; i < _EntityRect.h; i++)
					{
						if (((unsigned int*)m_Map->pixels)[(m_Map->w * (iY + 1)) + (iX)] > TRANSPARENCY){
							CollisionPosition->setXY(iX, iY);
							return CollisionPosition;
						}
					}
				}
				iX = pVector->getComposanteX() + pVector->getXDebut();
				iY = pVector->getComposanteY() + pVector->getYDebut();
				pVector->setXYDebut(iX, iY);

			}
			CollisionPosition->setXY(pVector->getXfin(), pVector->getYfin());
			delete pVector;
			return CollisionPosition;
		}
		return nullptr;
	}




	static void VerifyNextPosition(CPosition* _ActualPos, CPosition* _NextPos, SDL_Rect _EntityRect){
		bool boYContact(false), boXContact(false);
		int YContact(0), XContact(0);
		int DeltaY = _NextPos->getY() - _ActualPos->getY();
		int DeltaX = _NextPos->getX() - _ActualPos->getX();
		if (_NextPos->getY() > _ActualPos->getY()){
			for (int i = 0; i < DeltaY; i++){
				if (((unsigned int*)m_Map->pixels)[m_Map->w * ((int)_ActualPos->getY() + i) + (int)_ActualPos->getX()] > TRANSPARENCY && !boYContact){
					boYContact = true;
					YContact = i;
				}
			}
		}
		else{
			for (int i = DeltaY; i < 0; i++){
				if (((unsigned int*)m_Map->pixels)[m_Map->w * ((int)_ActualPos->getY() + i) + (int)_ActualPos->getX()] > TRANSPARENCY && !boYContact){
					boYContact = true;
					YContact = i;
				}
			}
		}
		if (_NextPos->getX() > _ActualPos->getX()){
			for (int i = 0; i < DeltaX; i++){
				if (((unsigned int*)m_Map->pixels)[(m_Map->w * (int)_ActualPos->getY()) + (int)_ActualPos->getX() + i] > TRANSPARENCY && !boXContact){
					boXContact = true;
					XContact = i;
				}
			}
		}
		else{
			for (int i = DeltaX; i < 0; i++) {
				if (((unsigned int*)m_Map->pixels)[(m_Map->w * (int)_ActualPos->getY()) + (int)_ActualPos->getX() + i] > TRANSPARENCY && !boXContact){
					boXContact = true;
					XContact = i;
				}
			}
		}
		if (XContact)
			_NextPos->setX(_ActualPos->getX() + XContact - _EntityRect.w);
		if (YContact)
			_NextPos->setY(_ActualPos->getY() + YContact - _EntityRect.h);
	}

	/*
	M�thode : EvaluateSlope
	Brief : Fonction qui retourne la pente (en degr�s) � partir d'une section de la map
	Params :
	_Pos : Position dans la surface o� la pente est �valu�e
	_Direction : Direction de laquelle vient l'entit� impliqu�e
	Discussion : � FAIRE : �valuer une collision "de cot�"
	*/
	static double EvaluateSlope(SDL_Rect* _Rect){
		double Slope = 0;
		bool first = false;
		int PreviousY;
		double PointsSignificatifs = 0;
		for (int x = _Rect->x; x < _Rect->x + _Rect->w; x++){
			for (int y = _Rect->y; y < _Rect->y + _Rect->h; y++){
				if (((unsigned int*)m_Map->pixels)[m_Map->w * (y)+x] >TRANSPARENCY){
					if (((unsigned int*)m_Map->pixels)[m_Map->w * (y + 1) + x] == 0
						|| ((unsigned int*)m_Map->pixels)[m_Map->w * (y - 1) + x] == 0){
						double TmpY = y;
						if (first)
							Slope = Slope + (TmpY - PreviousY);
						else
							first = true;
						PreviousY = TmpY;
						PointsSignificatifs++;
						y = _Rect->y + _Rect->h;
					}
				}
			}
		}
		return RadToDeg(atan(Slope / (PointsSignificatifs - 1)));

	}


	//M�thode: Fall:	Calcule la trajectoire d'un glissement d'une entit�.
	//			Param�tres:	_Vector - Vecteur(vitesse et direction) initiale du glissement.
	//						_X et _Y - Positions en X et en Y intiales de l'entit�.
	static CTrajectory * Slide(CPosition * _Vector, int _X, int _Y){
		return nullptr;
	}

	/*M�thode : Propulsion
	Brief : Fonction qui retourne la trajectoire d'une entit� propuls�e
	Params :
	_PosInit : Position initiale de la propulsion
	_Vit : Vitesse initiale de la propulsion
	*/
	static CTrajectory* Propulsion(CPosition* _PosInit, C2DVector* _Vit, C2DVector* _Acc){
		return new CTrajectory(_PosInit, _Vit, _Acc);
	}

	/*
	M�thode : Move
	Brief : Fonction qui ajuste la position suite � un mouvement sans acc�l�ration
	Params:
	_Rect : Rectangle se d�pla�ant
	_Direction : Bool de la direction emprunt�e
	true : gauche
	false : droite
	Return : true : d�placement effectu�
	false : d�placement non effectu�
	Discussion : Ne d�place actuellement que d'un pixel sur l'axe X, � changer si voulu
	La hauteur (en pixels) d'une pente "escaladable" en y sera � d�terminer (actuellement 3 pixels)
	*/
	static bool Move(SDL_Rect _Rect, bool _Direction){
		if (_Direction){
			for (int i = 0; i < _Rect.h + 3; i++){
				if (!(((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect.x - 1 + i) + _Rect.x - 1] == 0)){
					if (i < _Rect.h - 3)
						return BLOCKED;
					else {
						_Rect.y = _Rect.y + (_Rect.h - i);
					}
				}
				if (i == _Rect.h + 2){
					_Rect.y = _Rect.y + (_Rect.h - i);
				}
			}
			_Rect.x = _Rect.x - 1;
			return MOVING;
		}
		else{
			for (int i = 0; i < _Rect.h + 3; i++){
				if (!(((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect.x - 1 + i) + _Rect.x + _Rect.w] == 0)){
					if (i < _Rect.h - 3)
						return BLOCKED;
					else {
						_Rect.y = _Rect.y + (_Rect.h - i);
					}
				}
				if (i == _Rect.h + 2){
					_Rect.y = _Rect.y + (_Rect.h - i);
				}
			}
			_Rect.x = _Rect.x + 1;
			return MOVING;

		}
	}

	//Accesseurs...
	static CPosition* GetWind(){
		return m_Wind;
	}
	static double GetGravity(){
		return m_Gravity;
	}
	static void setGravity(double _d){
		m_Gravity = _d;
	}
};
CPosition * CPhysics::m_Wind = new CPosition(0., 0.);
double CPhysics::m_Gravity = 1;
int CPhysics::m_MaxSpeed = 1;
int CPhysics::m_MaxWindSpeed = 50;
SDL_Surface * CPhysics::m_Map = nullptr;
unsigned int CPhysics::m_uiPixel[WIDTH * HEIGHT];