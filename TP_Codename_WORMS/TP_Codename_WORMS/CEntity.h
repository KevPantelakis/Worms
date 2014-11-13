#ifndef TP_Codename_WORMS_CEntity_h
#define TP_Codename_WORMS_CEntity_h


/*!
@CEntity
@Classe Abstraite repr�sentant les entit�es affect�s par la physique.
*/
class CEntity{
protected:
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
	SDL_Rect getPosition(){
		return m_RectPosition;
	}

	bool isFocused(){
		return m_boFocus;
	}

	void setFocus(bool _Focus){
		m_boFocus = _Focus;
	}

	virtual void ReactToExplosion(int,int,int) = 0;
	virtual void HandleEvent(SDL_Event) = 0;

};

#endif
