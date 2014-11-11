#ifndef TP_Codename_WORMS_CMissiles_h
#define TP_Codename_WORMS_CMissiles_h


/*!
@CGrenades
@Classe permettant la cr�ation d'une grenade
*/
class CMissiles : public CObjets{

public:
	/*!
	@Constructeur
	@Description: Permet d'initialiser les donn�es membres
	@Param�tres: Le nom du labelImage afin de l'identifier, le text � l'int�rieur, le font et le rect, et la texture contenant l'image.
	@Classe h�ritant de CGUIE, donc elle passe les param�tres n�cessaires au constructeur de CGUIE
	*/
	CMissiles() :CObjets(){
	}
	/*!
	@Destructeur:
	@Permet de d�truire les objets cr��s en m�moire
	*/
	~CMissiles(){
	}



	/*!
	@Accesseurs:
	*/

};

#endif
