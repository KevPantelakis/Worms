/*	
420-202-RE : Structure de donn�es "la Liste doublement cha�n�e"
Classe CListeDC
Cr�e le 15 avril 2014 par Kevin Pantelakis( DA : 1303126  /  E-mail : kev.pantelakis@gail.com)
*/
template <class T>
class CCelluleListeDC{
private:

	CCelluleListeDC<T>* m_pSuivant;	  // Pointeur de cellule suivante.
	CCelluleListeDC<T>* m_pPrecedent; // Pointeur de cellule pr�c�dente.
	T m_Element;				   	  // �l�ment a contenir dans la liste.

public:

	//Constructeur
	//Param�tre : l'�l�ment a contenir dans la file et les pointeurs de cellule suivante et pr�c�dente.
	//Retour: L'adresse m�moire.
	CCelluleListeDC(T _Element,CCelluleListeDC<T>* _Precedent, CCelluleListeDC<T>* _Suivant){
		m_Element = _Element;
		m_pPrecedent = _Precedent;
		m_pSuivant = _Suivant;
	}

	//Destructeur
	~CCelluleListeDC(){
	}

	//Acesseurs.

	T getElement(){
		return m_Element;
	}

	CCelluleListeDC<T>* getSuivant(){
		return m_pSuivant;
	}

	CCelluleListeDC<T>* getPrecedent(){
		return m_pPrecedent;
	}

	void setSuivant(CCelluleListeDC<T>* _pSuivant){
		m_pSuivant = _pSuivant;
	}

	void setPrecedent(CCelluleListeDC<T>* _pPrecedent){
		m_pPrecedent = _pPrecedent;
	}

};
template <class T>
class CListeDC{
private:

	CCelluleListeDC<T>* m_pDerniere;// Pointe sur la derni�re cellule.
	CCelluleListeDC<T>* m_pCurseur; // Pointeur sur une cellule quelconque.
	unsigned int m_uiCompte;		// Nombre de cellule dans la liste.

public:

	//Constructeur
	CListeDC(){
		m_pDerniere = nullptr;
		m_pCurseur = nullptr;
		m_uiCompte = 0;
	}

	//Destructeur
	~CListeDC(){
		AllerDebut();
		while(m_pDerniere != nullptr)
			 Retirer(true);
	}

	//M�thodes.

	/********************************************************************************
	But: Mettre le curseur au d�but de la liste.

	Param�tres: Aucun.

	Retour: true si l'op�ration s'est faite et false si elle ne s'est pas ex�cut�e.
	********************************************************************************/
	bool AllerDebut(){
		if(m_pDerniere != nullptr)
		{
			m_pCurseur = m_pDerniere->getSuivant();
			return true;
		}
		return false;
	}

	/********************************************************************************
	But:  Mettre le curseur a la fin de la liste.

	Param�tres: Aucun

	Retour: true si l'op�ration s'est faite et false si elle ne s'est pas ex�cut�e.
	********************************************************************************/
	bool AllerFin(){
		if(m_pDerniere != nullptr)
		{
			m_pCurseur = m_pDerniere;
			return true;
		}
		return false;
	}

	/********************************************************************************
	But: D�placer le curseur sur son suivant.

	Param�tres: Aucun.

	Retour: true si l'op�ration s'est faite et false si elle ne s'est pas ex�cut�e.
	********************************************************************************/
	bool AllerSuivant(){
		if((m_pDerniere != nullptr) && (m_pCurseur->getSuivant() != m_pDerniere->getSuivant())){
			m_pCurseur = m_pCurseur->getSuivant();
			return true;
		}
		return false;
	}
	
	/****************************************************************************************
	But: D�placer le curseur sur son pr�c�dent.

	Param�tres: Aucun.

	Retour: Retour: true si l'op�ration s'est faite et false si elle ne s'est pas ex�cut�e.
	****************************************************************************************/
	bool AllerPrecedent(){
		if((m_pDerniere != nullptr) && (m_pCurseur->getPrecedent() != m_pDerniere)){
			m_pCurseur = m_pCurseur->getPrecedent();
			return true;
		}
		return false;
	}

	/*****************************************************************************************
	But: Met le curseur � la position d�sir�e.

	Param�tres: unsigned int _uiPosition d�termine la position ou mettre le curseur

	Retour: true si l'op�ration s'est faite et false si elle ne s'est pas ex�cut�e.
	*****************************************************************************************/
	bool AllerA(unsigned int _uiPosition){
		if (_uiPosition >= m_uiCompte)
			return false;

		if (m_pDerniere != nullptr)
		{
			if(_uiPosition > (m_uiCompte / 2))
			{
				AllerFin();
				for(unsigned int ui = 0; ui < (m_uiCompte - _uiPosition) - 1; ui++)
					AllerPrecedent();
			}
			else
			{
				AllerDebut();
				for(unsigned int ui = 0; ui < (_uiPosition); ui++)
					AllerSuivant();
			}
			return true;
		}
		return false;
	}

	/******************************************************
	But: Ajoute une cellule au d�but de la liste.

	Param�tres: T _Element l'�l�ment a lister.

	Retour: Aucun.
	*******************************************************/
	void AjouterDebut(T _Element){
		if(m_pDerniere == nullptr)
		{
			m_pDerniere = new CCelluleListeDC<T>(_Element,nullptr,nullptr);
			m_pDerniere->setSuivant(m_pDerniere);
			m_pDerniere->setPrecedent(m_pDerniere);
			m_uiCompte++;
		}
		else
		{
			m_pDerniere->setSuivant(new CCelluleListeDC<T>(_Element,m_pDerniere,m_pDerniere->getSuivant()));
			m_pDerniere->getSuivant()->getSuivant()->setPrecedent(m_pDerniere->getSuivant());
			m_uiCompte++;
		}
	}

	/******************************************************
	But: Ajoute une cellule � la fin de la liste.

	Param�tres: T _Element l'�l�ment a lister.

	Retour: Aucun.
	*******************************************************/
	void AjouterFin(T _Element){
		if(m_pDerniere == nullptr)
		{
			m_pDerniere = new CCelluleListeDC<T>(_Element,nullptr,nullptr);
			m_pDerniere->setSuivant(m_pDerniere);
			m_pDerniere->setPrecedent(m_pDerniere);
			m_uiCompte++;
		}
		else
		{
			m_pDerniere->setSuivant(new CCelluleListeDC<T>(_Element,m_pDerniere,m_pDerniere->getSuivant()));
			m_pDerniere->getSuivant()->getSuivant()->setPrecedent(m_pDerniere->getSuivant());
			m_pDerniere = m_pDerniere->getSuivant();
			m_uiCompte++;
		}
	}

	/********************************************************************************
	But: Ins�re une cellule � l'endroit indiqu� par le curseur

	Param�tres: T _Element l'�l�ment a lister.

	Retour: true si l'op�ration s'est faite et false si elle ne s'est pas ex�cut�e.
	*********************************************************************************/
	void Inserer(T _Element){
		
		//if(m_pCurseur == nullptr)
		//	return false;

		m_pCurseur = new CCelluleListeDC<T>(_Element,m_pCurseur->getPrecedent(),m_pCurseur);
		m_pCurseur->getPrecedent()->setSuivant(m_pCurseur);
		m_pCurseur->getSuivant()->setPrecedent(m_pCurseur);
		m_uiCompte++;

		//return true;
	}
	
	/*******************************************************************************
	But: Retire une cellule de la liste.

	Param�tres: bool _boSupprimer: supprimer ou non l'�l�ment

	Retour: true si l'op�ration s'est faite et false si elle ne s'est pas ex�cut�e.
	********************************************************************************/
	bool Retirer(bool _boSupprimer){
	
		if(m_pCurseur == nullptr)
			return false;

		CCelluleListeDC<T>* pCelltemp = m_pCurseur;
		m_pCurseur->getPrecedent()->setSuivant(m_pCurseur->getSuivant());
		m_pCurseur->getSuivant()->setPrecedent(m_pCurseur->getPrecedent());

		if(m_pCurseur == m_pDerniere){
			m_pCurseur = m_pCurseur->getPrecedent();
			m_pDerniere = m_pDerniere->getPrecedent();
		}
		else
			m_pCurseur = m_pCurseur->getSuivant();

		if (_boSupprimer)
			delete pCelltemp->getElement();

		delete pCelltemp;
		m_uiCompte--;
		if(!m_uiCompte)
		{
			m_pCurseur = nullptr;
			m_pDerniere = nullptr;
		}
		return true;
	}

	//Acesseurs//

	/******************************************************
	But: Obtient l'�l�ment ou se trouve le curseur.

	Param�tres: Aucun.

	Retour: Retourne l'�l�ment pr�sent dans la liste.
	*******************************************************/
	T ObtenirElement(){
		if (m_pCurseur != nullptr)
			return m_pCurseur->getElement();
		return nullptr;
	}

	unsigned int Compte(){
		return m_uiCompte;
	}
};