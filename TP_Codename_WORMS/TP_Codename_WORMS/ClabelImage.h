#ifndef TP_Codename_WORMS_CLabelImage_h
#define TP_Codename_WORMS_CLabelImage_h


/*!
@CLabelImage
@Classe permettant la cr�ation et l'affichage d'un label contenant du texte et une image.
*/
class CLabelImage : public CLabel {
private:
	//Donn�es membres:
	SDL_Texture* m_pTexture;

public:
	/*!
	@Constructeur
	@Description: Permet d'initialiser les donn�es membres
	@Param�tres: Le nom du labelImage afin de l'identifier, le text � l'int�rieur, le font et le rect, et la texture contenant l'image.
	@Classe h�ritant de CGUIE, donc elle passe les param�tres n�cessaires au constructeur de CGUIE
	*/
	CLabelImage(const char* _Name, const char* _strText, CFont* _Font, SDL_Rect _Rect, SDL_Texture* _Texture) :CLabel(_Name, _strText, _Font, _Rect){
		m_pTexture = _Texture;
		m_Font->setFontColor(SDL_Color{ 0, 0, 0, 0 });

	}
	/*!
	@Destructeur:
	@Permet de d�truire les objets cr��s en m�moire
	*/
	~CLabelImage(){
	}
	/*!
	@M�thode Draw:
	@Fonction permettant de dessiner le LabelImage sur le renderer.
	@Param�tre: Le renderer sur lequel on dessine l'image
	*/
	void Draw(SDL_Renderer* _Renderer){
		SDL_RenderCopy(_Renderer, m_pTexture, NULL, &m_Rect);
		m_Font->RenderText(_Renderer, m_strText.c_str(), m_Rect.x, m_Rect.y);
	}

	/*!
	@M�thode AutoSize:
	@Fonction permettant de rendre l'image du label de la m�me dimension que le texte.
	*/
	void Autosize(){
		m_Rect.w = m_strText.length() * (m_Font->getFontSize());
		m_Rect.h = m_Font->getFontSize();
	}
	/*!
	@Accesseurs:
	*/
	void DefinirFontColor(unsigned int _iR, unsigned int _iB, unsigned int _iG, unsigned int _iA){
		m_Font->setFontColor(SDL_Color{ _iR, _iB, _iG, _iA });
	}

	void DefinirPositionLabel(int _iX, int _iY){
		m_Rect.x = _iX;
		m_Rect.y = _iY;
	}

	int ObtenirWidth(){
		return m_Rect.w;
	}
	int ObtenirHeight(){
		return m_Rect.h;
	}
};

#endif
