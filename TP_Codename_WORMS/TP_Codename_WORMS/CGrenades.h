#ifndef TP_Codename_WORMS_CGrenades_h
#define TP_Codename_WORMS_CGrenades_h


/*!
@CGrenades
@Classe permettant la cr�ation d'une grenade
*/
class CGrenades : public CObjets{
private:
	//Donn�es membres:
	CTimer* m_pTimer; // D�claration d'une nouvelle minuterie pour le temps � �couler avant l'explosion.
	SDL_Texture* m_pTexture; // Texture de l'image � afficher.

public:
	/*!
	@Constructeur
	@Description: Permet d'initialiser les donn�es membres
	 @param _iRayon: le rayond d'explosion de l'objet
	 @param _RectPos: la pos du rectangle de l'objet
	 @param _pTexture : texture de l'image � afficher
	@Classe h�ritant de CObjets, elle prend donc les param�tres du constructeur CObjets
	*/

	CGrenades(int _iRayon, SDL_Rect _RectPos, SDL_Texture* _pTexture) :CObjets(_iRayon,_RectPos){
		m_pTexture = _pTexture;
		m_pTimer = new CTimer();
		m_pTimer->SetTimer(1000);
		m_pTimer->Start();
		m_iRayon = _iRayon;
	}
	
	/*!
	@method Draw
	@param _Renderer : Renderer pour rendre le textures du Sprite et du texte du bouton
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
		if (m_pTimer->IsElapsed())
			Explosed();
	}
	
	/*!
	@M�thode:
	@Explosed
	@Permet de d�clancher l'explosion
	*/
	void Explosed(){
		m_RectPosition.x = 
	}
	/*!
	@M�thode:
	@ReactToExplosion
	@Permet de calculer les dommages subit par l'explosion
	*/
	void ReactToExplosion(int _iX, int _iY, int _iRayon){}
	/*!
	@Accesseurs:
	*/

	void setPos(int _ix, int _iy){
		m_RectPosition.x = _ix;
		m_RectPosition.y = _iy;
	}

	/*!
	@Destructeur:
	@Permet de d�truire les objets cr��s en m�moire
	*/
	~CGrenades(){
	}


};

#endif
