//
//  CMenu.h
//  TP_Codename_WORMS
//
//  Cr�� par Kevin Pantelakis le 2014-10-28.
//  Mise � jour par Kevin Pantelakis le 2014-10-29
//  
//

/*!
@class CMenus
@discussion Classe qui repr�sente les menus
*/
class CMenu{
private:
	CListeDC<CGUIE*>* m_pList;
	SDL_Renderer* m_pRenderer;
	bool m_boMenuActif;
public:


	//Pour une raison obscure un fenetre ne peut contenir plus d'un renderer.
	/*!
	@ Constructeur
	@brief Initialise les donn�es membres
	@param _Window : Fen�tre ou afficher le renderer
	@return l'adresse m�moire de l'objet
	*/
	CMenu(SDL_Renderer* _Renderer){
		m_pList = new CListeDC < CGUIE* >;
		m_pRenderer = _Renderer;
		m_boMenuActif = false;
	}

	/*
	CMenu(SDL_Window* _Window){
		m_pList = new CListeDC < CGUIE* >;
		m_pRenderer = SDL_CreateRenderer(_Window, -1, SDL_RENDERER_ACCELERATED);
		m_boMenuActif = false;
	}
	*/


	~CMenu(){
		SDL_DestroyRenderer(m_pRenderer);
		delete m_pList;
	}

	void ActivateMenu(){
		m_boMenuActif = true;
	}

	void DisableMenu(){
		m_boMenuActif = false;
	}

	/*!
	@Method AddElement
	@brief Ajoute un Contr�le visuel dans une liste.
	@param  _Element: Contr�le visuel � ajouter
	@param  _uiX: Position en x
	@param  _uiY: Position en y
	@param  _uiW: Largueur du contr�le
	@param  _uiH: Hauteur du contr�le
	@return true si il n'y avait aucun doublon et ajoute l'objet
	@return false si il y un doublon et ne l'ajoute pas � la liste.
	*/
	bool AddElement(CGUIE* _Element, unsigned int _uiX, unsigned int _uiY, unsigned int _uiW, unsigned int _uiH){
		for (int i = 0; i < m_pList->Count(); i++)
		{
			if (m_pList->ObtenirElement()->getName() == _Element->getName())
				return false;
			m_pList->AllerSuivant();
		}
		_Element->setPos(_uiX, _uiY);
		_Element->setSize(_uiW, _uiH);
		m_pList->AjouterFin(_Element);
		return true;
	}

	/*!
	@Method Render
	@brief Appelle la fonction Draw de chaque contr�le visuel dans la liste.
	@param  Aucun
	@return Aucun.
	*/
	void Render(){
		if (m_boMenuActif)
		{
			m_pList->AllerDebut();
			for (int i = 0; i < m_pList->Count(); i++)
			{
				m_pList->ObtenirElement()->Draw(m_pRenderer);
				m_pList->AllerSuivant();
			}
		}
	}

	/*!
	@Method setOnCreenPos
	@brief D�finit un nouvel emplacement pour le contr�le visuel.
	@param  _chrName: Nom du Contr�le Visuel.
	@param  _uiX: Position en x
	@param  _uiY: Position en y
	@return Aucun.
	*/
	void setOnScreenPos(const char* _chrName, unsigned int _uiX, unsigned int _uiY){
		m_pList->AllerDebut();
		for (int i = 0; i < m_pList->Count(); i++)
		{
			if (m_pList->ObtenirElement()->getName() == _chrName){
				m_pList->ObtenirElement()->setPos(_uiX, _uiY);
				break;
			}
			m_pList->AllerSuivant();
		}
	}

	/*!
	@Method setSize
	@brief Modifie la taille du contr�le visuel.
	@param  _chrName: Nom du controle a changer.
	@param  _uiWidth: Largueur.
	@param  _uiHeight: Hauteur.
	@return Aucun.
	*/
	void setSize(const char* _chrName, unsigned int _uiWidth, unsigned int _uiHeight){
		m_pList->AllerDebut();
		for (int i = 0; i < m_pList->Count(); i++)
		{
			if (m_pList->ObtenirElement()->getName() == _chrName){
				m_pList->ObtenirElement()->setPos(_uiWidth, _uiHeight);
				break;
			}
			m_pList->AllerSuivant();
		}
	}

	/*!
	@Method getElement
	@brief : Obtient le contr�le visuel d�sir�
	@param  _chrName: Nom du controle a trouver.
	@return Le controle visuel rechercher si il est pr�sent.
	@return nullptr si le controle ne fait pas parti de la liste.
	*/
	CGUIE* getElement(const char* _chrName){
		m_pList->AllerDebut();
		for (int i = 0; i < m_pList->Count(); i++)
		{
			if (m_pList->ObtenirElement()->getName() == _chrName)
				return m_pList->ObtenirElement();
			m_pList->AllerSuivant();
		}
		return nullptr;
	}

	SDL_Renderer* getRenderer(){
		return m_pRenderer;
	}

	/*!
	@Method ClickEvent.
	@brief Appelle le bon OnClick.
	@param  _uiX: Position en x de la souris.
	@param  _uiY: Position en y de la souris.
	@return Aucun.
	*/
	void ClickEvent(unsigned int _uiX, unsigned int _uiY){
		if (m_boMenuActif)
		{
			CGUIE* Temp;
			unsigned int uiXTemp, uiYTemp;
			m_pList->AllerDebut();
			for (int i = 0; i < m_pList->Count(); i++)
			{
				Temp = m_pList->ObtenirElement();
				uiXTemp = Temp->getX();
				uiYTemp = Temp->getY();
				if ((_uiX >= uiXTemp) &&
					(_uiX <= (uiXTemp + Temp->getWidth())) &&
					(_uiY >= uiYTemp) &&
					(_uiY <= (uiYTemp + Temp->getHeight()))){
					Temp->OnClick();
					break;
				}
				m_pList->AllerSuivant();
			}
		}
	}

};