//
//  CGame.h
//
//  Created by Kevin Pantelakis on 2014-11-11.
//
//

/*!
@class CGame.h
@discussion Classe qui repr�sente une partie.
*/
class CGame{
private:
	Uint8 m_uiTeamTurn;					// Indique a quelle �quipe de jouer.
	Uint8 m_uiNbOfPlayingTeams;			// Combien d'�quipe participe a la partie.
	Uint8 m_uiNbOfWormPerTeam;
	SDL_Renderer* m_pRenderer;			// Rendu de la fenetre du jeu. 
	CBoussole* m_pBoussole;				// Boussole de vents.
	CMap* m_pMap;						// Champ de bataille.
	CListeDC<CTeam*>* m_pListeTeam;		// Liste d'�quipe qui participe au jeu.
	CListeDC<CObjets*>* m_pListeObjets; // Liste d'objets a afficher.
	bool m_boInPlay;					// Indique si la partie est termin� ou non.
	CGestionnaireRessources* m_Gestionaire;
	bool m_boPause;
	CTimer* TurnTimer;
	CTimer* DropperTimer;
public:

	/*!
	@method Constructeur.
	@brief Initialise les donn�es membres.
	@param CMap* _Map : Map a jouer.
	@param CBoussole* _Boussole : La boussole.
	@param SDL_Renderer* _Renderer: Le rendu de la fenetre.
	@return Adresse m�moire de l'objet.
	@discussion Nuff said.
	*/
	CGame(CMap* _Map, CBoussole* _Boussole, SDL_Renderer* _Renderer, int _NbOfTeam, int _NbOfWormPerTeam, CGestionnaireRessources* _Gestionaire){
		TurnTimer = new CTimer();
		DropperTimer = new CTimer();
		m_uiNbOfPlayingTeams = _NbOfTeam;
		m_uiNbOfWormPerTeam = _NbOfWormPerTeam;
		m_Gestionaire = _Gestionaire;
		m_pBoussole = _Boussole;
		m_pRenderer = _Renderer;
		m_uiTeamTurn = 0;
		m_boInPlay = false;
		m_boPause = false;
		m_pMap = _Map;
		CPhysics::Init(m_pMap->getMap(), m_pMap->getGravity(), m_pMap->getWind());
		m_pListeTeam = nullptr;
		m_pListeObjets = new CListeDC<CObjets*>();
		for(int i = 0; i < m_pMap->getMine(); i++){
			m_pListeObjets->AjouterFin(new CMines(20, {((rand()% (WIDTH - 10)) + 5), 5, 12, 8}, m_Gestionaire->GetTexture("mine")->GetTexture()));
		}
		DropperTimer->SetTimer(2000);
		DropperTimer->Start();
	}
	
	/*!
	@method Destructeur.
	@brief Destroy.
	@discussion He dead man... he dead.
	*/
	~CGame(){
		delete m_pListeTeam;
		delete m_pListeObjets;
		delete m_pBoussole;
		CPhysics::Annihilate();
	}

	/*!
	@method NextTurn
	@brief Change le focus des �quipes pour le changement de tour.
	*/
	void NextTurn(){
		Uint8 uitemp = m_uiTeamTurn % m_uiNbOfPlayingTeams;
		m_pListeTeam->AllerA(uitemp);
		if (m_pListeTeam->ObtenirElement()->IsFocused()) {
			m_pListeTeam->ObtenirElement()->NextTurn();
			m_pListeTeam->ObtenirElement()->setFocus(false);
		}
		m_pListeTeam->AllerA((uitemp + 1) % m_uiNbOfPlayingTeams);
		m_pListeTeam->ObtenirElement()->setFocus(true);
	}

	/*!
	@method Render
	@brief Affiche le jeu sur la fenetre.
	*/
	void Render(){
		m_pMap->Draw(m_pRenderer);
		m_pBoussole->Draw(m_pRenderer);
		
		m_pListeObjets->AllerDebut();
		for (int i = 0; i < m_pListeObjets->Count(); i++){
			if (!m_boPause)
				m_pListeObjets->ObtenirElement()->Move();
			m_pListeObjets->ObtenirElement()->Draw(m_pRenderer);
			m_pListeObjets->AllerSuivant();
		}
		if (m_pListeTeam != nullptr){
			m_pListeTeam->AllerDebut();
			
			for (int i = 0; i < m_uiNbOfPlayingTeams; i++){
				m_pListeTeam->ObtenirElement()->draw(m_pRenderer);
				m_pListeTeam->AllerSuivant();
			}
		}
	}
	
	void HandleEvent(SDL_Event _Event){
		if (!m_boPause){
			switch (_Event.key.keysym.sym) {
			case SDLK_ESCAPE:
				PauseGame();
				break;
			}
		}
	}

	//Papoi,papoi
	void AjouterTeam(CTeam* _team){
		m_pListeTeam->AjouterFin(_team);
	}
	
	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux donn�es membres.
	*/

	void CreateTeam(){
		m_pListeTeam = new CListeDC<CTeam*>();
		string temp("Team");
		char buf[10];
		for (int i = 0; i < m_uiNbOfPlayingTeams; i++){
			temp.append(SDL_itoa(i, buf, 10));
			m_pListeTeam->AjouterFin(new CTeam(temp, {static_cast<Uint8>(i * 200), static_cast<Uint8>(i * 100), static_cast<Uint8>(i * 50), 1},m_Gestionaire->GetTexture("worm")->GetTexture(), m_Gestionaire->GetTexture("wormSprite")->GetTexture(), m_uiNbOfWormPerTeam, m_Gestionaire->GetFont("FontMenu")));
			temp.pop_back();
		}
	}
	
	void MainGame(){
		if (DropperTimer->IsElapsed() && (m_pListeTeam == nullptr))
			CreateTeam();
	}
	
	void setNbOfPlayingTeams(Uint8 _NbOfTeams){ m_uiNbOfPlayingTeams = _NbOfTeams; }

	Uint8 getNbOfPlayingTeams(){ return m_uiNbOfPlayingTeams; }
	
	bool inGame(){return m_boInPlay;}
	void Activate(){m_boInPlay = true;}
	void DeActivate(){m_boInPlay = false;}
	void PauseGame(){ m_boPause = true; }
	void ResumeGame(){ m_boPause = false; }

};