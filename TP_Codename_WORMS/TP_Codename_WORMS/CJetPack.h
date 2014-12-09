#ifndef TP_Codename_WORMS_CJetPack_h
#define TP_Codename_WORMS_CJetPack_h

/* Liste de chose TOO DOOO :
-Faire en sorte que le worm en jetpack rotate d�pendament si tu vas a gauche ou droite
-Tester
*/
/*!
 @class CJetPack
 @discussion Classe permettant l'affichage et l'utilisation du JetPack
 */
class CJetPack{
private:
	//Donn�es membres:
	SDL_Rect m_RectJetPack;
	SDL_Rect m_RectSurface;		// La pos du rectangle de la surface de la barre de gaz
	CPowerBar* m_pBarreGaz;		// Surface de la barre de lancement.
	bool boBarreGaz;			// Bool�en pour v�rifier si la barre de lancement sera afficher
	double m_iAngle;			// L'angle d'orientation du vecteur de d�placement
	double m_iNorme;			// La norme du vecteur de d�placement
	C2DVector* m_pVecteur;		// Le pointeur de vecteur de d�placement
	CTimer* m_pTimer;			// Une minuterie pour d�cr�menter le power � tous les "x" secondes
	CWorm * Worm;


public:


	/*!
	@method Constructeur.
	@brief Initialise les donn�es membres.
	@param _RectWorm: le rect position du worm qui s'apprete � s'envoler
	@return Adresse m�moire de l'objet.
	@discussion No discussion is needed.
	*/
	CJetPack(CWorm* _pWorm){
		Worm = _pWorm;
		m_RectJetPack = _pWorm->getPosition();
		m_pBarreGaz = new CPowerBar(m_RectSurface);
		m_pBarreGaz->setPowerLevel(100);
		m_iAngle = 0;
		m_iNorme = 20;
		m_pVecteur = new C2DVector(m_iNorme, m_iAngle, m_RectJetPack.x, m_RectJetPack.y);
		boBarreGaz = false;
		m_pTimer = new CTimer();
		m_pTimer->SetTimer(100);

	}

	/*!
	@method Destructeur.
	@brief Destroy.
	@discussion He is dead. spotted
	*/
	~CJetPack(){
	}

	/*!
	@methodRender
	@param _pRenderer : Renderer pour render la barre de gaz
	@return null
	*/
	void Render(SDL_Renderer* _pRenderer){
		m_pBarreGaz->Draw(_pRenderer);
	}

	/*!
	@method Deplacer
	@brief Deplace le jetpack
	@param _RectPosInitiale: position initiale du worm
	@param _Angle : angle du vecteur deplacement.
	@return Aucun
	@discussion none.
	*/
	/*void Deplacer(SDL_Rect* _RectPosInitiale, double _Angle){
		_RectPosInitiale->x += m_iNorme * cos(_Angle);
		_RectPosInitiale->y += m_iNorme * sin(_Angle);
		m_RectJetPack = _RectPosInitiale;
		}*/

	/*!
	@method HandleEvent
	@param _Event : Un SDL_Event pour traiter les evenement
	@return null
	*/
	void RefreshPosWorm(CWorm* _pWorm){
		_pWorm->setPosXY(m_RectJetPack.x, m_RectJetPack.y);
	}
	void HandleEvent(SDL_Event* _Event){
		switch (_Event->key.keysym.sym){


			int right, left, up;
		case SDLK_LEFT:
			//V�rifier si le timer � �t� partie, sinon, le partir
			if (!m_pTimer->HasStarted()){
				m_pTimer->Start();
			}
			//D�placer la position du rect selon un angle de 180degree ou pi radian
			left = m_RectJetPack.x;
			left--;
			m_RectJetPack.x = left;
			cout << "LEFT. X = " << Worm->getPosition().x << " Y = " << Worm->getPosition().y << endl;
			RefreshPosWorm(Worm);
			//V�rifier si le timer est d�clancher, si oui, d�cr�menter le power et repartir le timer
			if (m_pTimer->IsElapsed()){
				if (m_pBarreGaz->getPower() != 0){
					m_pBarreGaz->PowerDown();
					m_pTimer->Start();
				}
			}
			break;

		case SDLK_UP:
			if (!m_pTimer->HasStarted()){
				m_pTimer->Start();
			}
			up = m_RectJetPack.y;
			up-= 2;
			m_RectJetPack.y = up;
			cout << "UP. X = " << Worm->getPosition().x << " Y = " << Worm->getPosition().y << endl;
			RefreshPosWorm(Worm);
			if (m_pTimer->IsElapsed()){
				if (m_pBarreGaz->getPower() != 0){
					m_pBarreGaz->PowerDown();
					m_pTimer->Start();
				}
			}
			break;

		case SDLK_RIGHT:
			if (!m_pTimer->HasStarted()){
				m_pTimer->Start();
			}
			if (m_pTimer->IsElapsed()){
				if (m_pBarreGaz->getPower() != 0){
					m_pBarreGaz->PowerDown();
					m_pTimer->Start();
				}
				right = m_RectJetPack.x;
				right++;
				m_RectJetPack.x = right;
				cout << "RIGHT. X = " << Worm->getPosition().x << " Y = " << Worm->getPosition().y << endl;
				RefreshPosWorm(Worm);
			}
			break;

		}
	}



};

#endif
