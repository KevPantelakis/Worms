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



class CPhysics{
private:
	static C2DVector * m_Wind;			// Le vent
	static double m_Gravity;			// La gravit�
	static int m_MaxSpeed;				// La vitesse maximum
	static int m_MaxWindSpeed;			// Le vent maximum
	static SDL_Surface * m_Map;			// Le Cham de battaile ou la physique aura son effet.
	
	
	
public:
	
	/*!
	 @method Init.
	 @brief Initialise les donn�es membres.
	 @param _map: Champ de battaile
	 @param _gravity: Gravit� qui influra sur les entit�es
	 @param _maxWind: Vent maximum.
	 @return Adresse m�moire de l'objet.
	 @discussion Comme tous les donn�es membres sont statiques, Le init agit comme un constructeur.
	 */

	static void Init(SDL_Surface* _map, double _gravity, int _maxWind){
		m_Wind = new C2DVector(0, 0, 0, 0);
		m_Map = _map;
		m_Gravity = _gravity;
		m_MaxWindSpeed = _maxWind;
		RedefineWind();
	}
	
	/*!
	 @method Annihilate.
	 @brief Agit comme un destructeur, met tout a nullptr
	 @return Aucun
	 @discussion Aucune
	 */
	static void Annihilate(){
		m_Map = nullptr;
		m_Gravity = 0;
		m_MaxWindSpeed = 0;
		delete m_Wind;
		m_Wind = nullptr;
	}
	
	/*!
	 @method RedefineWind
	 @brief  Permet de changer aleatoirement la direction du vent.
	 @param Aucun.
	 @return Aucun
	 @discussion Aucune.
	 */
	static void RedefineWind(){
		double temp = (rand() % (int)m_MaxWindSpeed);
		double Norme = temp / 100;
		m_Wind->setNorme(Norme);
		double angle = (rand() % 360);
		m_Wind->setOrientation(DegToRad(angle));
	}
	
	/*!
	 @method Verify collision
	 @brief V�rifie si deux rect se touche
	 @param _Collider: Le rect en mouvement
	 @param _Collidee: Le rect immobile .
	 @return true si il y a un collision?
	 @return false si il n'en a pas
	 @discussion Aucune.
	 */
	static bool VerifyCollision(SDL_Rect _Collider, SDL_Rect _Collidee){
		if ((_Collider.x + _Collider.w > _Collidee.x) || (_Collider.x < _Collidee.x + _Collidee.w)){
			if ((_Collider.y + _Collider.h > _Collidee.y) || (_Collider.y < _Collidee.y + _Collidee.h)){
				return true;
			}
		}
		return false;
	}
	
	
	
	static void HandleGroundCollision(SDL_Rect* _Rect, int _Direction){
		switch (_Direction) {
			case GROUNDLEFT:
			case CEILINGRIGHT:
				for (int i = 0; i < _Rect->w; i++){
					while (((unsigned int*)m_Map->pixels)[(m_Map->w * (_Rect->y + _Rect->h)) + _Rect->x + i] != TRANSPARENCY){
						_Rect->y--;
					}
					while (((unsigned int*)m_Map->pixels)[(m_Map->w * (_Rect->y + _Rect->h)) + _Rect->x + i] == TRANSPARENCY){
						_Rect->y++;
					}
				}
				break;
			case CEILINGLEFT:
			case GROUNDRIGHT:
				for (int i = _Rect->w; i > 0; i--){
					while (((unsigned int*)m_Map->pixels)[(m_Map->w * (_Rect->y + _Rect->h)) + _Rect->x + i] != TRANSPARENCY){
						_Rect->y--;
					}
					while (((unsigned int*)m_Map->pixels)[(m_Map->w * (_Rect->y + _Rect->h)) + _Rect->x + i] == TRANSPARENCY){
						_Rect->y++;
					}
				}
				break;
		}
	}
	
	
	
	/*!
	 @method VerifyGroudColision
	 @brief V�rifie si deux rect se touche
	 @param _Collider: Le rect en mouvement
	 @param _Collidee: Le rect immobile .
	 @return NOCONTACT : Le rectangle ne touche � rien
	 @return GROUND : Le rectangle touche au sol
	 @return LEFT : Le rectangle touche le terrain � gauche
	 @return RIGHT : Le rectangle touche le terrain � droite
	 @return CEILING : Le rectangle touche le plafond
	 @return GROUNDLEFT : Le rectangle touche le sol et la gauche
	 @return GROUNDRIGHT : Le rectangle touche le sol et la droite
	 @return CEILINGLEFT : Le rectangle touche le plafond et la gauche
	 @return CEILINGRIGHT : Le rectangle touche le plafond et la droite
	 @return GROUNDCEILING : Le rectangle touche au plafond et au sol
	 @discussion Aucune.
	 */
	static CPosition* verifyGroundCollision(SDL_Rect _Rect){
		for (int i = 0; i < _Rect.h; i++){
			for (int j = 0; j < _Rect.w; j++) {
				if (((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect.y + i) + _Rect.x + j] != TRANSPARENCY){
					return new CPosition(_Rect.x + j, _Rect.y + i);
				}
			}
		}
		return nullptr;
	}
	
	/*!
	 @method VerifyNextPosition
	 @brief V�rifie la position prochaine pour les collisions.
	 @param _Trajectoire: Trajectoire a parcourir par l'objet.
	 @param _EntityRect: Rect de l'objet qui tombe
	 @return La position de la collision si il y en a une.
	 @return La position finale si la trajectoire c'est fait sans collisions.
	 @return nullptr si le d�placement n'est pas significatif.
	 @discussion Retourne toujours une position valide sauf si le vecteur Original n'est pas assez gros.
	 */
	static CPosition* VerifyNextPosition(CTrajectory* _Trajectoire, SDL_Rect _EntityRect){
		C2DVector* pVector = new C2DVector((int)_Trajectoire->GetActualPosition()->getX(), (int)_Trajectoire->GetActualPosition()->getY(), (int)_Trajectoire->getNextPos()->getX(), (int)_Trajectoire->getNextPos()->getY());
			//BIG BANANA TRIP
		if (pVector->getNorme()){
			CPosition* CollisionPosition = new CPosition(0.0, 0.0);
			pVector->Normalize();
			double dblX, dblY;
			dblX = pVector->getComposanteX() + pVector->getXStart();
			dblY = pVector->getComposanteY() + pVector->getYStart();
			int temp = 0;
			
				//x>0 y>0
			if (((pVector->getComposanteX()) > 0) && (pVector->getComposanteY() > 0)){
				while ((pVector->getXEnd() >= pVector->getXStart()) &&
					   (pVector->getYEnd() >= pVector->getYStart()))
				{
					for (int i = 0; i < _EntityRect.w; i++){
						temp = (m_Map->w * ((int)dblY + _EntityRect.h)) + ((int)dblX + i);
						if ((temp >= 0)){
							if (((unsigned int*)m_Map->pixels)[temp] > TRANSPARENCY){
								CollisionPosition->setXY(dblX, dblY);
								delete pVector;
								if ((dblX > WIDTH) || (dblY > HEIGHT) || (dblX < (0 - _EntityRect.w)) || (dblY < (0 - _EntityRect.h)))
									CollisionPosition->setState(true);
								return CollisionPosition;
							}
						}
					}
					for (int i = 0; i < _EntityRect.h; i++){
						temp = (m_Map->w * ((int)+i)) + ((int)dblX + _EntityRect.w);
						if ( temp >= 0){
							if (((unsigned int*)m_Map->pixels)[temp] > TRANSPARENCY){
								CollisionPosition->setXY(dblX, dblY);
								delete pVector;
								if ((dblX > WIDTH) || (dblY > HEIGHT) || (dblX < (0 - _EntityRect.w)) || (dblY < (0 - _EntityRect.h)))
									CollisionPosition->setState(true);
								return CollisionPosition;
							}
						}
					}
					dblX = pVector->getComposanteX() + pVector->getXStart();
					dblY = pVector->getComposanteY() + pVector->getYStart();
					pVector->setDOUBLE_XY_START(dblX, dblY);
				}
			}
			
				//x<0 y>0
			if (((pVector->getComposanteX()) < 0) && (pVector->getComposanteY() > 0)){
				while ((pVector->getXEnd() <= pVector->getXStart()) &&
					   (pVector->getYEnd() >= pVector->getYStart()))
				{
					for (int i = 0; i < _EntityRect.w; i++){
						temp = (m_Map->w * ((int)dblY + _EntityRect.h)) + ((int)dblX + i);
						if (temp >= 0){
							if (((unsigned int*)m_Map->pixels)[temp] > TRANSPARENCY){
								CollisionPosition->setXY(dblX, dblY);
								delete pVector;
								if ((dblX > WIDTH) || (dblY > HEIGHT) || (dblX < (0 - _EntityRect.w)) || (dblY < (0 - _EntityRect.h)))
									CollisionPosition->setState(true);
								return CollisionPosition;
							}
						}
					}
					for (int i = 0; i < _EntityRect.h; i++){
						temp = (m_Map->w * ((int)dblY + i)) + ((int)dblX);
						if (temp >= 0){
							if (((unsigned int*)m_Map->pixels)[temp] > TRANSPARENCY){
								CollisionPosition->setXY(dblX, dblY);
								delete pVector;
								if ((dblX > WIDTH) || (dblY > HEIGHT) || (dblX < (0 - _EntityRect.w)) || (dblY < (0 - _EntityRect.h)))
									CollisionPosition->setState(true);
								return CollisionPosition;
							}
						}
					}
					dblX = pVector->getComposanteX() + pVector->getXStart();
					dblY = pVector->getComposanteY() + pVector->getYStart();
					pVector->setDOUBLE_XY_START(dblX, dblY);
				}
			}
			
				//x>0 y<0
			if (((pVector->getComposanteX()) > 0) && (pVector->getComposanteY() < 0)){
				while ((pVector->getXEnd() >= pVector->getXStart()) &&
					   (pVector->getYEnd() <= pVector->getYStart()))
				{
					for (int i = 0; i < _EntityRect.w; i++){
						temp = (m_Map->w * ((int)dblY)) + ((int)dblX + i);
						if (temp >= 0){
							if (((unsigned int*)m_Map->pixels)[temp] > TRANSPARENCY){
								CollisionPosition->setXY(dblX, dblY);
								delete pVector;
								if ((dblX > WIDTH) || (dblY > HEIGHT) || (dblX < (0 - _EntityRect.w)) || (dblY < (0 - _EntityRect.h)))
									CollisionPosition->setState(true);
								return CollisionPosition;
							}
						}
					}
					for (int i = 0; i < _EntityRect.h; i++){
						temp = (m_Map->w * ((int)dblY + i)) + ((int)dblX + _EntityRect.w);
						if (temp >= 0){
							if (((unsigned int*)m_Map->pixels)[temp] > TRANSPARENCY){
								CollisionPosition->setXY(dblX, dblY);
								delete pVector;
								if ((dblX > WIDTH) || (dblY > HEIGHT) || (dblX < (0 - _EntityRect.w)) || (dblY < (0 - _EntityRect.h)))
									CollisionPosition->setState(true);
								return CollisionPosition;
							}
						}
					}
					dblX = pVector->getComposanteX() + pVector->getXStart();
					dblY = pVector->getComposanteY() + pVector->getYStart();
					pVector->setDOUBLE_XY_START(dblX, dblY);
				}
			}
			
				//x<0 y<0
			if (((pVector->getComposanteX()) < 0) && (pVector->getComposanteY() < 0)){
				while ((pVector->getXEnd() <= pVector->getXStart()) &&
					   (pVector->getYEnd() <= pVector->getYStart()))
				{
					for (int i = 0; i < _EntityRect.w; i++){
						temp = (m_Map->w * ((int)dblY)) + ((int)dblX + i);
						if (temp >= 0){
							if (((unsigned int*)m_Map->pixels)[temp] > TRANSPARENCY){
								CollisionPosition->setXY(dblX, dblY);
								delete pVector;
								if ((dblX > WIDTH) || (dblY > HEIGHT) || (dblX < (0 - _EntityRect.w)) || (dblY < (0 - _EntityRect.h)))
									CollisionPosition->setState(true);
								return CollisionPosition;
							}
						}
					}
					for (int i = 0; i < _EntityRect.h; i++){
						temp = (m_Map->w * ((int)dblY + i)) + ((int)dblX);
						if (temp >= 0){
							if (((unsigned int*)m_Map->pixels)[temp] > TRANSPARENCY){
								CollisionPosition->setXY(dblX, dblY);
								delete pVector;
								if ((dblX > WIDTH) || (dblY > HEIGHT) || (dblX < (0 - _EntityRect.w)) || (dblY < (0 - _EntityRect.h)))
									CollisionPosition->setState(true);
								return CollisionPosition;
							}
						}
					}
					dblX = pVector->getComposanteX() + pVector->getXStart();
					dblY = pVector->getComposanteY() + pVector->getYStart();
					pVector->setDOUBLE_XY_START(dblX, dblY);
				}
			}
			
				//x=0 y>0
			if (((pVector->getComposanteX()) == 0) && (pVector->getComposanteY() > 0)){
				while (pVector->getYEnd() >= pVector->getYStart())
				{
					for (int i = 0; i < _EntityRect.w; i++){
						temp = (m_Map->w * ((int)dblY + _EntityRect.h)) + ((int)dblX + i);
						if (temp >= 0){
							if (((unsigned int*)m_Map->pixels)[temp] > TRANSPARENCY){
								CollisionPosition->setXY(dblX, dblY);
								delete pVector;
								if ((dblX > WIDTH) || (dblY > HEIGHT) || (dblX < (0 - _EntityRect.w)) || (dblY < (0 - _EntityRect.h)))
									CollisionPosition->setState(true);
								return CollisionPosition;
							}
						}
					}
					dblX = pVector->getComposanteX() + pVector->getXStart();
					dblY = pVector->getComposanteY() + pVector->getYStart();
					pVector->setDOUBLE_XY_START(dblX, dblY);
				}
			}
			
				//x=0 y<0
			if (((pVector->getComposanteX()) == 0) && (pVector->getComposanteY() < 0)){
				while (pVector->getYEnd() <= pVector->getYStart())
				{
					for (int i = 0; i < _EntityRect.w; i++){
						temp = (m_Map->w * ((int)dblY)) + ((int)dblX + i);
						if (temp >= 0){
							if (((unsigned int*)m_Map->pixels)[temp] > TRANSPARENCY){
								CollisionPosition->setXY(dblX, dblY);
								delete pVector;
								if ((dblX > WIDTH) || (dblY > HEIGHT) || (dblX < (0 - _EntityRect.w)) || (dblY < (0 - _EntityRect.h)))
									CollisionPosition->setState(true);
								return CollisionPosition;
							}
						}
					}
					dblX = pVector->getComposanteX() + pVector->getXStart();
					dblY = pVector->getComposanteY() + pVector->getYStart();
					pVector->setDOUBLE_XY_START(dblX, dblY);
				}
			}
			
				//x>0 y=0
			if (((pVector->getComposanteX()) > 0) && (pVector->getComposanteY() == 0)){
				while (pVector->getXEnd() >= pVector->getXStart())
				{
					for (int i = 0; i < _EntityRect.h; i++){
						temp = (m_Map->w * ((int)dblY + i)) + ((int)dblX + _EntityRect.w);
						if (temp >= 0){
							if (((unsigned int*)m_Map->pixels)[temp] > TRANSPARENCY){
								CollisionPosition->setXY(dblX, dblY);
								delete pVector;
								if ((dblX > WIDTH) || (dblY > HEIGHT) || (dblX < (0 - _EntityRect.w)) || (dblY < (0 - _EntityRect.h)))
									CollisionPosition->setState(true);
								return CollisionPosition;
							}
						}
					}
					dblX = pVector->getComposanteX() + pVector->getXStart();
					dblY = pVector->getComposanteY() + pVector->getYStart();
					pVector->setDOUBLE_XY_START(dblX, dblY);
				}
			}
			
				//x<0 y=0
			if (((pVector->getComposanteX()) < 0) && (pVector->getComposanteY() == 0)){
				while (pVector->getXEnd() <= pVector->getXStart())
				{
					for (int i = 0; i < _EntityRect.h; i++){
						temp = (m_Map->w * ((int)dblY + i)) + ((int)dblX);
						if (temp >= 0){
							if (((unsigned int*)m_Map->pixels)[temp] > TRANSPARENCY){
								CollisionPosition->setXY(dblX, dblY);
								delete pVector;
								if ((dblX > WIDTH) || (dblY > HEIGHT) || (dblX < (0 - _EntityRect.w)) || (dblY < (0 - _EntityRect.h)))
									CollisionPosition->setState(true);
								return CollisionPosition;
							}
						}
					}
					dblX = pVector->getComposanteX() + pVector->getXStart();
					dblY = pVector->getComposanteY() + pVector->getYStart();
					pVector->setDOUBLE_XY_START(dblX, dblY);
				}
			}
			CollisionPosition->setXY(pVector->getXfin(), pVector->getYfin());
			delete pVector;
			return CollisionPosition;
		}
		delete pVector;
		return nullptr;
	}
	
	/*!
	 @method Evaluate Slope
	 @brief  Fonction qui retourne la pente (en degr�s) � partir d'une section de la map
	 @param _Pos : Position dans la surface o� la pente est �valu�e
	 @param _Direction : Direction de laquelle vient l'entit� impliqu�e
	 @return L'angle de la pennte en degr�;
	 */
	static double EvaluateSlope(SDL_Rect _Rect){
		double Slope = 0;
		bool first = false;
		int PreviousY = 0;
		double PointsSignificatifs = 0;
		for (int x = _Rect.x; x < _Rect.x + _Rect.w; x++){
			for (int y = _Rect.y; y < _Rect.y + _Rect.h; y++){
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
						y = _Rect.y + _Rect.h;
					}
				}
			}
		}
		double Angle = atan(Slope / (PointsSignificatifs - 1));
		return Angle;
	}
	
	/*
	 Method : VerifyIfSliding
	 Brief : Fonction qui retourne la trajectoire d'une chose en train de glisser par rapport au terrain
	 Params:
	 _Rect : Rectangle � �valuer
	 */
	static bool VerifyIfSliding(SDL_Rect* _Rect){
		int iNbrPixels = 0; //Nombre de pixels en contact directement sous le rectangle
		for (int i = 0; i < _Rect->w; i++){
			if (((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect->y + _Rect->h) + _Rect->x + i] == TRANSPARENCY){
				iNbrPixels++;
			}
		}
		return (iNbrPixels < _Rect->w / 2);//On suppose qu'� 50% du rect en contact avec le sol, aucune glissade ne survient
	}
	
	/*!
	 @method Propulsion
	 @brief  Retourne une trajectoire selon un vitesse de d�part et un acc�l�ration
	 @param _PosInit: Position initiale de l'objet subbisant la propulsion
	 @param _Vit: Vitesse et direction initial du glissement
	 @param _Acc: Position initial de l'entit�
	 @return La trajectoire de ala propuslion
	 @discussion Aucune.
	 */
	static CTrajectory* Propulsion(CPosition* _PosInit, C2DVector* _Vit, C2DVector* _Acc){
		return new CTrajectory(_PosInit, _Vit, *_Acc + m_Wind);
	}
	
	/*!
	 @method Slide
	 @brief  Fonction qui fait glisser si la pente est trop grande
	 @param _Rect : Rectangle de l'objet impliqu�
	 @return La trajectoire du glissement
	 */
	/*static CTrajectory * Slide(CEntity* _Entity){
		SDL_Rect* TmpRect = new SDL_Rect({ _Entity->getPosition().x, _Entity->getPosition().y + _Entity->getPosition().h
	 , 50, _Entity->getPosition().w }); //Le 50 est arbitraire because or reasons
		double AngleDePente = CPhysics::EvaluateSlope(TmpRect);
		if (_Entity->getTrajectoire() != nullptr){
		}
		else{
		}
	 }*/
	
	/*!
	 @method Move
	 @brief  Fonction qui ajuste la position suite � un mouvement sans acc�l�ration
	 @param _Rect : Rectangle se d�pla�ant
	 @param _Direction : Bool de la direction emprunt�e (true = gauche, false = droite))
	 @return BLOCKED: Si l'entit� est pogn�e
	 @return MOVING: Si l'entit� peut continuer
	 @discussion Ne d�place actuellement que d'un pixel sur l'axe X, � changer si voulu La hauteur (en pixels) d'une pente "escaladable" en y sera � d�terminer (actuellement 3 pixels)
	 */
	static int Move(SDL_Rect* _Rect, int _Direction){
		if (_Direction == LEFT){
			for (int i = 0; i < _Rect->h / 2; i++){
				if (((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect->y + i) + _Rect->x] != 0){
					if (i < _Rect->h)
						return BLOCKED;
				}
				else{
					_Rect->x = _Rect->x - 1;
					return MOVING;
				}
			}
		}
		else{
			for (int i = 0; i < _Rect->h / 2; i++){
				if (((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect->y + i) + _Rect->x + _Rect->w] != 0){
					if (i < _Rect->h)
						return BLOCKED;
				}
				else{
					_Rect->x = _Rect->x + 1;
					return MOVING;
				}
			}
		}
		return NULL;
	}
	
	/*!
	 @method Acesseurs
	 @brief Servent a acceder/modifier aux donn�es membres.
	 */
	static C2DVector* GetWind(){
		return m_Wind;
	}
	static double GetGravity(){
		return m_Gravity;
	}
	static void setGravity(double _d){
		m_Gravity = _d;
	}
	static SDL_Surface* GetMap(){
		return m_Map;
	}
};
C2DVector * CPhysics::m_Wind = nullptr;
double CPhysics::m_Gravity = 1;
int CPhysics::m_MaxSpeed = 1;
int CPhysics::m_MaxWindSpeed = 50;
SDL_Surface * CPhysics::m_Map = nullptr;
