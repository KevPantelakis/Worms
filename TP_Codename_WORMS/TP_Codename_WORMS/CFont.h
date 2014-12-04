/*!
@class CFont
@discussion Classe pour l'impl�mentation des police et affichage de texte
*/
class CFont : public CRessource{
private:
	TTF_Font* m_pFont; 			// Membre pour loader la font
	SDL_Surface* m_pSurface;	// Membre pour render du texte
	SDL_Texture* m_pTexture;	// membre pour l'affichage du texte
	SDL_Color m_Color;			// Membre pour la couleur du texte
	SDL_Rect m_Rect;			// Section de l'affichage
	int iSize;                  //Repr�sente la taille de la police de caract�re
public:

	/*!
	@method Constructeur
	@param _FontPath : cosnt char* pour acqueillir le chemin fichier
	@param _iSize : Int pour la grandeur de la police
	*/
	CFont(const char* _Name, const char* _FontPath, int _iSize) : CRessource(_Name){
		m_pSurface = nullptr;
		m_pTexture = nullptr;
		m_pFont = TTF_OpenFont(_FontPath, _iSize);
		m_Color = { 1, 1, 1, 255 };
	}

	/*!
	@method Destructeur:
	@brief Permet de d�truire les objets cr��s en m�moire
	*/
	~CFont(){
		TTF_CloseFont(m_pFont);
		SDL_DestroyTexture(m_pTexture);
		SDL_FreeSurface(m_pSurface);
	}

	/*!
	@method RenderText
	@brief methode pour render du text � l'�cran
	@param _Renderer : Le renderer sur le quel afficher
	@param _chrtext : Le text � afficher
	@param _ix : Position en x
	@param _iy : Position en y
	@return Aucun
	*/
	void RenderText(SDL_Renderer* _Renderer, const char* _chrText, int _ix, int _iy){
		if (m_pSurface)SDL_FreeSurface(m_pSurface);
		m_pSurface = TTF_RenderText_Solid(m_pFont, _chrText, m_Color);
		if (m_pTexture)SDL_DestroyTexture(m_pTexture);
		m_pTexture = SDL_CreateTextureFromSurface(_Renderer, m_pSurface);
		SDL_QueryTexture(m_pTexture, NULL, NULL, &m_Rect.w, &m_Rect.h);
		m_Rect.x = _ix;
		m_Rect.y = _iy;
		SDL_RenderCopy(_Renderer, m_pTexture, NULL, &m_Rect);
	}

	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux donn�es membres.
	*/
	
	void setFontColor(SDL_Color _Color){
		m_Color = _Color;
	}

	int getFontSize(){
		return iSize;
	}


};
