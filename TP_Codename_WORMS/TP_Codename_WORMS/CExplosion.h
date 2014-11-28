#ifndef TP_Codename_WORMS_CExplosion_h
#define TP_Codename_WORMS_CExplosion_h

class CExplosion{
private:
	CSprite* m_pSprite;		//Donn�e membre repr�sentant le sprite d'explosion.
	CPosition* m_pPosition;	//Donn�e membre repr�sentant la position de l'explosion.

public:

	/*!
	@method Constructeur.
	@brief Initialise les donn�es membres.
	@param _Sprite : le sprite de de l'explosion
	@return Adresse m�moire de l'objet.
	@discussion No discussion is needed.
	*/
	CExplosion(CSprite* _Sprite){
		m_pSprite = _Sprite;
		m_pSprite->setSpritePos(m_pPosition->getX(), m_pPosition->getY());
	}

	/*!
	@method Draw
	@param _Renderer : Renderer pour rendre la textures du Sprite.
	@return null
	*/
	void Draw(SDL_Renderer* _pRenderer){
		m_pSprite->Render(_pRenderer);
	}

	/*!
	@Destructeur:
	@Permet de d�truire les objets cr��s en m�moire
	*/
	~CExplosion(){
	}

};

#endif