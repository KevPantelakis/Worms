#ifndef TP_Codename_WORMS_CBazouka_h
#define TP_Codename_WORMS_CBazouka_h


/*!
@CBazouka
@Classe permettant l'affichage et la rotation du bazouka
*/
class CBazouka{
private:
	//Donn�es membres:
	SDL_Rect m_Rect; //La pos du rectangle de l'objet
	SDL_Rect m_RectSurface; //La pos du rectangle de l'objet
	double iAngle; // L'angle de rotation
	SDL_Texture* m_pTexture; // Texture de l'image � afficher.
	SDL_Surface* m_pSurfaceBarreLancement; // Surface de la barre de lancement.
	bool boIsLaunch; // Bool�en pour v�rifier si le bazouka va lancer un missile
	bool boIsRotated; // Bool�en pour v�rifier si le bazouka sera en rotation
	bool boBarreLancement; // Bool�en pour v�rifier si la barre de lancement sera afficher
	unsigned int iPower; // Repr�sente le power du missile.

public:
	/*!
	@Constructeur
	@Description: Permet d'initialiser les donn�es membres
	@param _ix _iy : la pos du bazouka (� modifier pour la pos du worms)
	@param _pTexture : texture de l'image � afficher.
	@Classe h�ritant de CObjets, elle prend donc les param�tres du constructeur CObjets
	*/
	CBazouka(int _ix, int _iy, SDL_Texture* _pTexture){ // La position du bazouka devra �tre remplacer par la position du worms qui s'apprete  a attaquer.
		m_Rect.x = _ix;
		m_Rect.y = _iy;
		m_Rect.w = 52; // Dimension du bazouka
		m_Rect.h = 28; // Dimension du bazouka
		m_pTexture = _pTexture;
		m_pSurfaceBarreLancement = SDL_CreateRGBSurface(0, m_RectSurface.x, 10, 32, 0, 0, 0, 0);
		boIsLaunch = false;
		boIsRotated = false;
		boBarreLancement = false;
		iAngle = 0;
		iPower = 0;
	}

	/*!
	@methodRender
	@param _pRenderer : Renderer pour rendre la texture du bazouka
	@return null
	*/
	void Render(SDL_Renderer* _pRenderer){

		if (!boIsRotated)
			SDL_RenderCopy(_pRenderer, m_pTexture, NULL, &m_Rect);
		else
			SDL_RenderCopyEx(_pRenderer, m_pTexture, NULL, &m_Rect, iAngle, NULL, SDL_FLIP_NONE);

		if (boIsLaunch){
			IsLaunch(_pRenderer);
		}
	}
	/*!
	@method IsLaunch
	@description: permet de faire afficher la barre de lancement.
	@param _pRenderer: Renderer pour rendre la texture du bazouka
	@return null
	*/
	void IsLaunch(SDL_Renderer* _pRenderer){
		SetRectSurface(iPower);

		if (iPower <= 16)
			SDL_SetRenderDrawColor(_pRenderer, 150 + iPower, (200 + iPower + 4), 0, 0);
		if (iPower > 17 && iPower <= 34)
			SDL_SetRenderDrawColor(_pRenderer, (200 + iPower + 4), (200 + iPower + 4), 0, 0);
		if (iPower > 34)
			SDL_SetRenderDrawColor(_pRenderer, 200 + iPower + 8, 100 + iPower, 0, 0);


		SDL_RenderFillRect(_pRenderer, &m_RectSurface);


	}
	/*!
	@method HandleEvent
	@param _Event : Un SDL_Event pour traiter les evenement
	@return null
	*/
	void HandleEvent(SDL_Event* _Event){

		switch (_Event->key.keysym.sym){

		case SDLK_UP:

			if (iAngle > -360)
				iAngle--;
			else{
				iAngle = 0;
				iAngle--;
			}
			boIsRotated = true;
			break;

		case SDLK_DOWN:
			iAngle++;
			if (iAngle > 360)
				iAngle = 0;
			boIsRotated = true;
			break;

		case SDLK_SPACE:
			boIsLaunch = true;
			if (iPower <= 50 && !boBarreLancement){
				if (iPower == 50)
					boBarreLancement = true;
				iPower = (iPower + 1);
			}
			else
			if (boBarreLancement){
				iPower--;
				if (iPower == 0)
					boBarreLancement = false;
			}
			break;
		}
	}
	/*!
	@method SetRectSurface
	@description: permet de set la position et la dimension du rect de la barre de lancement.
	@param: _iWidth: la largeur du rect
	*/

	void SetRectSurface(int _iWidth){
		m_RectSurface.x = m_Rect.x;
		m_RectSurface.y = m_Rect.y - 15;
		m_RectSurface.w = _iWidth;
		m_RectSurface.h = 10;

	}


	/*!
	@Destructeur:
	@Permet de d�truire les objets cr��s en m�moire
	*/
	~CBazouka(){

	}
};

#endif
