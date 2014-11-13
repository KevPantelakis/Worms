#ifndef TP_Codename_WORMS_CCaisseSoin_h
#define TP_Codename_WORMS_CCaisseSoin_h


/*!
@CCaisseSoin
@Classe permettant la cr�ation d'une caisse de soin
*/
class CCaisseSoin : public CCaisses{

public:
	/*!
	@Constructeur
	@Description: Permet d'initialiser les donn�es membres
	@Param�tres: Le nom du labelImage afin de l'identifier, le text � l'int�rieur, le font et le rect, et la texture contenant l'image.
	@Classe h�ritant de CGUIE, donc elle passe les param�tres n�cessaires au constructeur de CGUIE
	*/
	CCaisseSoin(const char* _Name, unsigned int _uiMasse, SDL_Rect _RectPos) :CCaisses(_Name, _uiMasse, _RectPos){
	}
	/*!
	@Destructeur:
	@Permet de d�truire les objets cr��s en m�moire
	*/
	~CCaisseSoin(){
	}



	/*!
	@Accesseurs:
	*/

};

#endif
