#ifndef TP_Codename_WORMS_CEntity_h
#define TP_Codename_WORMS_CEntity_h

enum EntityStates {Chute, Immobile, Deplacement};


/*!
@CEntity
@Classe Abstraite repr�sentant les entit�es affect�s par la physique.
*/
class CEntity{
protected:
	SDL_Rect m_RectPosition; // Position de l'Entit�
	bool m_boFocus;			 // Indique si l'entit� a le Focus
	CTrajectory* m_Trajectoire;
	unsigned int m_EntityState;
	SDL_Texture* m_pTexture;
	C2DVector* m_pForce;
public:

	/*!
	@Constructeur
	@Description: Permet d'initialiser les donn�es membres
	@Param�tres:
	*/
	CEntity(SDL_Rect _RectPos, SDL_Texture* _Texture){
		m_RectPosition = _RectPos;
		m_boFocus = false;
		m_Trajectoire = nullptr;
		m_EntityState = 0;
	}

	/*!
	@Destructeur:
	@Permet de d�truire les objets cr��s en m�moire
	*/
	~CEntity(){
		delete m_Trajectoire;
		m_Trajectoire = nullptr;
		delete m_pForce;
	}
	
	virtual void Move(){
		switch (m_EntityState) {
			case Chute:
					//m_pForce = m_Trajectoire->GetPosition();
				m_RectPosition.y = m_pForce->getY();
				m_RectPosition.x = m_pForce->getX();
    			break;
		}
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
