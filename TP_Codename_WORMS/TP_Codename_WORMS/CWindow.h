//
//  CWindow.h
//  CFenetre
//
//  Created by Richer Archambault on 2014-10-07.
//  Copyright (c) 2014 Richer Archambault. All rights reserved.
//



#ifndef CFenetre_CWindowManager_h
#define CFenetre_CWindowManager_h


/*!
 @class CWindow
 @discussion Classe Exploitant la SDL pour l'affichage des fenetres
 */
class CWindow {
private:
	SDL_Window* m_pSDLWindow;		// Fen�tre.
	SDL_Renderer* m_pSDLRenderer;	// Rendu de la fen�tre.
	unsigned int m_uiWindowID;		// ID de la F�netre.
public:

	CWindow(const char* _WindowTitle, unsigned int _width, unsigned int _height){
		m_pSDLWindow = SDL_CreateWindow(_WindowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, NULL);
		m_pSDLRenderer = SDL_CreateRenderer(m_pSDLWindow, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
		m_uiWindowID = SDL_GetWindowID(m_pSDLWindow);
	}

	~CWindow(){
		SDL_DestroyRenderer(m_pSDLRenderer);
		SDL_DestroyWindow(m_pSDLWindow);
	}

	void Refresh(){
		SDL_RenderPresent(m_pSDLRenderer);
	}

	void SetTitle(const char *_Title){
		SDL_SetWindowTitle(m_pSDLWindow, _Title);
	}

	unsigned int GetWindowID(){
		return m_uiWindowID;
	}

	SDL_Renderer* getRenderer(){
		return m_pSDLRenderer;
	}

	SDL_Window* getWindow(){
		return m_pSDLWindow;
	}
};



#endif
