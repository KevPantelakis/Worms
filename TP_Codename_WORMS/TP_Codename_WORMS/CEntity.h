#ifndef TP_Codename_WORMS_CEntity_h
#define TP_Codename_WORMS_CEntity_h


/*!
@CEntity
@Classe Abstraite repr�sentant les entit�es affect�s par la physique.
*/
class CEntity{
protected:
	string m_strName;
	SDL_Rect m_RectPosition;
	bool m_boFocus;
public:

	/*!
	@Constructeur
	@Description: Permet d'initialiser les donn�es membres
	@Param�tres:
	*/
	CEntity(SDL_Rect _RectPos){
		m_RectPosition = _RectPos;
		m_boFocus = false;
	}

	/*!
	@Destructeur:
	@Permet de d�truire les objets cr��s en m�moire
	*/
	~CEntity(){
	}

	/*!
	@Accesseurs:
	*/
	const char* getName(){
<<<<<<< HEAD
	}
=======
		return m_strName;
	}

		//	unsigned int m_uiMasse(){
		//return m_uiMasse;
		//	}
>>>>>>> 620d262c90c1eaa43e43336d6e0d57479837c984

	SDL_Rect getPosition(){
		return m_RectPosition;
	}

	bool isFocused(){
		return m_boFocus;
	}

	void setFocus(bool _Focus){
		m_boFocus = _Focus;
	}

	virtual void ReactToExplosion() = 0;
	virtual void HandleEvent() = 0;

};

#endif
