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
	/*!
	@Constructeur
	@Description: Permet d'initialiser les donn�es membres
<<<<<<< HEAD
	@Param�tres: 
	@Classe h�ritant 
=======
	@Param�tres: Le nom du labelImage afin de l'identifier, le text � l'int�rieur, le font et le rect, et la texture contenant l'image.
	@Classe h�ritant de CGUIE, donc elle passe les param�tres n�cessaires au constructeur de CGUIE
	*/
	CCaisseSoin(const char* _Name, unsigned int _uiMasse, SDL_Rect _RectPos) :CCaisses(_Name, _uiMasse, _RectPos){
	}
	/*!
	@Destructeur:
	@Permet de d�truire les objets cr��s en m�moire
>>>>>>> 620d262c90c1eaa43e43336d6e0d57479837c984
	*/
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
