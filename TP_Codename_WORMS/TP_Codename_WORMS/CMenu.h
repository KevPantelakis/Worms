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

	void AddElement(CGUIE* _Element, unsigned int _uiX, unsigned int _uiY, unsigned int _uiW, unsigned int _uiH){
		m_pList->AjouterFin(_Element);
	}

	void setOnScreenPos(const char* _Name, unsigned int _uiX, unsigned int _uiY){
		m_pList->AllerDebut();
		for (int i = 0; i < m_pList->Count(); i++)
		{
			if (m_pList->ObtenirElement()->getName() == _Name){
				
			}
		}
	}


};