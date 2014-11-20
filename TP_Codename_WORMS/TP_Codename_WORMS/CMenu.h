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
	CListeDC<CGUIE*>* m_pList; // Liste de contr�le visuel.
	SDL_Renderer* m_pRenderer; // Rendu de la fen�tre sur la quelle afficher le menu.
	SDL_Rect m_MenuInfo;	   // Position et dimension du menu.
	bool m_boMenuActif;		   // Indique si le menu est actif ou non
	SDL_Texture* m_pBackground;
public:



	/*!
	@ Constructeur
	@brief Initialise les donn�es membres.
	@param _Renderer : Renderer de la fenetre.
	@param _PositionDimension : Informations sur la position et la dimension de la f�netre.
	@return l'adresse m�moire de l'objet.
	*/
	CMenu(SDL_Renderer* _Renderer, SDL_Rect _PositionDimension){
		m_pList = new CListeDC <CGUIE*>;
		m_pRenderer = _Renderer;
		m_MenuInfo.x = _PositionDimension.x;
		m_MenuInfo.y = _PositionDimension.y;
		m_MenuInfo.w = _PositionDimension.w;
		m_MenuInfo.h = _PositionDimension.h;
		m_boMenuActif = false;
		m_pBackground = nullptr;
	}

	~CMenu(){
		delete m_pList;
	}

	/*!
	@method AddElement
	@brief Ajoute un Contr�le visuel dans une liste.
	@param  _Element: Contr�le visuel � ajouter
	@param  _uiX: Position en x par rapport a la position du menu.
	@param  _uiY: Position en y par rapport a la position du menu.
	@param  _uiW: Largueur du contr�le
	@param  _uiH: Hauteur du contr�le
	@return true si il n'y avait aucun doublon et ajoute l'objet
	@return false si il y un doublon et ne l'ajoute pas � la liste.
	*/
	bool AddElement(CGUIE* _Element, unsigned int _uiX, unsigned int _uiY, unsigned int _uiW, unsigned int _uiH){
		m_pList->AllerDebut();
		for (int i = 0; i < m_pList->Count(); i++)
		{
			if (m_pList->ObtenirElement()->getName() == _Element->getName())
				return false;
			m_pList->AllerSuivant();
		}
		_Element->setPos(m_MenuInfo.x + _uiX, m_MenuInfo.y + _uiY);
		_Element->setSize(_uiW, _uiH);
		m_pList->AjouterFin(_Element);
		return true;
	}

	/*!
	 @method ClickEvent.
	 @brief Appelle le bon OnClick.
	 @param  _uiX: Position en x de la souris.
	 @param  _uiY: Position en y de la souris.
	 @return Aucun.
	 */
	void HandleEvent(SDL_Event _Event){
		if (m_boMenuActif){
			CGUIE* Temp;
			unsigned int uiXTemp, uiYTemp;
			m_pList->AllerDebut();
			for (int i = 0; i < m_pList->Count(); i++){
				Temp = m_pList->ObtenirElement();
				uiXTemp = Temp->getX();
				uiYTemp = Temp->getY();
				if (Temp->isTextBox()){
					if ((_Event.button.x >= uiXTemp) &&
						(_Event.button.x <= (uiXTemp + Temp->getWidth())) &&
						(_Event.button.y >= uiYTemp) &&
						(_Event.button.y <= (uiYTemp + Temp->getHeight())) &&
						(_Event.type == SDL_MOUSEBUTTONDOWN)){
						Temp->setFocus(true);
						break;
					}
				}
				else{
					if ((_Event.button.x >= uiXTemp) &&
						(_Event.button.x <= (uiXTemp + Temp->getWidth())) &&
						(_Event.button.y >= uiYTemp) &&
						(_Event.button.y <= (uiYTemp + Temp->getHeight()))){
						Temp->setFocus(true);
						break;
					}
					else if (Temp->isFocussed())
						Temp->setFocus(false);
				}
				m_pList->AllerSuivant();
			}
			for (int i = 0; i < m_pList->Count(); i++){
				Temp = m_pList->ObtenirElement();
				if (Temp->isFocussed()){
					Temp->HandleEvent(_Event);
					break;
				}
			}
			
		}
	}

	/*!
	@method Render
	@brief Appelle la fonction Draw de chaque contr�le visuel dans la liste.
	@param  Aucun
	@return Aucun.
	*/
	void Render(){
		if (m_boMenuActif)
		{
			if (m_pBackground != nullptr){
				SDL_RenderCopy(m_pRenderer, m_pBackground, NULL, &m_MenuInfo);
			}
			else{
				SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND);
				SDL_SetRenderDrawColor(m_pRenderer, 50, 50, 50, 150);
				SDL_RenderFillRect(m_pRenderer, &m_MenuInfo);
			}
			m_pList->AllerDebut();
			for (int i = 0; i < m_pList->Count(); i++)
			{
				m_pList->ObtenirElement()->Draw(m_pRenderer);
				m_pList->AllerSuivant();
			}
		}
	}

	/*!
	@method setOnCreenPos
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

	void ActivateMenu(){
		m_boMenuActif = true;
	}

	void DeActivateMenu(){
		m_boMenuActif = false;
	}

	bool IsActive(){
		return m_boMenuActif;
	}

	/*!
	@method setSize
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
	@method getElement
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

	void setBackground(SDL_Texture* _Texture){
		m_pBackground = _Texture;
	}


};