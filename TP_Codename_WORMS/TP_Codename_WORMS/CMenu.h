/*!
@class CMenus
@discussion Classe qui repr�sente les menus
*/
class CMenu{
private:
	CListeDC<CGUIE*>* m_pList;
	SDL_Renderer* m_pRenderer;
public:

	/*!
	@ Constructeur
	@brief Initialise les donn�es membres
	@param _Window : Fen�tre ou afficher le renderer
	@return l'adresse m�moire de l'objet
	*/
	CMenu(SDL_Window* _Window){
		m_pList = new CListeDC < CGUIE* >;
		SDL_CreateRenderer(_Window, NULL, NULL);
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
	@return false si il y un doublon et ne l'ajoute pas � la liste.
	*/
	void Render(){
		m_pList->AllerDebut();
		for (int i = 0; i < m_pList->Count(); i++)
		{
			m_pList->ObtenirElement()->Draw(m_pRenderer);
			m_pList->AllerSuivant();
		}
	}

	/*!
	@Method setOnCreenPos
	@brief D�finit un nouvel emplacement pour le contr�le visuel.
	@param  _Element: Contr�le visuel � ajouter
	@param  _uiX: Position en x
	@param  _uiY: Position en y
	@return Aucun.
	*/
	void setOnScreenPos(const char* _Name, unsigned int _uiX, unsigned int _uiY){
		m_pList->AllerDebut();
		for (int i = 0; i < m_pList->Count(); i++)
		{
			if (m_pList->ObtenirElement()->getName() == _Name){
				m_pList->ObtenirElement()->setPos(_uiX, _uiY);
				break;
			}
			m_pList->AllerSuivant();
		}
	}

	/*!
	@Method setSize
	@brief Modifie la taille du contr�le visuel.
	@param  _Name: Nom du controle a changer.
	@param  _uiWidth: Largueur.
	@param  _uiHeight: Hauteur.
	@return Aucun.
	*/
	void setSize(const char* _Name, unsigned int _uiWidth, unsigned int _uiHeight){
		m_pList->AllerDebut();
		for (int i = 0; i < m_pList->Count(); i++)
		{
			if (m_pList->ObtenirElement()->getName() == _Name){
				m_pList->ObtenirElement()->setPos(_uiWidth, _uiHeight);
				break;
			}
			m_pList->AllerSuivant();
		}
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

};