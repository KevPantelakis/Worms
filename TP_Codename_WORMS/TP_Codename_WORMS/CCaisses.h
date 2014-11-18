#ifndef TP_Codename_WORMS_CCaisses_h
#define TP_Codename_WORMS_CCaisses_h


/*!
@CCaisses
@Classe permettant la cr�ation d'une caisse
*/
class CCaisses : public CObjets{
private:
	//Donn�es membres:
	SDL_Texture* m_pTexture; // Texture de l'image � afficher.
	bool boIsExplosed;//Donn�e repr�sentant si l'objet est explos� (true) ou non (false).

public:
	/*!
	@Constructeur
	@Description: Permet d'initialiser les donn�es membres
	@param _RectPos: la pos du rectangle de l'objet
	@param _pTexture : texture de l'image � afficher
	@Classe h�ritant de CObjets, elle prend donc les param�tres du constructeur CObjets
	*/
	CCaisses(int _iRayon, SDL_Rect _RectPos, SDL_Texture* _pTexture) :CObjets(_iRayon, _RectPos){
		m_pTexture = _pTexture;
		m_iRayon = _iRayon;
		boIsExplosed = false;
	}

	/*!
	@method Draw
	@param _Renderer : Renderer pour rendre la texture de la caisse
	@return null
	*/
	void Draw(SDL_Renderer* _pRenderer){
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
	~CCaisses(){
	}
};

#endif
