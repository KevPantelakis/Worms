#ifndef TP_Codename_WORMS_CExplosion_h
#define TP_Codename_WORMS_CExplosion_h

class CExplosion{
private:
	CSprite* m_pSprite;//Donn�e membre repr�sentant le sprite d'explosion.
	CPosition* m_pPosition; //Donn�e membre repr�sentant la position de l'explosion.

public:
	/*!
	@Constructeur
	@Description: Permet d'initialiser les donn�es membres
	@param _Sprite : le sprite de l'objet
	@param _RectPos : le rect de l'objet
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