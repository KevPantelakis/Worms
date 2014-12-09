#ifndef TP_Codename_WORMS_CMissiles_h
#define TP_Codename_WORMS_CMissiles_h


/*!
@CMissiles
@Classe permettant la cr�ation d'un missile
*/
class CMissiles : public CObjets{
private:
	//Donn�es membres:
	bool boIsexploded; //Donn�e repr�sentant si l'objet est explos� (true) ou non (false)
	C2DVector* m_pVectorVitesse;
	C2DVector* m_pVectorAccel;
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
	CMissiles(SDL_Texture* _textureExplosion, SDL_Rect _RectPos, SDL_Texture* _Texture, int _uiPower) :CObjets(_textureExplosion, _RectPos, _Texture){
		boIsexploded = false;
		m_pVectorVitesse = new C2DVector(_RectPos.x, _RectPos.y, 20, 20); // pas bon �a
		m_pVectorAccel = new C2DVector(_RectPos.x, _RectPos.y, 35, 35); // pas bon �a aussi
	}

	/*!
	@Destructeur:
	@Permet de d�truire les objets cr��s en m�moire
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
