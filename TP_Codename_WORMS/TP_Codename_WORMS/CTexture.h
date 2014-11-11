class CTexture :public CRessource{
private:
	SDL_Texture* m_pTexture; // Texture de l'image � afficher
public:

	CTexture(const char* _strName, SDL_Texture* _Texture) : CRessource(_strName){
		m_pTexture = _Texture;
	}

	~CTexture(){
		SDL_DestroyTexture(m_pTexture);
	}

	SDL_Texture* GetTexture(){
		return m_pTexture;
	}

};