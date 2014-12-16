#ifndef TP_Codename_WORMS_CMissiles_h
#define TP_Codename_WORMS_CMissiles_h
enum MissileStates { BazzLeft, BazzRight };
/*!
@CMissiles
@Classe permettant la cr�ation d'un missile
*/
class CMissiles : public CObjets{
private:
	//Donn�es membres:
	bool boIsexploded; //Donn�e repr�sentant si l'objet est explos� (true) ou non (false).
	int m_iPower; // Donn�e repr�sentant le power du missile donn� par le bazouka.
	int m_iAngle; // Donn�e repr�sentant l'angle d'inclinaison du bazouka.
public:


	/*!
	@method Constructeur.
	@brief Initialise les donn�es membres.
	@param _iRayon: le rayond d'explosion de l'objet
	@param _RectPos: la pos du rectangle de l'objet
	@param _pTexture : texture de l'image � afficher
	@return Adresse m�moire de l'objet.
	@discussion Classe h�ritant de CObjets, elle prend donc les param�tres du constructeur CObjets
	*/
	CMissiles(SDL_Rect _RectPos, SDL_Texture* _Texture, int _iPower, int _iAngle, CExplosion* _Explosion, int _uiMissileState) :CObjets( _RectPos, _Texture, _Explosion){
		boIsexploded = false;
		m_iPower = _iPower;
		m_iAngle = _iAngle;
		m_Trajectoire = nullptr;
		m_EntityState = _uiMissileState;
	}

	/*!
	@method Destructeur.
	@brief Destroy.
	@discussion He is dead.
	*/
	~CMissiles(){
	}

	void Move(){
		switch (m_EntityState){
		case Deplacement:
			m_Trajectoire->UpdatePosition();
			CPosition* temp = CPhysics::VerifyNextPosition(m_Trajectoire, m_RectPosition);
			if (temp != nullptr)
			{
				m_Trajectoire = (CPhysics::Propulsion(temp, m_pVectorVitesse, m_pVectorAccel));
				m_RectPosition.y = temp->getY();
				m_RectPosition.x = temp->getX();
				delete temp;
			}
			else{
				m_RectPosition.x = m_Trajectoire->GetActualPosition()->getX();
				m_RectPosition.y = m_Trajectoire->GetActualPosition()->getY();
			}
			break;
		}
	}

	/*!
	@method Draw
	@param _Renderer : Renderer pour rendre la texture du missile
	@return null
	*/
	void Draw(SDL_Renderer* _pRenderer){
		Move();
		SDL_RenderCopy(_pRenderer, m_pTexture, NULL, &m_RectPosition);
	}

	/*!
	@method HandleEvent
	@param _Event : Un SDL_Event pour traiter les evenement
	@return null
	*/
	void HandleEvent(SDL_Event _Event){
		m_boFocus = true;
	}

	/*!
	@M�thode:
	@ReactToExplosion
	@Permet de calculer les dommages subit par l'explosion
	*/
	void ReactToExplosion(int _iX, int _iY, int _iRayon){}

	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux donn�es membres.
	*/

	void setPos(int _ix, int _iy){
		m_RectPosition.x = _ix;
		m_RectPosition.y = _iy;
	}

	bool IsItexploded(){
		return boIsexploded;
	}

	void setExplosion(bool _boSet){
		boIsexploded = _boSet;
	}


};

#endif
