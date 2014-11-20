#ifndef TP_Codename_WORMS_CMines_h
#define TP_Codename_WORMS_CMines_h


/*!
@CMines
@Classe permettant la cr�ation d'une mines
*/
class CMines : public CObjets{
private:

	//Donn�es membres:
	CSprite* m_pSprite; // Texture de l'image � afficher.
	bool boIsExplosed; //Donn�e repr�sentant si l'objet est explos� (true) ou non (false)

public:
	/*!
	@Constructeur
	@Description: Permet d'initialiser les donn�es membres
	 @param _iRayon: le rayond d'explosion de l'objet
	 @param _RectPos: la pos du rectangle de l'objet
	 @param _pTexture : texture de l'image � afficher
	@Classe h�ritant de CObjets, elle prend donc les param�tres du constructeur CObjets
	*/

	CMines(int _iRayon, SDL_Rect _RectPos, SDL_Texture* _Texture) :CObjets(_iRayon, _RectPos){
		m_pSprite = new CSprite("", _Texture, 2, 1, 500, 0);
		m_pSprite->setSpritePos(m_RectPosition.x, m_RectPosition.y);
		m_iRayon = _iRayon;
		boIsExplosed = false;
	}
	/*!
	@method Draw
	@param _Renderer : Renderer pour rendre la texture de la mine
	@return null
	*/
	void Draw(SDL_Renderer* _pRenderer){
		if (boIsExplosed)
			m_pSprite->Render(_pRenderer, 1);
		else
			m_pSprite->Render(_pRenderer, 0);
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
	void ReactToExplosion(int _iX, int _iY, int _iRayon){
		boIsExplosed = true;
	}
	/*!
	@Accesseurs:
	*/
	bool IsItExplosed(){
		return boIsExplosed;
	}
	void setExplosion(bool _boSet){
		boIsExplosed = _boSet;
	}

	void setPos(int _ix, int _iy){
		m_RectPosition.x = _ix;
		m_RectPosition.y = _iy;
	}




	/*!
	@Destructeur:
	@Permet de d�truire les objets cr��s en m�moire
	*/
	~CMines(){
	}

};

#endif
