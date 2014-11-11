#ifndef TP_Codename_WORMS_CEntity_h
#define TP_Codename_WORMS_CEntity_h


/*!
@CEntity
@Classe Abstraite repr�sentant les entit�es affect�s par la physique.
*/
class CEntity{
private:
	const char* m_strName;
	unsigned int m_uiMasse;
	SDL_Rect m_RectPosition;
	bool m_boFocus;
public:

	/*!
	@Constructeur
	@Description: Permet d'initialiser les donn�es membres
	@Param�tres:
	*/
	CEntity(const char* _Name, unsigned int _uiMasse,SDL_Rect _RectPos){
		m_strName = _Name;
		m_uiMasse = _uiMasse;
		m_RectPosition = _RectPos;
		m_boFocus = false;
	}

	/*!
	@Destructeur:
	@Permet de d�truire les objets cr��s en m�moire
	*/
	~CEntity(){
		delete m_strName;
	}

	/*!
	@Accesseurs:
	*/
	const char* getName(){
		return m_strName;
	}

	unsigned int m_uiMasse(){
		return m_uiMasse;
	}

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
