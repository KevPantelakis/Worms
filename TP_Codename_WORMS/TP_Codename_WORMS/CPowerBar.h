class CPowerBar{
private:

	SDL_Rect m_RectPower; //Dimension et position de la powerbar
	bool m_boActive;
	bool m_boReversePowerBar; // Bool�en pour v�rifier si la barre de lancement ira dans le sense contraire.
	unsigned int m_uiPower; // Repr�sente la longueuer du Fill Rect.
public:

	/*!
	@method Constructeur.
	@brief Initialise les donn�es membres.
	@param _Rect rect de l'objet qui a une powerbar
	@return Adresse m�moire de l'objet.
	@discussion Classe h�ritant de CObjets, elle prend donc les param�tres du constructeur CObjets
	*/
	CPowerBar(SDL_Rect _Rect){
		m_boActive = false;
		m_boReversePowerBar = false;
		m_RectPower.x = _Rect.x;
		m_RectPower.y = _Rect.y;
		m_RectPower.w = 0;
		m_RectPower.h = 10;
	}

	/*!
	@method Destructeur:
	@brief Permet  de d�truire les objets cr��s en m�moire
	*/
	~CPowerBar(){}

	/*!
	@method <#name#>
	@brief <#Short description#>
	@param <#Paremeter#>
	@return <#Return value#>
	@discussion <#Other code info#>
	*/
	void Draw(SDL_Renderer* _pRenderer){
		if (m_uiPower <= 16)
			SDL_SetRenderDrawColor(_pRenderer, (150 + m_uiPower), (204 + m_uiPower), 0, 0);
		if (m_uiPower > 17 && m_uiPower <= 34)
			SDL_SetRenderDrawColor(_pRenderer, (204 + m_uiPower), (204 + m_uiPower), 0, 0);
		if (m_uiPower > 34)
			SDL_SetRenderDrawColor(_pRenderer, (208 + m_uiPower), (100 + m_uiPower), 0, 0);
		SDL_RenderFillRect(_pRenderer, &m_RectPower);
	}

	/*!
	@method <#name#>
	@brief <#Short description#>
	@param <#Paremeter#>
	@return <#Return value#>
	@discussion <#Other code info#>
	*/
	void PowerUp(){
		if (m_uiPower <= 50 && !m_boReversePowerBar){
			if (m_uiPower == 50)
				m_boReversePowerBar = true;
			else
				m_uiPower++;
		}
		else if (m_boReversePowerBar){
			if (m_uiPower == 0)
				m_boReversePowerBar = false;
			else
				m_uiPower--;
		}
	}

	/*!
	@method <#name#>
	@brief <#Short description#>
	@param <#Paremeter#>
	@return <#Return value#>
	@discussion <#Other code info#>
	*/
	void PowerDown(){
		//todo
	}

	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux donn�es membres.
	*/

	void SetDimension(){
		m_RectPower.w = m_uiPower;
	}
	void SetPosition(int _ix, int _iy){
		m_RectPower.x = _ix;
		m_RectPower.y = _iy - 15;
	}
	unsigned int getPowerLevel(){
		unsigned int temp = m_uiPower * 2;
		m_uiPower = 0;
		return temp;
	}
	void setPowerLevel(unsigned int _ipower){ m_uiPower = _ipower; }
};