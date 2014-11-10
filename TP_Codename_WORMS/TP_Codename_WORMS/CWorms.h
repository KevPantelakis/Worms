/*!
 * Fichier pour la classe CWorms
 * Créé le 06/11/2014 à 13h50 par Richer Archambault
 */


#include "CTimer.h"
#include "CListeDC.h"
#include "CGestionnaireRessources.h"
#include "CWindow.h"
#include "CGUIE.h"
#include "CLabel.h"
#include "ClabelImage.h"
#include "CButton.h"
#include "CTextBox.h"
#include "CSlideShow.h"
#include "CMenu.h"



/*!
 @class CWorms
 @discussion Classe principale du projet, dans lequel se fait la gestion de l'affichage et des SDLEvent.
 */
class CWorms {
private:
	static	CWindow* m_pWindow;
	static	CMenu* m_MenuPrincipal;
	static	CMenu* m_MenuNewGame;
	static	CMenu* m_MenuPause;
	static	CMenu* m_MenuNewTeam;
	static	SDL_Event* m_pEvent;
	static	bool m_boRun;
	static 	bool m_boInMenu;
	static	CGestionnaireRessources* m_Gestionaire;
public:
	
	CWorms(){
		m_pWindow = new CWindow("Worms", WIDTH, HEIGHT);
		m_MenuPrincipal = new CMenu(m_pWindow->getRenderer(), {0, 0, WIDTH, HEIGHT});
		m_MenuNewGame = new CMenu(m_pWindow->getRenderer(), {0, 0, WIDTH, HEIGHT});
		m_MenuPause = new CMenu(m_pWindow->getRenderer(), {0, 0, (WIDTH / 2), (HEIGHT / 2)});
		m_MenuNewTeam = new CMenu(m_pWindow->getRenderer(), {0, 0, WIDTH, HEIGHT});
		m_pEvent = new SDL_Event();
		m_Gestionaire = new CGestionnaireRessources();
	}
	
	~CWorms(){
		delete m_pWindow;
		delete m_MenuPrincipal;
		delete m_MenuNewGame;
		delete m_MenuPause;
		delete m_MenuNewTeam;
		delete m_pEvent;
	}
	
	static void Start(){
		while (m_boRun) {
			Render();
			while (SDL_PollEvent(m_pEvent)) {
				if (m_boInMenu){
					if (m_MenuPrincipal->IsActive())
						m_MenuPrincipal->HandleEvent(*m_pEvent);
					else if (m_MenuNewGame->IsActive())
						m_MenuNewGame->HandleEvent(*m_pEvent);
					else if (m_MenuNewTeam->IsActive())
						m_MenuNewTeam->HandleEvent(*m_pEvent);
					else if (m_MenuPause->IsActive())
						m_MenuPause->HandleEvent(*m_pEvent);
				}
				
				// Event In-Game.
					switch (m_pEvent->type) {
						default:
							break;
					}
			}
		}
	}
	
	static void Render(){
		SDL_RenderClear(m_pWindow->getRenderer());
		SDL_SetRenderDrawColor(m_pWindow->getRenderer(), 255, 255, 255, 255);
		if (m_boInMenu){
			if (m_MenuPrincipal->IsActive())
				m_MenuPrincipal->Render();
			else if (m_MenuNewGame->IsActive())
				m_MenuNewGame->Render();
			else if (m_MenuNewTeam->IsActive())
				m_MenuNewTeam->Render();
			else if (m_MenuPause->IsActive())
				m_MenuPause->Render();
		}
		else{		//Affichage in-game.
			
		}
		m_pWindow->Refresh();
	}
	
	static void LoadResources(string _argv){
		string strPath(_argv); //Donnée membre représentant le chemin du fichier.
		unsigned int uiPosString = (strPath.length() - 1); // Donnée membre représentant une position dans la string.
#if defined(__APPLE__) && defined(__MACH__)
		while (strPath[uiPosString] != '/'){
			strPath.erase(uiPosString, 1);
			uiPosString--;
		}
#elif defined (_win32)
		while (strPath[uiPosString] != '\\'){
			strPath.erase(uiPosString, 1);
			uiPosString--;
		}
#endif
		strPath.append("Ressources");
#if defined(__APPLE__) && defined(__MACH__)
		strPath.append("/");
#elif defined (_win32)
		strPath.append("\\");
#endif
		string FileName[12] = {"Arpegius.ttf", "Btn1.png", "BtnL.png", "BtnR.png", "map1.png", "background1.png", "map2.png", "background2.png", "map3.png", "background3.png", "map4.png", "background4.png"};
		string strFilePath[12];
		for (int i = 0; i < 3; i++){
			strFilePath[i] = strPath;
			strFilePath[i].append(FileName[i]);
		}
		m_Gestionaire->AjouterFont(new CFont("FontMenu", strFilePath[0].c_str(), 30));
			/* Sprite pour le menu principal */
		m_Gestionaire->AjouterSprite(new CSprite("SpriteBtnNG", IMG_LoadTexture(m_pWindow->getRenderer(),strFilePath[1].c_str()), 2, 1, 0, 0));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteBtnQ", IMG_LoadTexture(m_pWindow->getRenderer(), strFilePath[1].c_str()), 2, 1, 0, 0));
			/* Sprite pour le menu New Game */
		m_Gestionaire->AjouterSprite(new CSprite("SpriteBtnCancel", IMG_LoadTexture(m_pWindow->getRenderer(), strFilePath[1].c_str()), 2, 1, 0, 0));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteBtnPlay", IMG_LoadTexture(m_pWindow->getRenderer(), strFilePath[1].c_str()), 2, 1, 0, 0));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteBtnNT", IMG_LoadTexture(m_pWindow->getRenderer(), strFilePath[1].c_str()), 2, 1, 0, 0));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteMapLeft", IMG_LoadTexture(m_pWindow->getRenderer(), strFilePath[2].c_str()), 2, 1, 0, 0));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteMapRight", IMG_LoadTexture(m_pWindow->getRenderer(), strFilePath[3].c_str()), 2, 1, 0, 0));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteTeamLeft", IMG_LoadTexture(m_pWindow->getRenderer(), strFilePath[2].c_str()), 2, 1, 0, 0));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteTeamRight", IMG_LoadTexture(m_pWindow->getRenderer(), strFilePath[3].c_str()), 2, 1, 0, 0));
			/* Map et leur background */
		m_Gestionaire->AjouterSurface(new CSurface("map1", IMG_Load(strFilePath[5].c_str())));
		m_Gestionaire->AjouterSurface(new CSurface("background1", IMG_Load(strFilePath[6].c_str())));
		m_Gestionaire->AjouterSurface(new CSurface("map2", IMG_Load(strFilePath[7].c_str())));
		m_Gestionaire->AjouterSurface(new CSurface("background2", IMG_Load(strFilePath[8].c_str())));
		m_Gestionaire->AjouterSurface(new CSurface("map3", IMG_Load(strFilePath[9].c_str())));
		m_Gestionaire->AjouterSurface(new CSurface("background3", IMG_Load(strFilePath[10].c_str())));
		m_Gestionaire->AjouterSurface(new CSurface("map4", IMG_Load(strFilePath[11].c_str())));
		m_Gestionaire->AjouterSurface(new CSurface("background4", IMG_Load(strFilePath[12].c_str())));

		
	}
	
	static void Init(string _argv){
		LoadResources(_argv);
			//
			// Initialisation du menu Principal
			//
		m_MenuPrincipal->AddElement(new CButton("btnNewGame", "New Game", m_Gestionaire->GetFont("FontMenu"), {0,0,10,10}, m_Gestionaire->GetSprite("SpriteBtnNG")), 800, 200, 162, 33);
		m_MenuPrincipal->AddElement(new CButton("btnQuit", "Quit", m_Gestionaire->GetFont("FontMenu"), {0,0,10,10}, m_Gestionaire->GetSprite("SpriteBtnQ")), 800, 500, 162, 33);
		m_MenuPrincipal->getElement("btnQuit")->OnClickAction = FuncBtnQuit;
		m_MenuPrincipal->AddElement(new CLabel("lblWorms", "Worms", m_Gestionaire->GetFont("FontMenu"), {0, 0, 10, 10}), 100, 100, 400, 200);
		m_MenuPrincipal->getElement("btnNewGame")->OnClickAction = FuncBtnNewGame;
		m_MenuPrincipal->ActivateMenu();
			//
			// Initialisation du menu NewGame
			//
		m_MenuNewGame->AddElement(new CLabel("lblNewGame", "Create a new game", m_Gestionaire->GetFont("FontMenu"), {}), 0, 0, 100, 20);
		m_MenuNewGame->AddElement(new CButton("btnCancel", "Cancel", m_Gestionaire->GetFont("FontMenu"), {}, m_Gestionaire->GetSprite("SpriteBtnCancel")), 20, (HEIGHT - 66), 162, 33);
		m_MenuNewGame->AddElement(new CButton("btnPlay", "Play", m_Gestionaire->GetFont("FontMenu"), {}, m_Gestionaire->GetSprite("SpriteBtnPlay")), ((WIDTH / 2) - 81), (HEIGHT - 66), 162, 33);
		m_MenuNewGame->AddElement(new CButton("btnNTeam", "New Team", m_Gestionaire->GetFont("FontMenu"), {}, m_Gestionaire->GetSprite("SpriteBtnNT")), (WIDTH - 182), (HEIGHT - 66), 162, 33);
		CSlideShow* SSTemp = new CSlideShow("SSMap", m_Gestionaire->GetFont("FontMenu"), {}, m_Gestionaire->GetSprite("SpriteMapLeft"), m_Gestionaire->GetSprite("SpriteMapRight"));
		SSTemp->ajouterTexture(4, SDL_CreateTextureFromSurface(m_pWindow->getRenderer(), m_Gestionaire->GetSurface("map1")->getSurface()), SDL_CreateTextureFromSurface(m_pWindow->getRenderer(), m_Gestionaire->GetSurface("map2")->getSurface()), SDL_CreateTextureFromSurface(m_pWindow->getRenderer(), m_Gestionaire->GetSurface("map3")->getSurface()), SDL_CreateTextureFromSurface(m_pWindow->getRenderer(), m_Gestionaire->GetSurface("map4")->getSurface()));
		m_MenuNewGame->AddElement(SSTemp, 20, 40, 500, 300);
		
	}
	
		//
		// Définition des action de chaque bouton dans les menu.
		//
	static void FuncBtnQuit(){
		m_boRun = false;
	}
	static void FuncBtnNewGame(){
		m_MenuPrincipal->DeActivateMenu();
		m_MenuNewGame->ActivateMenu();
	}
	
};

	// Initialisation des données membre statique

CWindow* CWorms::m_pWindow = new CWindow("Worms", WIDTH, HEIGHT);
CMenu* CWorms::m_MenuPrincipal = new CMenu(m_pWindow->getRenderer(), {0, 0, WIDTH, HEIGHT});
CMenu* CWorms::m_MenuNewGame = new CMenu(m_pWindow->getRenderer(), {0, 0, WIDTH, HEIGHT});
CMenu* CWorms::m_MenuPause = new CMenu(m_pWindow->getRenderer(), {0, 0, (WIDTH / 2), (HEIGHT / 2)});
CMenu* CWorms::m_MenuNewTeam = new CMenu(m_pWindow->getRenderer(), {0, 0, WIDTH, HEIGHT});
bool CWorms::m_boInMenu = true;
SDL_Event* CWorms::m_pEvent = new SDL_Event();
CGestionnaireRessources* CWorms::m_Gestionaire = new CGestionnaireRessources();
bool CWorms::m_boRun = true;

