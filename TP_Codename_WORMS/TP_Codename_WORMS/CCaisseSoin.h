#ifndef TP_Codename_WORMS_CCaisseSoin_h
#define TP_Codename_WORMS_CCaisseSoin_h


/*!
@CCaisseSoin
@Classe permettant la cr�ation d'une caisse de soin
*/
class CCaisseSoin : public CCaisses{
private:

	//Donn�es membres:
	SDL_Texture* m_pTexture; // Texture de l'image � afficher.

public:


	CCaisseSoin(int _iRayon, SDL_Rect _RectPos , SDL_Texture* _pTexture) :CCaisses(_iRayon, _RectPos,_pTexture){
	}





	/*!
	@Accesseurs:
	*/

	/*!
	@Destructeur:
	@Permet de d�truire les objets cr��s en m�moire
	*/
	~CCaisseSoin(){
	}

};

#endif
